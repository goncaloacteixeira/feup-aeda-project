//
// Created by skidr on 25/10/2019.
//

#include "Condominio.h"

Condominio::Condominio(unsigned int numPrestLimpeza) : numPrestLimpeza(numPrestLimpeza) {
    this->habitacoes = {};
    this->condominos = {};

    current_ap_id = 0;
    current_vi_id = 0;
}

float Condominio::calcReceitas() {
    float rec = 0;
    if (this->getNumHabitacoes() != 0) {
        for (int i = 0; i < this->getCondominos().size(); i++)
            rec += this->getCondominos()[i]->mensalidadeTotal();
    }
    return rec;
}

unsigned int Condominio::getNumPrestLimpeza() {
    return this->numPrestLimpeza;
}

vector<Servico *> Condominio::getServicos() {
    return this->servicosPrestados;
}

vector<Habitacao *> Condominio::getHabitacoes() {
    return this->habitacoes;
}

unsigned int Condominio::getNumHabitacoes() {
    return this->habitacoes.size();
}

void Condominio::adicionaHabitacao(Habitacao *hab) {
    this->habitacoes.push_back(hab);
}

void Condominio::removeHabitacao(Habitacao *hab) {
    for (int i = 0; i < habitacoes.size(); i++) {
        if (habitacoes[i] == hab) {
            habitacoes.erase(habitacoes.begin() + i);
            break;
        }
    }
}

// a implementar
void Condominio::ordernarHab() {
    return;
}

vector<Condomino *> Condominio::getCondominos() {
    return condominos;
}

unsigned int Condominio::getNumCondominos() {
    return condominos.size();
}

void Condominio::adicionaCondomino(Condomino *con) {
    this->condominos.push_back(con);
}

void Condominio::removeCondomino(Condomino *con) {
    for (int i = 0; i < condominos.size(); i++) {
        if (condominos[i] == con) {
            condominos.erase(condominos.begin() + i);
            break;
        }
    }
}

void Condominio::ordenarCond() {
    int i, j;
    for (j = 1; j < condominos.size(); j++)    // Start with 1 (not 0)
    {
        Condomino *temp = condominos[j];

        for (i = j - 1; (i >= 0) && (condominos[i]->mensalidadeTotal() <
                                     temp->mensalidadeTotal()); i--)   // Smaller values move up
        {
            condominos[i + 1] = condominos[i];
        }
    }
}
