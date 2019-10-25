cmake_minimum_required(VERSION 3.10)
project(parte1)

set(CMAKE_CXX_STANDARD 14)

add_executable(parte1 main.cpp classes/Morada.cpp classes/Morada.h classes/Habitacao.cpp classes/Habitacao.h classes/Servico.cpp classes/Servico.h classes/Condomino.cpp classes/Condomino.h classes/Condominio.cpp classes/Condominio.h)
