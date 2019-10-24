//
// Created by skidr on 12/10/2019.
//

#include "Servico.h"

Servico::Servico(float custo, string prestador, string servico) {
    this->custo = custo;
    this->prestador = prestador;
    this->servico = servico;
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





