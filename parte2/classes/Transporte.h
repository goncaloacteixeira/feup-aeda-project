//
// Created by skidr on 27/12/2019.
//

#ifndef PARTE2_TRANSPORTE_H
#define PARTE2_TRANSPORTE_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @file Transporte.h
 * @brief Classe e Métodos para Transportes
 */

/**
 * @brief Classe Transporte
 */
class Transporte {
    string localizacao;             //!< Localização do Ponto de Paragem
    unsigned int distancia;         //!< Distancia do Ponto de Paragem ao Condomínio
    string destino;                 //!< Destino do Ponto de Paragem
    bool active;                    //!< Estado do Ponto de Paragem
public:
    /**
     * @brief Construtor padrão para um transporte (paragem)
     */
    Transporte() : localizacao(""), distancia(0), destino(""), active(false) { };

    /**
     * @brief Construtor da Classe Transporte
     * @param loc       localização da paragem
     * @param dist      distancia entre paragem e condomínio
     * @param dest      destino do transporte
     * @param active    true - ativo | false - inativo
     */
    Transporte(string loc, unsigned dist, string dest, bool active);

    /**
     * @brief Metodo GET devolve localização da paragem
     * @return Localização da paragem
     */
    string getLocalization() const;

    /**
     * @brief Metodo GET devolve distancia
     * @return Distancia entre o condomínio e a paragem
     */
    unsigned getDistance() const;

    /**
     * @brief Metodo GET devolve destino
     * @return Destino do transported
     */
    string getDestiny() const;

    /**
     * @brief Metodo GET devolve atividade
     * @return true - ativo
     * @return false - inativo
     */
    bool getState() const;

    /**
     * @brief Metodo altera o destino do transporte
     * @param dest Novo destino
     */
    void changeDestiny(string dest);

    /**
     * @brief Metodo altera a atividade da paragem
     * @param state true - passa a ativo | false - passa a inativo
     */
    void changeState(bool state);

    /**
     * @brief Overload do operador '<<'
     * Apresenta info basica do transporte em formato 'user-friendly'
     */
    friend ostream& operator<<(ostream& os, Transporte& t1);

    /**
     * @brief Overload do operador '<'
     * Um transporte é "menor" que outro se a sua distancia for maior que a do segundo
     */
    bool operator<(const Transporte &t1) const;

    /**
     * @brief Overloado do operador '=='
     * Um transporte é igual ao outro se todos os atributos forem iguais, sem necessidade de incluir o estado de atividade
     */
    bool operator==(const Transporte &t1) const;
};


#endif //PARTE2_TRANSPORTE_H
