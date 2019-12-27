cmake_minimum_required(VERSION 3.15)
project(parte2)

set(CMAKE_CXX_STANDARD 14)

add_executable(parte2 main.cpp classes/Servico.cpp classes/Servico.h classes/Habitacao.cpp classes/Habitacao.h classes/Condomino.cpp classes/Condomino.h classes/Condominio.cpp classes/Condominio.h classes/utils.cpp classes/utils.h classes/bst.h classes/CAgency.cpp classes/CAgency.h)