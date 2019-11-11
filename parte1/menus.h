//
// Created by skidr on 10/11/2019.
//

#ifndef PARTE1_MENUS_H
#define PARTE1_MENUS_H

#include "classes/Condominio.h"
#include <iostream>

using namespace std;

void wait();

int firstMenu();
string filenameMenu();
Condominio newCondominium();

int mainMenu(Condominio *con);

int membersMenu(Condominio *con);
int addConMenu(Condominio *con);
int rmConMenu(Condominio *con);
int sortConMenu(Condominio *con);
int rqServiceMenu(Condominio *con);

void viewHabs(Condominio *con);
void viewAps(Condominio *con);
void viewVivs(Condominio *con);

int addHabMenu(Condominio *con);
int rmHabMenu(Condominio *con);
int assignHab(Condominio *con);
int unassignHab(Condominio *con);
int sortHabMenu(Condominio *con);

void servicesProvided(Condominio *con);
void incomeMenu(Condominio *con);

int exitMenu(Condominio *con);


#endif //PARTE1_MENUS_H
