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
CALL InsertarAlumno(73573822, 'Noelia Marializ', 'Callao', 'A', 9.2, 18, 'S');
select * from Estudiante_Callao;

CALL InsertarAlumno(72227482, 'Marco Wanly', 'Lima', 'B', 9.2, 18, 'M');
select * from Estudiante_Lima;

-- Cargar la data desde un archivo y guardar en un tabla temporal
CREATE TABLE temp_estudiantes (
  DNI INT,
  NOMBRE VARCHAR(255),
  Ciudad VARCHAR(255),
  GRUPO VARCHAR(1),
  PROMEDIO FLOAT,
  EDAD INT,
  SEXO CHAR(1)
);

-- cargar usuarios de el dataset
\\copy public.temp_estudiantes (dni, nombre, ciudad, grupo, promedio, edad, sexo) FROM 'C:/Users/ObregonW/Desktop/UTEC/BASE-D~2/Labs/LAB141~1/dataset/LIMA_C~1.CSV' DELIMITER ',' CSV HEADER QUOTE '\"' ESCAPE '''';""
select * from temp_estudiantes;


-- Para la llamada de la funcion insertar
DO $$ 
DECLARE 
    estudiante RECORD;
BEGIN
    FOR estudiante IN (SELECT * FROM temp_estudiantes)
    LOOP
        CALL InsertarAlumno(estudiante.DNI, estudiante.NOMBRE, estudiante.Ciudad, estudiante.GRUPO, estudiante.PROMEDIO, estudiante.EDAD, estudiante.SEXO);
    END LOOP;
END $$;
select * from Estudiante_Callao;
select * from Estudiante_Lima;
