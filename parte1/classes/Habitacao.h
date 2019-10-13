//
// Created by skidr on 12/10/2019.
//

#ifndef PARTE1_HABITACAO_H
#define PARTE1_HABITACAO_H

#include "Morada.h"

class Habitacao {
protected:
    Morada morada;
    float areaHabitacional;
public:
    Habitacao(Morada morada, float areaHabitacional);
    virtual float mensalidade();

    //GET Methods
    string getMorada();
    float getAreaHabitacional();
};

class Apartamento : public Habitacao {
    string tipologia;
    int piso;
public:
    Apartamento(Morada morada, float areaHabitacional, string tipologia, int piso);
    float mensalidade();

    //GET Methods
    string getTipologia();
    int getPiso();

    //SET Methods
    void setTipologia(string tipologia);
    void setPiso(int piso);
};

class Vivenda : public Habitacao {
    string areaExterior;
    bool piscina; // true para sim
public:
    Vivenda(Morada morada, float areaHabitacional, string areaExterior, bool piscina);
    float mensalidade();

    //GET Methods
    string getAreaExterior();
    bool getPiscina();

    //SET Methods
    void setAreaExterior (string areaExterior);
    void setPiscina (bool piscina);
};


#endif //PARTE1_HABITACAO_H
