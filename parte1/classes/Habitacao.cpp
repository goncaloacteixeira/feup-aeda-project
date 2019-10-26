//
// Created by skidr on 12/10/2019.
//

#include "Habitacao.h"

Habitacao::Habitacao(Morada morada, float areaHabitacional) {
    this->morada = morada;
    this->areaHabitacional = areaHabitacional;
    this->ocupado = false;
}

//GET Methods

string Habitacao::getMorada() {
    return morada.getMorada();
}

float Habitacao::getAreaHabitacional() {
    return areaHabitacional;
}

//Apartament Constructor

Apartamento::Apartamento(Morada morada, float areaHabitacional, string tipologia, int piso, const string id) : Habitacao(morada, areaHabitacional), id(id){
    this->tipologia = tipologia;
    this->piso = piso;
}

//GET Methods

string Apartamento::getTipologia() {
    return tipologia;
}

int Apartamento::getPiso() {
    return piso;
}

//Vivenda Constructor

Vivenda::Vivenda(Morada morada, float areaHabitacional, float areaExterior, bool piscina, const string id) : Habitacao(morada, areaHabitacional) , id(id)  {
    this->areaExterior = areaExterior;
    this->piscina = piscina;
}

//GET Methods

float Vivenda::getAreaExterior() {
    return areaExterior;
}

bool Vivenda::getPiscina() {
    return piscina;
}