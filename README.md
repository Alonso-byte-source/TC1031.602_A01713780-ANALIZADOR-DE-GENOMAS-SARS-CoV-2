# TC1031.602_A01713780-ANALIZADOR-DE-GENOMAS-SARS-CoV-2
# Sistema de análisis y organización de genomas de SARS-CoV-2

## Descripción

Este proyecto consiste en el desarrollo de un sistema en C++ para la carga, organización, búsqueda, filtrado y ordenamiento de información asociada a genomas completos de SARS-CoV-2.

El proyecto utiliza un conjunto de datos obtenido de **NCBI (National Center for Biotechnology Information)**, que contiene información sobre diferentes secuencias genómicas de SARS-CoV-2. Cada registro contiene atributos como accession, linaje, ubicación geográfica, fecha de recolección, huésped, longitud del genoma, completitud y fecha de liberación.

El propósito principal del proyecto es aplicar y analizar diferentes estructuras de datos y algoritmos fundamentales sobre un conjunto de datos de gran tamaño.

---

## Objetivos

### Objetivo general

Desarrollar un programa modular en C++ capaz de organizar y consultar un conjunto de datos de genomas de SARS-CoV-2 mediante estructuras de datos, algoritmos de búsqueda, filtros y algoritmos de ordenamiento.

### Objetivos específicos

- Cargar información desde un archivo TSV.
- Representar cada registro mediante una clase.
- Almacenar los registros utilizando un `std::vector`.
- Filtrar información utilizando diferentes atributos.
- Implementar algoritmos de búsqueda.
- Implementar algoritmos de ordenamiento.
- Aplicar buenas prácticas de programación y modularidad.

---

## Conjunto de datos

Los datos utilizados en este proyecto provienen de **NCBI** y corresponden a genomas completos de SARS-CoV-2.

El conjunto de datos contiene información como:

| Campo | Descripción |
|---|---|
| Accession | Identificador de la secuencia |
| Virus Pangolin Classification | Linaje de SARS-CoV-2 |
| Geographic Location | Ubicación geográfica de la muestra |
| Isolate Collection Date | Fecha en la que se recolectó la muestra |
| Host Name | Huésped de la muestra |
| Length | Longitud de la secuencia |
| Completeness | Estado de completitud del genoma |
| Release Date | Fecha de liberación del registro |

La fuente de los datos es:

**NCBI - National Center for Biotechnology Information**

https://www.ncbi.nlm.nih.gov/datasets/

> Nota: El archivo completo contiene millones de registros. Para el desarrollo y las pruebas iniciales se utiliza un subconjunto representativo de 100,000 registros.

---

## Estructura del proyecto

```text
TC1031.602_A01713780-ANALIZADOR-DE-GENOMAS-SARS-CoV-2/
│
├── main.cpp
├── SecuenciaViral.h
├── Dataset.h
├── Filtros.h
├── Busqueda.h
├── Ordenamiento.h
├── sars_cov2_100000.tsv
└── README.md
```
- main.cpp: contiene la función principal y el menú de interacción con el usuario.
- SecuenciaViral.h: define la clase que representa cada secuencia viral.
- Dataset.h: implementa la carga y visualización de los registros del archivo TSV.
- Filtros.h: contiene los métodos para filtrar secuencias por sus atributos.
- Busqueda.h: implementa los algoritmos de búsqueda por accession.
- Ordenamiento.h: implementa el algoritmo Merge Sort para ordenar las secuencias por longitud.
- sars_cov2_100000.tsv: contiene el subconjunto de datos utilizado para ejecutar y probar el programa.
- README.md: documenta el proyecto, su funcionamiento y las instrucciones de uso.

---

## Estructura del proyecto

El programa permite realizar las siguientes operaciones:

1. Mostrar una cantidad determinada de registros del conjunto de datos.
2. Filtrar secuencias por linaje.
3. Filtrar secuencias por ubicación geográfica.
4. Filtrar secuencias por un intervalo de longitud.
5. Buscar una secuencia por su identificador accession mediante búsqueda secuencial.
6. Ordenar las secuencias por longitud utilizando Merge Sort.

Los filtros generan un vector con las secuencias que cumplen la condición especificada. La operación de ordenamiento trabaja sobre una copia del vector original, por lo que no modifica el orden de los registros almacenados en el objeto Dataset

---

## Complejidad de los algoritmos

La complejidad temporal describe cómo crece el tiempo de ejecución de un algoritmo conforme aumenta la cantidad de registros, representada por (n). La complejidad espacial describe la memoria adicional que requiere.

