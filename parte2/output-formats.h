//
// Created by skidr on 28/12/2019.
//

#ifndef PARTE2_OUTPUT_FORMATS_H
#define PARTE2_OUTPUT_FORMATS_H

#include "classes/CAgency.h"
#include "fort.hpp"


string printTable(vector<Habitacao*> habitacoes);
string printTable(vector<Condomino*> condominos);
string printTable(tabHFormerMembers formerMembers);
string printTable(vector<FormerMember> formerMembers);
string printTable(vector<Transporte> transports);
string printTable(BST<Condominio*> condominios);
string printTable(vector<Servico*> servicos);




#endif //PARTE2_OUTPUT_FORMATS_H
