//
// Created by skidr on 25/12/2019.
//

#include "Condominio.h"
#include <chrono>
#include "utils.h"
#include <iostream>

set<string> Condominio::prestLimpeza = {};

Condominio::Condominio(string designation, string location, unsigned int numPrestLimpeza) :
    designation(designation), location(location), numPrestLimpeza(numPrestLimpeza) {

    this->condominos = {};
    this->habitacoes = {};
}

Condominio::Condominio(string filename) {
    auto start = chrono::steady_clock::now();

    filename = "../" + filename;
    ifstream condominio;
    string line;
    int i = 0;

    string condominosFileName;
    int numHab;

    condominio.open(filename);
    if (condominio.is_open()) {
        while (getline(condominio, line) && i < 5) {
            /**
             * line 0 -> designation
             * line 1 -> location
             * line 2 -> numPrestLimpeza
             * line 3 -> filename condominos
             * line 4 -> numHab
             */

            if (i == 0)
                this->designation = line;
            else if (i == 1)
                this->location = line;
            else if (i == 2)
                this->numPrestLimpeza = stoi(line);
            else if (i == 3)
                condominosFileName = line;
            else if (i == 4)
                numHab = stoi(line);
            i++;
        }
    }
    condominio.close();
    if (numHab == 0)
        this->habitacoes = {};
    else {
        vector<vector<string>> info;
        condominio.open(filename);
        if (condominio.is_open()) {
            int ctr = 0;
            string line1;
            for (int i = 0; i < numHab; i++) {
                vector<string> hab;
                while (getline(condominio, line1)) {
                    if (ctr >= 3) {
                        if (line1 != "::::::::::")
                            hab.push_back(line1);
                        else
                            break;
                    }
                    ctr++;
                }
                info.push_back(hab);
            }
            condominio.close();
        }


        for (int i = 0; i < numHab; i++) {
            if (info[i][0][0] == 'A') {
                Apartamento *ap = new Apartamento(info[i][2], stof(info[i][3]), info[i][4],stoi(info[i][5]), stof(info[i][6]));

                ap->setEstado(info[i][1] == "1");
                habitacoes.push_back(ap);
            }
            if (info[i][0][0] == 'V') {
                bool piscina;
                piscina = info[i][5] == "1";
                Vivenda *vi = new Vivenda(info[i][2], stof(info[i][3]), stof(info[i][4]), piscina, stof(info[i][6]));

                vi->setEstado(info[i][1] == "1");
                habitacoes.push_back(vi);
            }
        }
        info.clear();
    }

    // Condominos Read Snippet Code
    this->condominos = {};

    condominosFileName = "../" + condominosFileName;

    ifstream condominos;
    condominos.open(condominosFileName);

    int numCondominos = 0;

    if (condominos.is_open())
    {
        string l;
        getline(condominos, l);
        numCondominos = stoi(l);
        condominos.close();
    }

    vector<vector<string> > info;
    if (numCondominos != 0)
    {
        condominos.open(condominosFileName);
        if (condominos.is_open())
        {
            int ctr = 0;
            string line1;
            for (int i = 0; i < numCondominos; i++) {
                vector<string> con;
                while (getline(condominos, line1)) {
                    if (ctr >= 1) {
                        if (line1 != "::::::::::")
                            con.push_back(line1);
                        else
                            break;
                    }
                    ctr++;
                }
                info.push_back(con);
            }
            condominos.close();
        }
    }

    if (numCondominos != 0) {
        for (int i = 0; i < numCondominos; i++) {
            Condomino *c = new Condomino(info[i][0], stoi(info[i][1]));
            int numHabs = stoi(info[i][2]);
            if (numHabs != 0) {
                for (int j = 0; j < numHabs; j++)
                    c->adicionaHabitacao(findHab(info[i][3 + j]));
            }

            int numServ = stoi(info[i][3 + numHabs]);
            if (numServ != 0) {
                for (int j = 0; j < numServ; j++) {
                    vector<string> servico = split(info[i][4 + numHabs + j], " : ");
                    Servico *serv = new Servico(stof(servico[1]), servico[2], servico[0]);
                    if (serv->getTipo() == "Limpeza" || serv->getTipo() == "Cleaning")
                        prestLimpeza.insert(serv->getPrestador());
                    c->adicionaServico(serv);
                    this->servicosPrestados.push_back(serv);
                }
            }
            this->condominos.push_back(c);
        }
    }

    auto end = chrono::steady_clock::now();
    cout << "The reading took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";

}

void Condominio::writeToFiles(string condominioFilename, string condominosFilename) {
    auto start = chrono::steady_clock::now();

    condominioFilename = "../" + condominioFilename;

    fstream condominio(condominioFilename, std::ofstream::out | std::ofstream::trunc);
    condominio << this->designation << endl;
    condominio << this->location << endl;
    condominio << this->numPrestLimpeza << endl;
    condominio << condominosFilename << endl;
    condominio << this->getNumHabitacoes() << endl;
    if (this->getNumHabitacoes() != 0) {
        for (int i = 0; i < this->getNumHabitacoes(); i++)
        {
            condominio << this->habitacoes[i]->getID() << endl;
            condominio << this->habitacoes[i]->getEstado() << endl;
            condominio << this->habitacoes[i]->getMorada() << endl;
            condominio << this->habitacoes[i]->getAreaHabitacional() << endl;
            condominio << this->habitacoes[i]->extraInfo()[0] << endl;
            condominio << this->habitacoes[i]->extraInfo()[1] << endl;
            condominio << this->habitacoes[i]->mensalidade;
            if (i != this->getNumHabitacoes() - 1)
                condominio << "\n::::::::::\n";
        }
    }
    condominio.close();

    condominosFilename = "../" + condominosFilename;

    fstream cond(condominosFilename, std::ofstream::out | std::ofstream::trunc);
    cond << this->getNumCondominos() << endl;
    if (this->getNumCondominos() != 0)
    {
        for (int i = 0; i < this->getNumCondominos(); i++)
        {
            cond << this->condominos[i]->getNome() << endl;
            cond << this->condominos[i]->getNIF() << endl;
            cond << this->condominos[i]->getNumHabitacoes() << endl;
            if (this->condominos[i]->getNumHabitacoes() != 0)
            {
                for (int j = 0; j < this->condominos[i]->getNumHabitacoes() ; j++)
                    cond << this->condominos[i]->getHabitacoes()[j]->getID() << endl;
            }
            cond << this->condominos[i]->getServicos().size();
            if (this->condominos[i]->getServicos().size() != 0)
            {
                for (int j = 0; j < this->condominos[i]->getServicos().size() ; j++)
                    cond << endl << this->condominos[i]->getServicos()[j]->getTipo() << " : " << this->condominos[i]->getServicos()[j]->getCusto() << " : " << this->condominos[i]->getServicos()[j]->getPrestador();
            }
            if (i != this->getNumCondominos() - 1)
                cond << "\n::::::::::\n";
        }
    }
    auto end = chrono::steady_clock::now();
    cout << "The writing took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";
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

void Condominio::ordernarHab(string protocol) {
    if (protocol == "area-ascending") {
        for (unsigned int j = habitacoes.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (habitacoes[i + 1]->getAreaHabitacional() < habitacoes[i]->getAreaHabitacional()) {
                    swap(habitacoes[i], habitacoes[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "area-descending") {
        for (unsigned int j = habitacoes.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (habitacoes[i + 1]->getAreaHabitacional() > habitacoes[i]->getAreaHabitacional()) {
                    swap(habitacoes[i], habitacoes[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "pay-ascending") {
        for (unsigned int j = habitacoes.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (habitacoes[i + 1]->mensalidade < habitacoes[i]->mensalidade) {
                    swap(habitacoes[i], habitacoes[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "pay-descending") {
        for (unsigned int j = habitacoes.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (habitacoes[i + 1]->mensalidade > habitacoes[i]->mensalidade) {
                    swap(habitacoes[i], habitacoes[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }
}

vector<Condomino *> Condominio::getCondominos() {
    return condominos;
}

unsigned int Condominio::getNumCondominos() {
    return condominos.size();
}

void Condominio::adicionaCondomino(Condomino *con) {
    if (this->condominos.size() == 0)
        this->condominos.push_back(con);
    for (int i = 0; i < this->getNumCondominos(); i++) {
        if (this->getCondominos()[i]->getNIF() == con->getNIF())
            throw RepeatedCondomino(con->getNIF());
    }
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



void Condominio::ordenarCond(string protocol) {

    if (protocol == "name-ascending") {
        for (unsigned int j = condominos.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (condominos[i + 1]->getNome() < condominos[i]->getNome()) {
                    swap(condominos[i], condominos[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "name-descending") {
        for (unsigned int j = condominos.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (condominos[i + 1]->getNome() > condominos[i]->getNome()) {
                    swap(condominos[i], condominos[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "pay-ascending") {
        for (unsigned int j = condominos.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (condominos[i + 1]->mensalidadeTotal() > condominos[i]->mensalidadeTotal()) {
                    swap(condominos[i], condominos[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }

    else if (protocol == "pay-descending") {
        for (unsigned int j = condominos.size() - 1; j > 0; j--) {
            bool troca = false;
            for (unsigned int i = 0; i < j; i++)
                if (condominos[i + 1]->mensalidadeTotal() < condominos[i]->mensalidadeTotal()) {
                    swap(condominos[i], condominos[i + 1]);
                    troca = true;
                }
            if (!troca) return;
        }
    }
}

// Functions to find the pointers to objects in vector

Habitacao *Condominio::findHab(string id) {
    if (this->getNumHabitacoes() == 0)
        throw NoSuchHabitation(id);
    for (int i = 0; i < this->getNumHabitacoes(); i++)
    {
        if (this->getHabitacoes()[i]->getID() == id)
            return this->getHabitacoes()[i];
    }
    throw NoSuchHabitation(id);
}

Condomino *Condominio::findCon(int nif) {
    if (this->getNumCondominos() == 0)
        throw NoSuchCondomino(nif);
    for (int i = 0; i < this->getNumCondominos(); i++)
    {
        if (this->getCondominos()[i]->getNIF() == nif)
            return this->getCondominos()[i];
    }
    throw NoSuchCondomino(nif);
}

Servico *Condominio::findServ(float custo, string prestador, string servico) {
    if (this->getServicos().size() == 0)
        throw NoSuchService();
    for (int i = 0; i < this->getServicos().size(); i++)
    {
        if (this->getServicos()[i]->getCusto() == custo && this->getServicos()[i]->getPrestador() == prestador && this->getServicos()[i]->getTipo() == servico)
            return this->getServicos()[i];
    }
    throw NoSuchService();
}

void Condominio::adicionaServico(Servico *serv) {
    this->servicosPrestados.push_back(serv);
}


