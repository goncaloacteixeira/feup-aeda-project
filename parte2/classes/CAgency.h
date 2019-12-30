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
    vector<string> ids;

    BST<Condominio*> condominios;
public:
    CAgency(string name, unsigned int nif) :
        condominios(new Condominio("","",0)),
        name(name), nif(nif) { ids = {}; };

    int addCondominios(const vector<Condominio*>& cons);
    void addCondominio(Condominio* con);
    void removeCondominio(Condominio* con);

    bool findID(string id);

    vector<Condominio*> getCondominios(int nHabsMax);

    Condominio* findCondominio(string des, string loc);

    friend ostream& operator<<(ostream& os, const CAgency& dt);

    BST<Condominio*> getCondominios();

    void writeToFiles();

};


#endif //PARTE2_CAGENCY_H
