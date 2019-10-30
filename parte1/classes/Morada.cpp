//
// Created by skidr on 12/10/2019.
//

#include "Morada.h"
//Constructor

Morada::Morada() {
    this->rua = "Rua Default";
    this->localidade = "Localidade Default";
    this->numero = 0;
    this->codPostal = {0,0};
}

Morada::Morada(string rua, string localidade, unsigned int numero, vector<int> codPostal) {
    this->rua = rua;
    this->localidade = localidade;
    this->numero = numero;
    this-> codPostal = codPostal;
}

#include "utils.h"

void vecStrtoInt(vector<string> &vec, vector<int> *out)
{
    for (string elem : vec)
    {
        out->push_back(stoi(elem));
    }
}

Morada::Morada(string morada) {
    vector<string> vecMorada = split(morada, ", ");
    this->rua = vecMorada[0];
    this->localidade = vecMorada[1];
    stringstream os(vecMorada[2]);
    os >> this->numero;

    this->codPostal = {};
    vector<string> codVec = split(vecMorada[3], "-");
    vecStrtoInt(codVec, &this->codPostal);
}

//GET Methods

string Morada::getRua() {
    return rua;
}

string Morada::getLocalidade() {
    return localidade;
}

unsigned int Morada::getNumero() {
    return numero;
}

vector<int> Morada::getCodpostal() {
    return codPostal;
}

string Morada::getMorada() {
    string res;
    res = this->getRua() + ", " + to_string(this->getNumero()) + ", " + this->getLocalidade() + ", " + to_string(this->getCodpostal()[0]) + "-" + to_string(this->getCodpostal()[1]);
    return res;
}

//SET Methods

void Morada::setRua(string rua){
    this->rua = rua;
}

void Morada::setLocalidade(string localidade) {
    this->localidade = localidade;
}

void Morada::setNumero(unsigned int numero) {
    this->numero = numero;
}

void Morada::setCodpostal(vector<int> codPostal) {
    this->codPostal = codPostal;
}
