# Práctica MPI -- Programación con Paso de Mensajes

Este repositorio contiene el desarrollo completo de una práctica de
introducción a la programación paralela mediante MPI (Message Passing
Interface).

El objetivo general de la práctica es comprender el modelo de paso de
mensajes, analizar el coste de comunicación frente al coste de
computación y aplicar patrones básicos de paralelismo distribuido.

------------------------------------------------------------------------

## Estructura del repositorio

├── 1 → Programa básico "Hello World" en MPI\
├── 2 → Comunicación punto a punto maestro-esclavo\
├── 3 → Envío de mensajes desde esclavos al maestro\
├── 4 → Circulación de un token en topología en anillo\
├── 5 → Medición experimental del coste de comunicación (Ping-Pong)\
│ └── Incluye cuaderno Jupyter para regresión lineal\
└── 6 → Distribución y procesamiento paralelo de un vector

Cada directorio corresponde a uno de los apartados planteados en la
práctica.

------------------------------------------------------------------------

## Objetivos trabajados

-   Inicialización y finalización del entorno MPI.
-   Identificación de procesos y comunicadores.
-   Comunicación punto a punto (MPI_Send / MPI_Recv).
-   Patrones de comunicación maestro-esclavo.
-   Implementación de topologías lógicas (anillo).
-   Medición experimental de latencia y ancho de banda.
-   Ajuste del modelo lineal de comunicación T(n)=α+βn.
-   Paralelismo de datos mediante MPI_Scatter y MPI_Gather.

------------------------------------------------------------------------

## Análisis de rendimiento

En el apartado 5 se realiza un estudio experimental del coste de:

-   Operaciones aritméticas puras (CPU).
-   Comunicaciones punto a punto entre procesos (Ping-Pong).

Se incluye un cuaderno Jupyter (regresion-lineal.ipynb) donde se
realiza:

-   Ajuste lineal del modelo teórico de comunicación.
-   Representación gráfica de los datos experimentales.
-   Obtención de los parámetros de latencia y coste por dato.

------------------------------------------------------------------------

## Requisitos

-   Implementación de MPI (por ejemplo, OpenMPI)
-   Compilador mpicc
-   Python 3 (para el cuaderno Jupyter del apartado 5)

------------------------------------------------------------------------

## Ejecución general

Compilación:

mpicc archivo.c -o ejecutable

Ejecución:

mpirun -np `<n_procesos>` ./ejecutable

------------------------------------------------------------------------

## Conclusión

La práctica permite comprender los fundamentos del modelo de paso de
mensajes, experimentar con distintos patrones de comunicación y analizar
empíricamente el coste de comunicar frente al coste de calcular,
principio esencial en el diseño eficiente de aplicaciones paralelas.
