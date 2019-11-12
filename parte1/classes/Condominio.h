//
// Created by skidr on 25/10/2019.
//

#ifndef PARTE1_CONDOMINIO_H
#define PARTE1_CONDOMINIO_H

#include "Condomino.h"
#include <set>

/**
 * @brief Classe Condomínio
 */
class Condominio {
    static set<string> prestLimpeza;        //!< Set com os prestadores de limpeza atuais
    unsigned int numPrestLimpeza;           //!< Número de prestadores de limpeza do condomínio
    vector<Habitacao *> habitacoes;         //!< Vetor de apontadores para objetos Habitação
    vector<Condomino *> condominos;         //!< Vetor de apontadores para objetos Condómino
    vector<Servico *> servicosPrestados;    //!< Vetor de apontadores para objetos Serviço

public:
    /** @brief Construtor da Classe Comdoninio sem leitura de ficheiros
     *
     * @param numPrestLimpeza Número de prestadores de limpeza do condomínio
     */
    Condominio(unsigned int numPrestLimpeza);

    /** @brief Construtor da Classe Comdoninio com leitura de ficheiros
     *
     * @param filename Nome do ficheiro de texto com as informações do condomínio
     */
    Condominio(string filename);


    // Métodos GET
    /**
     * @return Número de prestadores de limpeza do condomínio
     */
    unsigned int getNumPrestLimpeza();

    /**
     *
     * @return Vetor com os serviços prestados pelo condomínio
     */
    vector<Servico *> getServicos();


    void adicionaServico(Servico *serv);

    /**
     *
     * @return Vetor com as habitações pertencentes ao condomínio
     */
    vector<Habitacao *> getHabitacoes();

    /**
     *
     * @return Número de habitações do condomínio
     */
    unsigned int getNumHabitacoes();

    /**
     *
     * @param hab Apontador para a habitação a adicionar ao condomínio
     */
    void adicionaHabitacao(Habitacao *hab);

    /**
     *
     * @param hab Apontador para a habitação a remover do condomínio
     */
    void removeHabitacao(Habitacao *hab);

    /**
     * @brief Ordena Habitações
     * @param protocol Portocolo de ordenação
     */
    void ordernarHab(string protocol);

    /**
     *
     * @return Vetor com os condóminos pertencentes ao condomínio
     */
    vector<Condomino *> getCondominos();

    /**
     *
     * @return Número de condóminos pertencentes ao condomínio
     */
    unsigned int getNumCondominos();

    /**
     *
     * @param con Apontador para o condómino a adicionar ao condomínio
     */
    void adicionaCondomino(Condomino *con);

    /**
     *
     * @param con Apontador para o condómino a remover do condimínio
     */
    void removeCondomino(Condomino *con);

    /**
     * @brief Ordena Condóminos
     * @param protocol Portocolo de ordenação
     */
    void ordenarCond(string protocol);

    /**
     *
     * @param id ID da habitação a encontrar
     * @return Apontador para habitação encontrada ou exception
     */
    Habitacao* findHab(string id);

    /**
     *
     * @param nif NIF do condómino a encontrar
     * @return Apontador para habitação encontrada ou exception
     */
    Condomino* findCon(int nif);

    /**
     *
     * @param custo Custo do serviço a encontrar
     * @param prestador Prestador do serviço a encontrar
     * @param servico Serviço a encontrar
     * @return Apontador para serviço ou exception
     */
    Servico* findServ(float custo, string prestador, string servico);

    /** @brief Função para escrita em ficheiros
     *
     * @param condominio Filename do condomínio
     * @param condominos Filename dos condóminos
     */
    void writeToFiles(string condominio, string condominos);

    /**
     *
     * @return Prestadores de Serviço de Limpeza
     */
    set<string> prestLimpezaAtuais() { return prestLimpeza; }

    // Mensalidades

    /**
    * @return O total de receitas no condomínio
    */
    float calcReceitas();
};

// Exception Classes

/**
 * @brief Exception Class para quando não conseguimos encontrar uma habitação
 */
class NoSuchHabitation {
    string id;
public:
    NoSuchHabitation(string id) { this->id = id; }
    string getID() { return this->id; }
};

/**
 * @brief Exception Class para quando não conseguimos encontrar um condómino
 */
class NoSuchCondomino {
    unsigned int nif;
public:
    NoSuchCondomino(unsigned int nif) { this->nif = nif; }
    unsigned int getNIF() { return this->nif; }
};

/**
 * @brief Exception Class para quando não conseguimos encontrar um serviço
 */
class NoSuchService {
public:
    NoSuchService() {};
};

/**
 * @brief Exception Class para quando ja existe determinado condómino
 */
class RepeatedCondomino {
    unsigned int nif;
public:
    RepeatedCondomino(unsigned int nif) { this->nif = nif; }
    unsigned int getNIF() { return this->nif; }
};

#endif //PARTE1_CONDOMINIO_H
