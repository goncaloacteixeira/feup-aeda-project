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

string Habitacao::info() {
    string out;
    out = "Morada: " + this->getMorada() + "\nArea Habitacional: " + to_string(this->getAreaHabitacional());
    (this->getEstado()) ? out += "\nOcupado\n" : out += "\nLivre\n";
    return out;
}


int Apartamento::ap_current_id = 0;
Apartamento::Apartamento(Morada morada, float areaHabitacional, string tipologia, int piso) : Habitacao(morada, areaHabitacional), id("A" + to_string(ap_current_id)){
    this->tipologia = tipologia;
    this->piso = piso;
    ap_current_id += 1;
}

//GET Methods

string Apartamento::getTipologia() {
    return tipologia;
}

int Apartamento::getPiso() {
    return piso;
}

string Apartamento::getID() {
    return this->id;
}

string Apartamento::info() {
    return Habitacao::info() + "ID: " + this->getID() + "\nTipologia: " + this->getTipologia() + "\nPiso: " + to_string(this->getPiso());
}

vector<string> Apartamento::extraInfo() {
    return {this->tipologia, to_string(this->piso)};
}

int Vivenda::vi_current_id = 0;
Vivenda::Vivenda(Morada morada, float areaHabitacional, float areaExterior, bool piscina) : Habitacao(morada, areaHabitacional) , id("V" + to_string(vi_current_id))  {
    this->areaExterior = areaExterior;
    this->piscina = piscina;
    vi_current_id += 1;
}

//GET Methods

float Vivenda::getAreaExterior() {
    return areaExterior;
}

bool Vivenda::getPiscina() {
    return piscina;
}

string Vivenda::getID() {
    return this->id;
}

string Vivenda::info() {
    return Habitacao::info() + "ID: " + this->getID() + "\nPiscina: " + to_string(this->getPiscina()) + " Area Exterior: " + to_string(this->getAreaExterior());
}

vector<string> Vivenda::extraInfo() {
    return {to_string(this->areaExterior), to_string(this->piscina)};
}
