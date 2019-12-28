//
// Created by skidr on 27/12/2019.
//

#ifndef PARTE2_TRANSPORTE_H
#define PARTE2_TRANSPORTE_H

#include <string>
#include <iostream>

using namespace std;

class Transporte {
    string localizacao;             //!< Localização do Ponto de Paragem
    unsigned int distancia;         //!< Distancia do Ponto de Paragem ao Condomínio
    string destino;                 //!< Destino do Ponto de Paragem
    bool active;
public:
    Transporte() : localizacao(""), distancia(0), destino(""), active(false) { };
    Transporte(string loc, unsigned dist, string dest);

    string getLocalization() const;
    unsigned getDistance() const;
    string getDestiny() const;

    void changeDestiny(string dest);
    void changeState(bool state);

    friend ostream& operator<<(ostream& os, Transporte& t1);
    bool operator<(const Transporte &t1) const;
    bool operator==(const Transporte &t1) const;

};


#endif //PARTE2_TRANSPORTE_H
