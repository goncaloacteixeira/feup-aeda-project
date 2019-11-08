//
// Created by skidr on 12/10/2019.
//

#ifndef PARTE1_MORADA_H
#define PARTE1_MORADA_H

#include <string>
#include <vector>

using namespace std;

/**
 * @brief Classe Morada
 *
 * A classe Morada é uma classe simples, apenas para armazenar os dados de uma morada como\n
 * por exemplo rua, numero, codigo posta, etc.
 *
 * \n\n
 *
 * Estão também definidos os vários métodos GET, SET e construtores
 */
class Morada {
    string rua;
    string localidade;
    unsigned int numero;
    vector<int> codPostal;
public:
    Morada();   // Construtor padrão
    Morada(string rua, string localidade, unsigned int numero, vector<int> codPostal);
    Morada(string morada);

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
