//
// Created by skidr on 27/12/2019.
//

#include "Transporte.h"

Transporte::Transporte(string loc, unsigned dist, string dest) : localizacao(loc), distancia(dist), destino(dest) {
    // do nothing
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

void Transporte::changeDestiny(const string dest) {
    this->destino = dest;
}

ostream &operator<<(ostream &os, Transporte &t1) {
    os << "Location: " << t1.localizacao << endl;
    os << "Distance: " << t1.distancia << endl;
    os << "Destiny: " << t1.destino << endl;
}

