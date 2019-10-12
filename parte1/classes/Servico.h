//
// Created by skidr on 12/10/2019.
//

#ifndef PARTE1_SERVICO_H
#define PARTE1_SERVICO_H

#include <string>

using namespace std;

enum tipo_servico {
    limpeza,
    canalizacao,
    pintura,
    arrumadorCarros,
    babysitting,
    cabeleireiro,
    petsitter,
    jardineiro,
    spa,
    cinema,
    lavagem_carros,
    seguranca,
    cozinheiro
};

class Servico {
    float custo;
    string prestador;
    string servico;
public:
    Servico(const float custo, string prestador, enum tipo_servico servico);
    string getTipo();
    float getCusto();
    string getPrestador();
};


#endif //PARTE1_SERVICO_H
