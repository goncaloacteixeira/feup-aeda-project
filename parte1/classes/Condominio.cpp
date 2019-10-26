//
// Created by skidr on 25/10/2019.
//

#include "Condominio.h"
#include <iostream>

Condominio::Condominio(unsigned int numPrestLimpeza) : numPrestLimpeza(numPrestLimpeza) {
    this->habitacoes = {};
    this->condominos = {};

    // current_ap_id = 0;
    // current_vi_id = 0;
}

Condominio::Condominio(string filename) {
    filename = "../" + filename;
    ifstream condominio;
    string line;
    int i = 0;

    // current_ap_id = 0;
    // current_vi_id = 0;

    string condominosFileName;
    int numHab;

    condominio.open(filename);
    if (condominio.is_open())
    {
        while (getline(condominio, line) && i < 3) {
            if (i == 0)
                this->numPrestLimpeza = stoi(line);
            else if (i == 1)
                condominosFileName = line;
            else if (i == 2)
                numHab = stoi(line);
            i++;
        }
    }
    condominio.close();
    if (numHab == 0)
        this->habitacoes = {};
    else
    {
        vector< vector<string>> info;
        condominio.open(filename);
        if (condominio.is_open())
        {
            int ctr = 0;
            string line1;
            for (int i = 0; i < numHab; i++)
            {
                vector<string> hab;
                while (getline(condominio, line1))
                {
                    if (ctr >= 3)
                    {
                        if (line1 != "::::::::::\r")
                            hab.push_back(line1);
                        else
                            break;
                    }
                    ctr++;
                }
                info.push_back(hab);
            }
        }

        for (int i = 0; i < numHab; i++)
        {
            Morada novaMorada(info[i][2]);
            if (info[i][0].at(0) == 'A')
            {
                Apartamento *ap = new Apartamento(novaMorada, stof(info[i][3]), info[i][4], stoi(info[i][5]), info[i][0]);
                if (info[i][1] == "true")
                    ap->setEstado(true);
                else
                    ap->setEstado(false);
                habitacoes.push_back(ap);
                // this->current_ap_id = stoi(ap->getID().erase(0,1));
            }
            if (info[i][0][0] == 'V')
            {
                bool piscina;
                (info[i][5] == "true") ? piscina = true : piscina = false;
                Vivenda *vi = new Vivenda(novaMorada, stof(info[i][3]), stof(info[i][4]), piscina, info[i][0]);

                if (info[i][1] == "true")
                    vi->setEstado(true);
                else
                    vi->setEstado(false);
                habitacoes.push_back(vi);
                // this->current_vi_id = stoi(vi->getID().erase(0,1));
            }
        }
    }
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
