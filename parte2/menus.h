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
 * @brief Menu da Agencia (Main Menu)
 * @param agency Agencia de Gestão de Condominios
 * @return 0 para sair
 * @return 1 para ver condominios
 * @return 2 para adicionar condominios
 * @return 3 para remover condominios
 */
int agencyMenu(CAgency* agency);

/**
 * @brief Menu Visualização de Condominios
 * @param agency Agencia de Gestão de Condominios
 * @return 0 para sair
 * @return 1 para ver um condomínio em especifico
 * @return 2 para voltar atrás
 */
int viewCondos(CAgency* agency);

/**
 * @brief Menu adicionar um condomínio
 * @param agency Agencia de Gestão de Condominios
 * @return 0 para sair
 * @return 1 para adicionar condominio 'from scratch'
 * @return 2 para adicionar condominio a partir de um ficheiro
 * @return 3 para voltar atrás
 */
int addCondo(CAgency* agency);

/**
 * @brief Menu remover um condomínio
 * @param agency Agencia de Gestão de Condominios
 */
void removeCondo(CAgency* agency);

/**
 * @brief Menu para especificar um condominio
 * @param agency Agencia de Gestão de Condominios
 * @return apontador para o condominio especificado pelo utilizador ou nullptr
 */
Condominio* speficifyCondo(CAgency* agency);


// --- MENUS PARA CONDOMINIOS

/**
 * @brief Menu para gestão de um condomínio especifico
 * @param cond Condominio especificado pelo utilizador
 * @return 0 para sair
 * @return 1 para entrar no menu dos condóminos
 * @return 2 para entrar no menu das habitações
 * @return 3 para entrar no menu dos serviços prestados
 * @return 4 para vizualizar o 'revenue' do condomínio
 * @return 5 para voltar atrás
 */
int condoMenu();

/**
 * @brief Menu para gestão dos condóminos relativos a um condominio especifico
 * @param cond Condominio especificado pelo utilizador
 * @return 0 para sair
 * @return 1 para adicionar um condómino
 * @return 2 para remover um membro
 * @return 3 para ordenar condóminos
 * @return 4 para requisitar um servico para um condómino em especifico
 * @return 5 para voltar atrás
 */
int membersMenu(Condominio* cond);

/**
 * @breif Menu para adicionar um condómino a um condominio especifico
 * @param cond Condominio especificado pelo utilizador
 */
void addMemberMenu(Condominio* cond);

/**
 * @breif Menu para remover um condómino de um condominio especifico
 * @param cond Condominio especificado pelo utilizador
 */
void removeMemberMenu(Condominio* cond);
void sortMembersMenu(Condominio* cond);
void rqService(Condominio* cond);


#endif //PARTE2_MENUS_H
