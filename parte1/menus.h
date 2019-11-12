//
// Created by skidr on 10/11/2019.
//

#ifndef PARTE1_MENUS_H
#define PARTE1_MENUS_H

/**
 * @file menus.h
 * @brief Funções documentadas para menus
 */

#include "classes/Condominio.h"
#include <iostream>

using namespace std;

/**
 * @brief Função que espera que o utilizador pressione ENTER
 */
void wait();

/**
 * @brief Menu inicial do programa
 * @return Opção selecionada pelo utilizador
 */
int firstMenu();

/**
 * @brief Menu para inicialização do programa a partir de ficheiros de texto
 * @return Opção selecionada pelo utilizador
 */
string filenameMenu();

/**
 * @brief Menu para inicialização do programa a partir do zero
 * @return Objeto Condominio criado
 */
Condominio newCondominium();

/* --- --- */

/**
 * @brief Menu principal do programa
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int mainMenu(Condominio *con);

/**
 * @brief Menu dos Condóminos
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int membersMenu(Condominio *con);

/**
 * @brief Adicionar um Condómino
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int addConMenu(Condominio *con);

/**
 * @brief Remover um condómino
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int rmConMenu(Condominio *con);

/**
 * @brief Ordenar um condómino
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int sortConMenu(Condominio *con);

/**
 * @brief Solicitar um serviço
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int rqServiceMenu(Condominio *con);


/* --- --- */

/**
 * @brief Ver todas as habitações
 * @param con Condominio atual
 */
void viewHabs(Condominio *con);

/**
 * @brief Ver todos os apartamentos
 * @param con Condominio atual
 */
void viewAps(Condominio *con);

/**
 * @brief Ver todas as vivendas
 * @param con Condominio atual
 */
void viewVivs(Condominio *con);


/* --- --- */

/**
 * @brief Adicionar uma habitação
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int addHabMenu(Condominio *con);

/**
 * @brief Remover uma habitação
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int rmHabMenu(Condominio *con);

/**
 * @brief Atribuir uma habitação que não esteja ocupada
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int assignHab(Condominio *con);

/**
 * @brief Desassociar uma habitação
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int unassignHab(Condominio *con);

/**
 * @brief Ordenar habitações
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int sortHabMenu(Condominio *con);

/* --- --- */

/**
 * @brief Serviços prestados
 * @param con Condominio atual
 */
void servicesProvided(Condominio *con);

/**
 * @brief Receitas do condomínio
 * @param con Condominio atual
 */
void incomeMenu(Condominio *con);

void searchMember(Condominio *con);
void searchHabitation(Condominio *con);


/**
 * @brief Menu para saída do programa
 * @param con Condominio atual
 * @return Opção selecionada pelo utilizador
 */
int exitMenu(Condominio *con);


#endif //PARTE1_MENUS_H
