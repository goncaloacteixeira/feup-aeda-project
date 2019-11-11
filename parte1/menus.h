//
// Created by skidr on 10/11/2019.
//

#ifndef PARTE1_MENUS_H
#define PARTE1_MENUS_H

#include "classes/Condominio.h"
#include <iostream>

using namespace std;

void wait();

int mainMenu();
string filenameMenu();
Condominio newCondominium();

int condominiumMenu(Condominio *con);

int membersMenu(Condominio *con);
void addConMenu(Condominio *con);
void rmConMenu(Condominio *con);
int sortConMenu(Condominio *con);
int rqServiceMenu(Condominio *con);


void addHabMenu(Condominio *con);
void rmHabMenu(Condominio *con);
void assignHab(Condominio *con);


#endif //PARTE1_MENUS_H
