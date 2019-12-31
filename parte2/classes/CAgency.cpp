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
    for (auto &h : con->getHabitacoes()) {
        this->ids.emplace_back(h->getID());
    }
}

void CAgency::removeCondominio(Condominio *con) {
    condominios.remove(con);

    for (auto &h : con->getHabitacoes()) {
        for (auto it = ids.begin(); it != ids.end(); it++) {
            if (*it == h->getID()) {
                it = ids.erase(it);
                it--;
            }
        }
    }

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

Condominio *CAgency::findCondominio(string des, string loc) {
    BSTItrIn<Condominio*> it(condominios);
    while (!it.isAtEnd()) {
        if (it.retrieve()->getDesignation() == des && it.retrieve()->getLocation() == loc) {
            return it.retrieve();
        }
        it.advance();
    }
    return nullptr;
}

bool CAgency::findID(string id) {
    for (auto &i : ids) {
        if (i == id) {
            return true;
        }
    }
    return false;
}

void CAgency::writeToFiles() {
    BSTItrIn<Condominio*> it(condominios);
    while (!it.isAtEnd()) {
        it.retrieve()->writeToFiles();
        it.advance();
    }
}

void CAgency::addID(string id) {
    this->ids.emplace_back(id);
}

void CAgency::removeID(string id) {
    for (auto it = ids.begin(); it != ids.end(); it++) {
        if (id == *it) {
            ids.erase(it);
            return;
        }
    }
}


