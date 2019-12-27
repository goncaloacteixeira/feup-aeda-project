//
// Created by skidr on 27/12/2019.
//

#ifndef PARTE2_CAGENCY_H
#define PARTE2_CAGENCY_H

#include "bst.h"
#include "Condominio.h"

class CAgency {
    string name;
    unsigned nif;

    BST<Condominio*> condominios;

public:
    CAgency(string name, unsigned int nif) :
        condominios(new Condominio("","",0)),
        name(name), nif(nif) { };

    int addCondominios(const vector<Condominio*>& cons);
    void addCondominio(Condominio* con);
    void removeCondominio(Condominio* con);

    friend ostream& operator<<(ostream& os, const CAgency& dt);

    BST<Condominio*> getCondominios();

};


#endif //PARTE2_CAGENCY_H
