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
    os << "Name: " << dt.name << endl;
    os << "VAT: " << dt.nif << endl;
    return os;
}

vector<Condominio *> CAgency::getCondominios(int nHabsMax) {
    vector<Condominio*> temp;
    BSTItrIn<Condominio*> it(condominios);

    while (!it.isAtEnd()) {
        if (it.retrieve()->getNumHabitacoes() <= nHabsMax) {
            temp.emplace_back(it.retrieve());
        }
        it.advance();
    }
    return temp;
}


