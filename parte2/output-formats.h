//
// Created by skidr on 28/12/2019.
//

#ifndef PARTE2_OUTPUT_FORMATS_H
#define PARTE2_OUTPUT_FORMATS_H

#include "classes/CAgency.h"
#include "fort.hpp"

/**
 * @file output-formats.h
 * @brief Funçoes para aprensentar info em forma de tabelas
 *
 * - Vetor de habitaçoes\n
 * - Vetor de condóminos\n
 * - HashTab de antigos condóminos\n
 * - Vetor de antigos condóminos\n
 * - Vetor de transportes (paragens)\n
 * - BST de condominios\n
 * - Vetor de Serviços
 */

string printTable(vector<Habitacao*> habitacoes);
string printTable(vector<Condomino*> condominos);
string printTable(tabHFormerMembers formerMembers);
string printTable(vector<FormerMember> formerMembers);
string printTable(vector<Transporte> transports);
string printTable(BST<Condominio*> condominios);
string printTable(vector<Servico*> servicos);




#endif //PARTE2_OUTPUT_FORMATS_H
