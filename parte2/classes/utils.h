//
// Created by skidr on 25/12/2019.
//

#ifndef PARTE2_UTILS_H
#define PARTE2_UTILS_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

/**
 * @file utils.h
 * @brief Funções uteis para o projeto geral
 */

/**
 * @brief Função de parsing de strings
 * @param s             string a ser "partida"
 * @param delimiter     string on queremos que s seja partida
 * @return vetor com as partes da string s partidas no delimiter
 */
vector<string> split (string &s, string delimiter);

/**
 * @brief Função para verificar a integridade de um NIF
 * @param nif NIF a ser verificado
 * @return true - NIF tem 9 carateres todos numéricos | false otherwise
 */
bool checkNIF(string nif);


#endif //PARTE2_UTILS_H
