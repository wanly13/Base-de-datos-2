-- CREAR UNA NUEVA TABLA EN CASO YA EXISTA

CREATE TABLE Estudiante (
  DNI INT,
  NOMBRE VARCHAR(255),
  Ciudad VARCHAR(255),
  GRUPO VARCHAR(1),
  PROMEDIO FLOAT,
  EDAD INT,
  SEXO CHAR(1)
);


CREATE OR REPLACE FUNCTION create_partition_and_insert() RETURNS TRIGGER AS
$BODY$
DECLARE
  partition_city TEXT;
  partition_name TEXT;
BEGIN
  partition_city := NEW.Ciudad;
  partition_name := TG_RELNAME || '_' || partition_city;

  -- Verificar si la partición existe
  IF NOT EXISTS (SELECT relname FROM pg_class WHERE relname = partition_name) THEN
    -- Crear la partición si no existe
    EXECUTE 'CREATE TABLE ' || partition_name || ' (CHECK (Ciudad = ''' || partition_city || ''')) INHERITS (' || TG_RELNAME || ');';
    RAISE NOTICE 'Se ha creado una nueva partición: %', partition_name;
  END IF;

  -- Insertar el registro en la partición correspondiente
  EXECUTE 'INSERT INTO ' || partition_name || ' SELECT (' || TG_RELNAME || ' ' || quote_literal(NEW) || ').* RETURNING *;';

  RETURN NULL;
END;
$BODY$
LANGUAGE plpgsql;

-- Crear el disparador (trigger) para invocar la función create_partition_and_insert
CREATE TRIGGER tr_create_partition_and_insert
BEFORE INSERT ON Estudiante
FOR EACH ROW
EXECUTE FUNCTION create_partition_and_insert();
