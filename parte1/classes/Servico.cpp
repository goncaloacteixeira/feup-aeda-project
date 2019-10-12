//
// Created by skidr on 12/10/2019.
//

#include "Servico.h"

Servico::Servico(float custo, string prestador, enum tipo_servico servico) {
    this->custo = custo;
    this->prestador = prestador;

    switch (servico)
    {
        case limpeza:
            this->servico = "limpeza";
        case canalizacao:
            this->servico = "canalização";
        case pintura:
            this->servico = "pintura";
        case arrumadorCarros:
            this->servico = "arrumador de carros";
        case babysitting:
            this->servico = "babysitting";
        case cabeleireiro:
            this->servico = "cabeleireiro";
        case petsitter:
            this->servico = "petsitter";
        case jardineiro:
            this->servico = "jardineiro";
        case spa:
            this->servico = "spa";
        case cinema:
            this->servico = "cinema";
        case lavagem_carros:
            this->servico = "lavagem de carros";
        case seguranca:
            this->servico = "segurança";
        case cozinheiro:
            this->servico = "cozinheiro";
        default:
            this->servico = "unknown";
    }
}

string Servico::getTipo() {
    return servico;
}

float Servico::getCusto() {
    return custo;
}

string Servico::getPrestador() {
    return prestador;
}





