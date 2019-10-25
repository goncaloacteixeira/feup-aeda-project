//
// Created by skidr on 25/10/2019.
//

#include "Condomino.h"
#include <sstream>

Condomino::Condomino(string nome, unsigned int nif) : nome(nome), nif(nif){
    this->habitacoes = {};
    this->servicos = {};
}

string Condomino::getNome() {
    return this->nome;
}

unsigned Condomino::getNIF() {
    return this->nif;
}

int Condomino::getNumHabitacoes() {
    return this->habitacoes.size();
}

vector<Habitacao *> Condomino::getHabitacoes() {
    return habitacoes;
}

vector<Servico *> Condomino::getServicos() {
    return servicos;
}

string Condomino::info() {
    stringstream os;
    os << "Nome: " << this->nome << endl << "NIF: " << this->nif << endl;
    os << "Numero de Habitaçoes: " << this->getNumHabitacoes();
    return os.str();
}

void Condomino::ordenarHabitacoesArea(bool reverse) {
    int i, j;
    for(j = 1; j < habitacoes.size(); j++)    // Start with 1 (not 0)
    {
        Habitacao *temp = habitacoes[j];
        if (reverse) {
            for (i = j - 1; (i >= 0) && (habitacoes[i]->getAreaHabitacional() <
                                         temp->getAreaHabitacional()); i--)   // Smaller values move up
            {
                habitacoes[i + 1] = habitacoes[i];
            }
        }
        else {
            for (i = j - 1; (i >= 0) && (habitacoes[i]->getAreaHabitacional() >
                                         temp->getAreaHabitacional()); i--)   // Higher values move up
            {
                habitacoes[i + 1] = habitacoes[i];
            }
        }
        habitacoes[i+1] = temp;    //Put key into its proper location
    }
}

void Condomino::ordenarHabitacoesMensalidade(bool reverse) {
    int i, j;
    for(j = 1; j < habitacoes.size(); j++)    // Start with 1 (not 0)
    {
        Habitacao *temp = habitacoes[j];
        if (reverse) {
            for (i = j - 1; (i >= 0) && (habitacoes[i]->mensalidade <
                                         temp->mensalidade); i--)   // Smaller values move up
            {
                habitacoes[i + 1] = habitacoes[i];
            }
        }
        else {
            for (i = j - 1; (i >= 0) && (habitacoes[i]->mensalidade >
                                         temp->mensalidade); i--)   // Higher values move up
            {
                habitacoes[i + 1] = habitacoes[i];
            }
        }
        habitacoes[i+1] = temp;    //Put key into its proper location
    }
}



void Condomino::setHabitacoes(vector<Habitacao *> hab) {
    this->habitacoes = hab;
}

void Condomino::adicionaHabitacao(Habitacao *hab) {
    this->habitacoes.push_back(hab);
}

void Condomino::removeHabitacao(Habitacao *hab) {
    for (int i = 0; i < habitacoes.size(); i++) {
        if (habitacoes[i] == hab) {
            habitacoes.erase(habitacoes.begin() + i);
            break;
        }
    }
}

float Condomino::mensalidadeTotal() {
    float mens = 0;
    for (Habitacao *habitacao : habitacoes)
        mens += habitacao->mensalidade;
    return mens;
}
