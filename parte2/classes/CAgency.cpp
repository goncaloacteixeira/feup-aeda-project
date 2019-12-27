//
// Created by skidr on 27/12/2019.
//

#include "CAgency.h"

int CAgency::addCondominios(const vector<Condominio *>& cons) {
    int count = 0;
    for (auto &i : cons) {
        condominios.insert(i);
        count++;
    }
    return count;
}

void CAgency::addCondominio(Condominio *con) {
    condominios.insert(con);
}

void CAgency::removeCondominio(Condominio *con) {
    condominios.remove(con);
}

BST<Condominio *> CAgency::getCondominios() {
    return condominios;
}

ostream& operator<<(ostream &os, const CAgency &dt) {
    BSTItrLevel<Condominio*> it(dt.condominios);
    while (!it.isAtEnd()) {
        os << it.retrieve()->getDesignation() << " : " << it.retrieve()->getNumHabitacoes() << endl;
        it.advance();
    }
}


