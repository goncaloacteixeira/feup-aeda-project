//
// Created by skidr on 25/12/2019.
//

#ifndef PARTE2_CONDOMINO_H
#define PARTE2_CONDOMINO_H

/**
 * @file Condomino.h
 * @brief Classe e Métodos para Condómino
 */

#include "Habitacao.h"
#include "Servico.h"
#include <fstream>

/**
 * @brief Classe Condómino
 */
class Condomino {
    const string nome;                  //!< Nome do Condómino
    const unsigned int nif;             //!< NIF do Condómino
    vector<Habitacao *> habitacoes;     //!< Vetor de Habitações pertencentes ao condómino
    vector<Servico *> servicos;         //!< Vetor de Serviços prestados ao condómino
public:
    /**
     * @brief Construtor da classe Condómino
     * @param nome Nome do Condómino
     * @param nif  NIF do Condómino
     */
    Condomino(string nome, unsigned int nif);

    // Métodos GET

    /**
     * @brief Metodo GET devolve nome do condómino
     * @return Nome do condómino
     */
    string getNome() const;

    /**
     * @brief Metodo GET devolve NIF do condómino
     * @return NIF do condómino
     */
    unsigned int getNIF() const;

    /**
     * @brief Metodo GET devolve numero de habitações do condómino
     * @return Número de Habitações do condómino
     */
    int getNumHabitacoes();

    /**
     * @brief Metodo GET devolve habitações do condómino
     * @return Vetor das Habitações pertencentes ao condómino
     */
    vector<Habitacao *> getHabitacoes();

    /**
     * @brief Metodo GET devolve serviços prestados ao condómino
     * @return Vetor das Serviços prestados ao condómino
     */
    vector<Servico *> getServicos();

    /**
     * @brief Metodo adiciona habitação as habitações do condómino
     * @param hab Apontador para Habitação a adicionar ao condómino
     */
    void adicionaHabitacao(Habitacao *hab);

    /**
     * @brief Metodo remove habitação das habitações do condómino
     * @param hab Apontador para Habitação a remover do condómino
     */
    void removeHabitacao(Habitacao *hab);

    /**
     * @brief Metodo adiciona serviço as serviços do condómino
     * @param serv Apontador para Serviço a adicionar ao condómino
     */
    void adicionaServico(Servico *serv);

    /**
     * @return Info do condómino em string 'user-friendly'
     */
    string info();

    /** @brief Ordena habitações por area habitacional
     *
     * @param reverse true - area maior para area menor
     */
    void ordenarHabitacoesArea(bool reverse);           // true -> area maior para area menor


    /** @brief Ordena habitaçoes por mensalidade
     *
     * @param reverse true - mensalidade maior para mensalidade menor
     */
    void ordenarHabitacoesMensalidade(bool reverse);    // true -> mensalidade maior para mensalidade menor

    /**
     *
     * @return Mensalidade total a pagar pelo condómino
     */
    float mensalidadeTotal();

    /**
    * @brief Overload do operador '<<'
    * Apresenta informações basicas do condómino em formato 'user-friendly'
    */
    friend ostream& operator<<(ostream& os, const Condomino& mem);
};



#endif //PARTE2_CONDOMINO_H
