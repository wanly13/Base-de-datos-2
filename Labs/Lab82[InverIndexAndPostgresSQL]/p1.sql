-- Creación de la tabla con dos atributos textuales, uno sin indexar y el otro indexado. 
CREATE EXTENSION pg_trgm

CREATE TABLE articles (
    body text,
    body_indexed text
);

-- Create Index
CREATE INDEX articles_search_idx ON articles USING gin (body_indexed gin_trgm_ops);

-- Inserción de datos aleatorios
INSERT INTO articles SELECT md5(random()::text), md5(random()::text) from ( SELECT * FROM generate_series(1,100000) AS id) AS x;

-- Consulta en el atributo sin indexar
EXPLAIN ANALYZE SELECT count(*) FROM articles WHERE body ILIKE '%abc%';

-- Consulta en el atributo indexado
EXPLAIN ANALYZE SELECT count(*) FROM articles WHERE body_indexed ILIKE '%abc%';


DELETE FROM articles;



/* CREATE TABLE articles (
	body text,
	body_indexed text
);

-- add an index
CREATE INDEX articles_search_idx ON articles USING gin (body_indexed gin_trgm_ops);

DELETE FROM articles;
-- populate table with data
INSERT INTO articles SELECT md5(random()::text), md5(random()::text) from ( SELECT * FROM generate_series(1,100) AS id) AS x;
 -- Consulta en el atributo sin indexar
EXPLAIN ANALYZE SELECT count(*) FROM articles WHERE body ILIKE '%abc%';
-- Consulta en el atributo indexado
EXPLAIN ANALYZE SELECT count(*) FROM articles WHERE body_indexed ILIKE '%abc%'; */