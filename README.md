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
Proyecto/
│
├── main.cpp
│
├── SecuenciaViral.h
├── Dataset.h
├── Filtros.h
├── Busqueda.h
├── Ordenamiento.h
│
└── data/
    └── sars_cov2_100000.tsv
