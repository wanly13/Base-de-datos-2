/* -- PASO 1) RESTAURAR LA BASE DE DATOS
    CREATE DATABASE dvdrental;
-- Descargamos el archivo y nos ubicamos en el terminal de pgAdminrestauramos la base de datos con pgRestore

pg_restore --dbname=dvdrental --username=postgres --no-owner --no-privileges --clean dvdrental.tar


ALTER TABLE film ADD COLUMN title_description_indexed tsvector;

UPDATE film SET title_description_indexed = to_tsvector('english', coalesce(title, '') || ' ' || coalesce(description, ''));

CREATE INDEX film_search_idx ON film USING gin(title_description_indexed);


CREATE INDEX film_search_idx ON film USING gin(title_description_indexed);


-- Consulta en el atributo sin indexar (por ejemplo, búsqueda en el título)
EXPLAIN ANALYZE SELECT * FROM film WHERE title ILIKE '%search_term%';

-- Consulta en el atributo indexado (título y descripción combinados)
EXPLAIN ANALYZE SELECT * FROM film WHERE title_description_indexed @@ to_tsquery('english', 'search_term');


-- Búsqueda en el atributo sin indexar con limitación de resultados
EXPLAIN ANALYZE SELECT * FROM film WHERE title ILIKE '%search_term%' LIMIT k;

-- Búsqueda en el atributo indexado con limitación de resultados
EXPLAIN ANALYZE SELECT * FROM film WHERE title_description_indexed @@ to_tsquery('english', 'search_term') LIMIT k;
 */

-- Ejemplo de donde saque los calculos de los tiempos
SELECT 
  setweight(to_tsvector('english', title), 'A') || setweight(to_tsvector('english', description), 'B')
    FROM film;


ALTER TABLE film ADD column indexado tsvector;

UPDATE  film SET indexado = T.indexado FROM (
  SELECT film_id,
   setweight(to_tsvector('english', title), 'A')   ||
   setweight(to_tsvector('english', description), 'B')
  AS indexado FROM film ) AS T WHERE film.film_id = T.film_id;


CREATE INDEX indexado_gin_idx on film USING gin(indexado);
-- 5.056 ms  Sin indexar
explain analyze
SELECT title, description FROM film
  WHERE description ilike '%man%' or description ilike '%woman%';
-- 0.376 ms Indexado
explain analyze
SELECT title, description FROM film
 WHERE to_tsquery('english', 'Man | Woman') @@ indexado;

-- Query por top k
explain analyze
SELECT title, description, 
       ts_rank_cd(indexado, query) AS rank
 FROM film, to_tsquery('english', 'Man | Woman') query 
 ORDER BY rank desc
 LIMIT 64;--2,4,8,16,32,64