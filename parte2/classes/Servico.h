//
// Created by skidr on 12/10/2019.
//

#ifndef PARTE1_SERVICO_H
#define PARTE1_SERVICO_H

/**
 * @file Servico.h
 * @brief Classe e Métodos para Serviço
 */

#include <string>

using namespace std;

/**
 * @brief Classe Serviço
 *
 * Métodos GET definidos
 */
class Servico {
    float custo;        //!< Custo do serviço prestado
    string prestador;   //!< Nome da empresa ou do functionário prestador do serviço
    string servico;     //!< Serviço prestado
public:

    /** @brief Construtor da Classe Serviço
     *
     * @param custo         Custo do serviço prestado
     * @param prestador     Nome da empresa ou do functionário prestador do serviço
     * @param servico       Serviço prestado
     */
    Servico(const float custo, string prestador, string servico);

    /**
     *
     * @return Tipo do serviço prestado (limpeza, cabeleireiro, jardineiro, etc.)
     */
    string getTipo();

    /**
     *
     * @return Custo do serviço prestado
     */
    float getCusto();

    /**
     *
     * @return Prestador do serviço
     */
    string getPrestador();
};


#endif //PARTE1_SERVICO_H
