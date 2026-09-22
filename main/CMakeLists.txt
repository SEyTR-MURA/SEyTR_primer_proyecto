# CMakeLists.txt de componente. Registra las fuentes y las cabeceras publicas.
# Si anades un fichero .c, anadelo tambien a SRCS.
idf_component_register(SRCS "primer_proyecto.c"
                       INCLUDE_DIRS ".")
