//
// Created by skidr on 27/12/2019.
//

#include "Transporte.h"

#include <utility>

Transporte::Transporte(string loc, unsigned dist, string dest) : localizacao(std::move(loc)), distancia(dist), destino(std::move(dest)) {
    this->active = false;
}

string Transporte::getLocalization() const {
    return this->localizacao;
}

unsigned Transporte::getDistance() const {
    return distancia;
}

string Transporte::getDestiny() const {
    return destino;
}

void Transporte::changeDestiny(string dest) {
    this->destino = std::move(dest);
}

ostream &operator<<(ostream &os, Transporte &t1) {
    os << "Location: " << t1.localizacao << endl;
    os << "Distance: " << t1.distancia << endl;
    os << "Destiny: " << t1.destino << endl;
}

bool Transporte::operator<(const Transporte &t1) const  {
    return this->distancia > t1.distancia;
}

bool Transporte::operator==(const Transporte &t1) const {
    return this->distancia == t1.distancia && this->localizacao == t1.localizacao && this->destino == t1.destino;
}

void Transporte::changeState(bool state) {
    this->active = state;
}

