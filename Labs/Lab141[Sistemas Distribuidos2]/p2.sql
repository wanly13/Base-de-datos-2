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
BEFORE INSERT ON temp_estudiantes
FOR EACH ROW
EXECUTE FUNCTION create_partition_and_insert();



insert into temp_estudiantes values (72227482, 'Marco Wanly', 'Chacas', 'B', 9.2, 18, 'M');