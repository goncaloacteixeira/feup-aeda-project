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
     *
     * @param nome Nome do Condómino
     * @param nif  NIF do Condómino
     */
    Condomino(string nome, unsigned int nif);

    // Métodos GET

    /**
     *
     * @return Nome do condómino
     */
    string getNome() const;

    /**
     *
     * @return NIF do condómino
     */
    unsigned int getNIF() const;

    /**
     *
     * @return Número de Habitações do condómino
     */
    int getNumHabitacoes();

    /**
     *
     * @return Vetor das Habitações pertencentes ao condómino
     */
    vector<Habitacao *> getHabitacoes();

    /**
     *
     * @return Vetor das Serviços prestados ao condómino
     */
    vector<Servico *> getServicos();

    /**
     *
     * @param hab Apontador para Habitação a adicionar ao condómino
     */
    void adicionaHabitacao(Habitacao *hab);

    /**
     *
     * @param hab Apontador para Habitação a remover do condómino
     */
    void removeHabitacao(Habitacao *hab);

    /**
     *
     * @param serv Apontador para Serviço a adicionar ao condómino
     */
    void adicionaServico(Servico *serv);

    /**
     *
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
};



#endif //PARTE2_CONDOMINO_H
