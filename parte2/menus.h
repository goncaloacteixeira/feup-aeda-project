//
// Created by skidr on 28/12/2019.
//

#ifndef PARTE2_MENUS_H
#define PARTE2_MENUS_H


#include "classes/CAgency.h"
#include "output-formats.h"
#include "classes/utils.h"


string tittleBars(string tittle);


/**
 * @brief First Menu function
 * @return Condominium Agency for a name and VAT given by user
 */
CAgency firstMenu();

/**
 * @param agency Agencia de Gestão de Condominios
 * @return 0 para sair
 * @return 1 para ver condominios
 * @return 2 para adicionar condominios
 * @return 3 para remover condominios
 */
int agencyMenu(CAgency* agency);

/**
 * @param agency Agencia de Gestão de Condominios
 * @return 0 para sair
 * @return 1 para ver um condomínio em especifico
 * @return 2 para voltar atrás
 */
int viewCondos(CAgency* agency);
int addCondo(CAgency* agency);
void removeCondo(CAgency* agency);

Condominio* speficifyCondo(CAgency* agency);





#endif //PARTE2_MENUS_H
