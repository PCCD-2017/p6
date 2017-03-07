cmake_minimum_required (VERSION 2.6)
project (p6)
add_executable(ej1 ej1.c)
add_executable(ej2 ej2.c)
add_executable(ej3 ej3.c)
add_executable(ej4 ej4.c)
add_executable(ej5 ej5.c)
add_executable(filosofo filosofo.c)
add_executable(inic_filosofos inic_filosofos.c)
add_executable(filosofo_mod filosofo_mod.c)
add_executable(inic_filosofos_mod inic_filosofos_mod.c)

set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_SOURCE_DIR}/out
)