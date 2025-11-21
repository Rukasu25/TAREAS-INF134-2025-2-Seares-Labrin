# TAREA-3-SANSABOOK

Tarea 3 de Estructuras de Datos USM

*__Estudiante 1:__ Lukas Labrín
    __Rol:__ 202473624-8
    __OS utilizado:__ Windows 11
    __Versión C/C++ VS Extension:__ 1.28.3
    __Versión compilador:__ 13.3.0

*__Estudiante 2:__ Patricio Seares
    __Rol:__ 202473636-1
    __OS utilizado:__ GNU/Linux Mint
    __Versión C/C++ VS Extension:__ 1.28.3
    __Versión compilador:__ 13.3.0


Para esta tarea se utilizó el compilador g++ usando la terminal de Ubuntu y el WSL Debian. El proyecto se trata de trabajar con grafos no dirigidos simulando un sistema de recomendacion de amistades tipo Facebook

La compilación, ejecución y borrado se realizará mediante un archivo de tipo makefile.

# notas extra:
Se implementó en el repositorio .gitattributes para evitar este warning "This diff contains a change in line endings from 'LF' to 'CRLF'."
Tambien se agregó un archivo "comu.txt" que fue utilizado para probar si las funciones de comunidades y puentes funcionaban correctamente, para implementarla en el codigo, simplemente reescriba "string archivo=__"datos.txt"__;" a "string archivo=__"comu.txt"__;" (linea 565)