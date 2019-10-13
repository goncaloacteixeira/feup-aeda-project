//
// Created by skidr on 12/10/2019.
//

#ifndef PARTE1_MORADA_H
#define PARTE1_MORADA_H

#include <string>
#include <vector>

using namespace std;

class Morada {
    string rua;
    string localidade;
    unsigned int numero;
    vector<int> codPostal;
public:
    Morada();
    Morada(string rua, string localidade, unsigned int numero, vector<int> codPostal);

    // GET Methods

    string getRua();
    string getLocalidade();
    unsigned int getNumero();
    vector<int> getCodpostal();
    string getMorada();

    // SET Methods

    void setRua (string rua);
    void setLocalidade (string localidade);
    void setNumero (unsigned int numero);
    void setCodpostal (vector<int> codPostal);
};

#endif //PARTE1_MORADA_H
