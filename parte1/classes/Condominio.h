//
// Created by skidr on 25/10/2019.
//

#ifndef PARTE1_CONDOMINIO_H
#define PARTE1_CONDOMINIO_H

#include "Condomino.h"


class Condominio {
    // static unsigned int current_ap_id;
    // static unsigned int current_vi_id;

    unsigned int numPrestLimpeza;
    vector<Habitacao *> habitacoes;
    vector<Condomino *> condominos;
    vector<Servico *> servicosPrestados;

public:
    Condominio(unsigned int numPrestLimpeza);
    Condominio(string filename);

    float calcReceitas();

    // Métodos GET
    unsigned int getNumPrestLimpeza();
    vector<Servico *> getServicos();

    vector<Habitacao *> getHabitacoes();
    unsigned int getNumHabitacoes();
    void adicionaHabitacao(Habitacao *hab);
    void removeHabitacao(Habitacao *hab);
    void ordernarHab();

    vector<Condomino *> getCondominos();
    unsigned int getNumCondominos();
    void adicionaCondomino(Condomino *con);
    void removeCondomino(Condomino *con);
    void ordenarCond();
};


#endif //PARTE1_CONDOMINIO_H
