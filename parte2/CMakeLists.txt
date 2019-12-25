cmake_minimum_required(VERSION 3.10)
project(parte2)

set(CMAKE_CXX_STANDARD 14)

add_executable(parte2 main.cpp classes/Morada.cpp classes/Morada.h classes/Habitacao.cpp classes/Habitacao.h
        classes/Servico.cpp classes/Servico.h classes/Condomino.cpp classes/Condomino.h
        classes/Condominio.cpp classes/Condominio.h classes/utils.h menus.cpp menus.h
        fort.c fort.h fort.hpp)
