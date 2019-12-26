cmake_minimum_required(VERSION 3.10)
project(generate-data)

set(CMAKE_CXX_STANDARD 14)

add_executable(generate-data main.cpp classes/Morada.cpp classes/Morada.h classes/Habitacao.cpp classes/Habitacao.h
        classes/Servico.cpp classes/Servico.h classes/Condomino.cpp classes/Condomino.h
        classes/Condominio.cpp classes/Condominio.h classes/utils.h
        fort.c fort.h fort.hpp)
