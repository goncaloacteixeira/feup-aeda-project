//
// Created by skidr on 25/12/2019.
//

#include "Condominio.h"
#include <chrono>
#include "utils.h"
#include <iostream>
#include <utility>

set<string> Condominio::prestLimpeza = {};

Condominio::Condominio(string designation, string location, unsigned int numPrestLimpeza) :
    designation(std::move(designation)), location(std::move(location)), numPrestLimpeza(numPrestLimpeza) {

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
    string transportsFileName;
    string formerMembersFileName;
    int numHab = 0;

    condominio.open(filename);
    if (condominio.is_open()) {
        while (getline(condominio, line) && i < 7) {
            /**
             * line 0 -> designation
             * line 1 -> location
             * line 2 -> numPrestLimpeza
             * line 3 -> filename condominos
             * line 4 -> numHab
             * line 5 -> transports filename
             * line 6 -> former members filename
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
            else if (i == 5)
                transportsFileName = line;
            else if (i == 6)
                formerMembersFileName = line;
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
            for (i = 0; i < numHab; i++) {
                vector<string> hab;
                while (getline(condominio, line1)) {
                    if (ctr >= 7) {     // control to skip first lines
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


        for (i = 0; i < numHab; i++) {
            if (info[i][0][0] == 'A') {
                auto *ap = new Apartamento(info[i][2], stof(info[i][3]), info[i][4],stoi(info[i][5]), stof(info[i][6]));

                ap->setEstado(info[i][1] == "1");
                habitacoes.push_back(ap);
            }
            if (info[i][0][0] == 'V') {
                bool piscina;
                piscina = info[i][5] == "1";
                auto *vi = new Vivenda(info[i][2], stof(info[i][3]), stof(info[i][4]), piscina, stof(info[i][6]));

                vi->setEstado(info[i][1] == "1");
                habitacoes.push_back(vi);
            }
        }
        info.clear();
    }

    // Transportes Read Snippet Code
    vector<Transporte> transports = {};
    transportsFileName = "../" + transportsFileName;

    ifstream transportsFile;
    transportsFile.open(transportsFileName);
    string trLine;

    if (transportsFile.is_open()) {
        while (getline(transportsFile, trLine)) {
            vector<string> temp = split(trLine, " : ");
            transport.push(Transporte(temp[0], stoi(temp[1]), temp[2]));
        }
        transportsFile.close();
    }
    else {
        cerr << "\nerror opening transports file\n";
    }

    // Former Members Read Snippet Code
    formerMembersFileName = "../" + formerMembersFileName;
    ifstream formerMembersFile;
    formerMembersFile.open(formerMembersFileName);
    string frLine;

    if (formerMembersFile.is_open()) {
        while (getline(formerMembersFile, frLine)) {
            vector<string> temp = split(frLine, " : ");
            FormerMember former;
            former.name = temp[0];
            former.nif = stoi(temp[1]);
            former.time = stoi(temp[2]);
            formerMembers.insert(former);
        }
    }
    else {
        cerr << "\nerror opening former members file\n";
    }

    // Condominos Read Snippet Code
    this->condominos = {};

    condominosFileName = "../" + condominosFileName;

    ifstream condominosFile;
    condominosFile.open(condominosFileName);

    int numCondominos = 0;

    if (condominosFile.is_open())
    {
        string l;
        getline(condominosFile, l);
        numCondominos = stoi(l);
        condominosFile.close();
    }

    vector<vector<string> > info;
    if (numCondominos != 0)
    {
        condominosFile.open(condominosFileName);
        if (condominosFile.is_open())
        {
            int ctr = 0;
            string line1;
            for (i = 0; i < numCondominos; i++) {
                vector<string> con;
                while (getline(condominosFile, line1)) {
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
            condominosFile.close();
        }
    }

    if (numCondominos != 0) {
        for (i = 0; i < numCondominos; i++) {
            auto *c = new Condomino(info[i][0], stoi(info[i][1]));
            int numHabs = stoi(info[i][2]);
            if (numHabs != 0) {
                for (int j = 0; j < numHabs; j++)
                    c->adicionaHabitacao(findHab(info[i][3 + j]));
            }

            int numServ = stoi(info[i][3 + numHabs]);
            if (numServ != 0) {
                for (int j = 0; j < numServ; j++) {
                    vector<string> servico = split(info[i][4 + numHabs + j], " : ");
                    auto *serv = new Servico(stof(servico[1]), servico[2], servico[0]);
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

void Condominio::writeToFiles(string condominioFilename, string condominosFilename, string transportFilename, string formerMembersFilename) {
    auto start = chrono::steady_clock::now();

    condominioFilename = "../" + condominioFilename;

    fstream condominio(condominioFilename, std::ofstream::out | std::ofstream::trunc);
    condominio << this->designation << endl;
    condominio << this->location << endl;
    condominio << this->numPrestLimpeza << endl;
    condominio << condominosFilename << endl;
    condominio << this->getNumHabitacoes() << endl;
    condominio << transportFilename << endl;
    condominio << formerMembersFilename << endl;
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
            if (!this->condominos[i]->getServicos().empty())
            {
                for (int j = 0; j < this->condominos[i]->getServicos().size() ; j++)
                    cond << endl << this->condominos[i]->getServicos()[j]->getTipo() << " : " << this->condominos[i]->getServicos()[j]->getCusto() << " : " << this->condominos[i]->getServicos()[j]->getPrestador();
            }
            if (i != this->getNumCondominos() - 1)
                cond << "\n::::::::::\n";
        }
    }
    cond.close();

    transportFilename = "../" + transportFilename;
    fstream trans(transportFilename, std::ofstream::out | std::ofstream::trunc);
    if (!transport.empty()) {
        auto transports = this->getVectorTransports();
        for (auto &t : transports) {
            trans << t.getLocalization() << " : " << t.getDistance() << " : " << t.getDestiny() << endl;
        }
    }
    trans.close();

    formerMembersFilename = "../" + formerMembersFilename;
    fstream form(formerMembersFilename, std::ofstream::out | std::ofstream::trunc);
    if (!formerMembers.empty()) {
        for (auto &i : formerMembers) {
            form << i.name << " : " << i.nif << " : " << i.time << endl;
        }
    }
    form.close();


    auto end = chrono::steady_clock::now();
    cout << "The writing took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";
}

float Condominio::calcReceitas() const {
    float rec = 0;

    if (this->getNumHabitacoes() != 0) {
        for (auto condomino : condominos)
            rec += condomino->mensalidadeTotal();
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

unsigned int Condominio::getNumHabitacoes() const {
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

void Condominio::ordernarHab(const string& protocol) {
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
    if (this->condominos.empty())
        this->condominos.push_back(con);
    for (int i = 0; i < this->getNumCondominos(); i++) {
        if (this->getCondominos()[i]->getNIF() == con->getNIF())
            throw RepeatedCondomino(con->getNIF());
    }
    this->condominos.push_back(con);
}

void Condominio::removeCondomino(Condomino *con, unsigned time) {
    for (int i = 0; i < condominos.size(); i++) {
        if (condominos[i] == con) {
            FormerMember former;
            former.name = condominos[i]->getNome();
            former.nif = condominos[i]->getNIF();
            former.time = time;
            formerMembers.insert(former);
            condominos.erase(condominos.begin() + i);
            break;
        }
    }
}



void Condominio::ordenarCond(const string& protocol) {

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

Habitacao *Condominio::findHab(const string& id) {
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

Servico *Condominio::findServ(float custo, const string& prestador, const string& servico) {
    if (this->getServicos().empty())
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

string Condominio::getDesignation() {
    return this->designation;
}

string Condominio::getLocation() {
    return this->location;
}

bool Condominio::operator<(const Condominio &con1) const {
    if (this->getNumHabitacoes() == con1.getNumHabitacoes()) {
        return this->getNumVivendas() < con1.getNumVivendas();
    }
    return this->getNumHabitacoes() < con1.getNumHabitacoes();
}

unsigned int Condominio::getNumVivendas() const {
    int res = 0;

    for (auto &h : this->habitacoes) {
        if (h->getID()[0] == 'V') {
            res++;
        }
    }
    return res;
}

bool Condominio::operator==(const Condominio &con1) const {
    return this->designation == con1.designation && this->location == con1.designation;
}

// HEAP
void Condominio::setTransports(vector<Transporte>* tr) {
    for (auto &t : *tr) {
        transport.push(t);
    }
}

HEAP_TRANSPORT Condominio::getTransports() const {
    return transport;
}

void Condominio::addTransportStop(const Transporte& t1) {
    this->transport.push(t1);
}

bool Condominio::removeTransportStop(const Transporte& t1) {
    vector<Transporte> toPutBack;
    bool found = false;
    while (!this->transport.empty()) {
        if (transport.top().getDestiny() == t1.getDestiny() &&
            transport.top().getDistance() == t1.getDistance() &&
            transport.top().getLocalization() == t1.getLocalization()) {
            found = true;
        }
        else {
            toPutBack.emplace_back(transport.top());
        }
        transport.pop();
    }
    return found;
}

Transporte Condominio::getTransport(const string& dest) {
    HEAP_TRANSPORT temp = this->transport;

    while (!temp.empty()) {
        if (temp.top().getDestiny() == dest) {
            return temp.top();
        }
        temp.pop();
    }
    return Transporte();
}

vector<Transporte> Condominio::getVectorTransports() const {
    HEAP_TRANSPORT temp = this->transport;
    vector<Transporte> res;

    while (!temp.empty()) {
        res.push_back(temp.top());
        temp.pop();
    }
    return res;
}

ostream &operator<<(ostream &os, const Condominio &con) {
    os << "Designation: " << con.designation << endl;
    os << "Location: " << con.location << endl;
    os << "Number of Habitations: " << con.habitacoes.size() << endl;
    os << "Number of Members: " << con.condominos.size() << endl;
    os << "Revenue: " << con.calcReceitas() << " euro" << endl;
    return os;
}


