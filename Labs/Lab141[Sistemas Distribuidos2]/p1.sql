-- UNICAMENTE INSERCIONES DINAMICAS
-- Crear tabla para estudiantes de Lima
CREATE TABLE Estudiante_Lima (
    DNI INT,
    NOMBRE VARCHAR(255),
    Ciudad VARCHAR(255),
    GRUPO VARCHAR(1),
    PROMEDIO FLOAT,
    EDAD INT,
    SEXO CHAR(1)
);

-- Crear tabla para estudiantes de Callao
CREATE TABLE Estudiante_Callao (
    DNI INT,
    NOMBRE VARCHAR(255),
    Ciudad VARCHAR(255),
    GRUPO VARCHAR(1),
    PROMEDIO FLOAT,
    EDAD INT,
    SEXO CHAR(1)
);


-- Crear el procedimiento almacenado InsertarAlumno
CREATE OR REPLACE PROCEDURE InsertarAlumno(
    DNI INT,
    NOMBRE VARCHAR(255),
    Ciudad VARCHAR(255),
    GRUPO VARCHAR(1),
    PROMEDIO FLOAT,
    EDAD INT,
    SEXO CHAR(1)
)
LANGUAGE plpgsql
AS $$
BEGIN
    -- Determinar el fragmento correspondiente según la ciudad
    IF Ciudad = 'Lima' THEN
        INSERT INTO Estudiante_Lima (DNI, NOMBRE, Ciudad, GRUPO, PROMEDIO, EDAD, SEXO)
        VALUES (DNI, NOMBRE, Ciudad, GRUPO, PROMEDIO, EDAD, SEXO);
    ELSEIF Ciudad = 'Callao' THEN
        INSERT INTO Estudiante_Callao (DNI, NOMBRE, Ciudad, GRUPO, PROMEDIO, EDAD, SEXO)
        VALUES (DNI, NOMBRE, Ciudad, GRUPO, PROMEDIO, EDAD, SEXO);
    ELSE
        RAISE EXCEPTION 'Ciudad inválida';
    END IF;
    
    COMMIT;
END;
$$;

-- Pruebas para ver que funcionó correctamente la insercion
CALL InsertarAlumno(72227482, 'Marco Wanly', 'Lima', 'B', 9.2, 18, 'M');
CALL InsertarAlumno(73573822, 'Noelia Marializ', 'Callao', 'A', 9.2, 18, 'S');


-- Es un temporal para poder usar la funcion CALL (Para cargar los datos del CSV[no encontre otra forma de hacerlo directo])
CREATE TABLE temp_estudiantes (
  DNI INT,
  NOMBRE VARCHAR(255),
  Ciudad VARCHAR(255),
  GRUPO VARCHAR(1),
  PROMEDIO FLOAT,
  EDAD INT,
  SEXO CHAR(1)
);
-- Para la llamada de la funcion insertar
DO $$ 
DECLARE 
    estudiante RECORD;
BEGIN
    FOR estudiante IN (SELECT * FROM temp_estudiantes)
    LOOP
        PERFORM InsertarAlumno(estudiante.DNI, estudiante.NOMBRE, estudiante.Ciudad, estudiante.GRUPO, estudiante.PROMEDIO, estudiante.EDAD, estudiante.SEXO);
    END LOOP;
END $$;