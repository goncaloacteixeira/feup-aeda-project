//
// Created by skidr on 25/10/2019.
//

#include "Condominio.h"
#include <iostream>

Condominio::Condominio(unsigned int numPrestLimpeza) : numPrestLimpeza(numPrestLimpeza) {
    this->habitacoes = {};
    this->condominos = {};
}

vector<string> split1 (string &s, string delimiter) {
    size_t pos = 0;
    std::string token;
    vector<string> result;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    result.push_back(s);
    return result;
}

Condominio::Condominio(string filename) {
    filename = "../" + filename;
    ifstream condominio;
    string line;
    int i = 0;

    string condominosFileName;
    int numHab;

    condominio.open(filename);
    if (condominio.is_open()) {
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
            Morada novaMorada(info[i][2]);
            if (info[i][0][0] == 'A') {
                Apartamento *ap = new Apartamento(novaMorada, stof(info[i][3]), info[i][4],stoi(info[i][5]), stof(info[i][6]));

                ap->setEstado(info[i][1] == "0");
                habitacoes.push_back(ap);
            }
            if (info[i][0][0] == 'V') {
                bool piscina;
                piscina = info[i][5] == "1";
                Vivenda *vi = new Vivenda(novaMorada, stof(info[i][3]), stof(info[i][4]), piscina, stof(info[i][6]));

                vi->setEstado(info[i][1] == "0");
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

    for (int i = 0; i < numCondominos; i++)
    {
        Condomino *c = new Condomino(info[i][0], stoi(info[i][1]));
        int numHabs = stoi(info[i][2]);
        if (numHabs != 0) {
            for (int j = 0; j < numHabs ; j++)
                c->adicionaHabitacao(findHab(info[i][3 + j]));
        }

        int numServ = stoi(info[i][3 + numHabs]);
        if (numServ != 0) {
            for (int j = 0; j < numServ ; j++) {
                vector<string> servico = split1(info[i][4 + numHabs + j]," : ");
                Servico *serv = new Servico(stof(servico[1]),servico[2],servico[0]);
                c->adicionaServico(serv);
            }
        }
        this->condominos.push_back(c);
    }
}

void Condominio::writeToFiles(string condominioFilename, string condominosFilename) {
    condominioFilename = "../" + condominioFilename;

    fstream condominio(condominioFilename, std::ofstream::out | std::ofstream::trunc);
    condominio << this->getNumPrestLimpeza() << endl;
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

