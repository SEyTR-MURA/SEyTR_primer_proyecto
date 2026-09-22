# CMakeLists.txt de proyecto. Es el fichero por el que empieza CMake.
# cmake_minimum_required() tiene que ser la primera ORDEN del fichero: los
# comentarios de encima no cuentan. La version es la que muestra la plantilla de
# proyecto de la documentacion del SDK del curso.
cmake_minimum_required(VERSION 3.22)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(primer_proyecto)
