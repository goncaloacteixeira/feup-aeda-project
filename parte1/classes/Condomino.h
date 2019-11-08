//
// Created by skidr on 25/10/2019.
//

#ifndef PARTE1_CONDOMINO_H
#define PARTE1_CONDOMINO_H

#include "Habitacao.h"
#include "Servico.h"
#include <fstream>

class Condomino {
    const string nome;
    const unsigned int nif;
    vector<Habitacao *> habitacoes;
    vector<Servico *> servicos;
public:
    Condomino(string nome, unsigned int nif);

    // Métodos GET
    string getNome();
    unsigned int getNIF();
    int getNumHabitacoes();
    vector<Habitacao *> getHabitacoes();
    vector<Servico *> getServicos();

    void adicionaHabitacao(Habitacao *hab);
    void removeHabitacao(Habitacao *hab);
    void adicionaServico(Servico *serv);

    string info();

    void ordenarHabitacoesArea(bool reverse);           // true -> area maior para area menor
    void ordenarHabitacoesMensalidade(bool reverse);    // true -> mensalidade maior para mensalidade menor

    float mensalidadeTotal();

    // testing functions
    void setHabitacoes(vector<Habitacao* > hab);
};

// Exception Classes

class NoSuchHabitation {
    string id;
public:
    NoSuchHabitation(string id) { this->id = id; }
    string getID() { return this->id; }
};
class NoSuchCondomino {
    unsigned int nif;
public:
    NoSuchCondomino(unsigned int nif) { this->nif = nif; }
    unsigned int getNIF() { return this->nif; }
};
class NoSuchService {
public:
    NoSuchService() {};
};







#endif //PARTE1_CONDOMINO_H
