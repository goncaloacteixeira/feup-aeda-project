//
// Created by skidr on 25/12/2019.
//

#ifndef PARTE2_CONDOMINIO_H
#define PARTE2_CONDOMINIO_H


#include "Condomino.h"
#include "Transporte.h"
#include <set>
#include <queue>
#include <unordered_set>


/**
 * @file Condominio.h
 * @brief Estruturas relacionadas com Condominio e respetivos Métodos
 */

/**
 * @brief Struct para guardar info de um antigo condómino
 */
typedef struct {
    string name;        //!< Nome do antigo condómino
    unsigned int nif;   //!< NIF do antigo condómino
    unsigned int time;  //!< Tempo passado no condominio
} FormerMember;

/**
 * @brief Hash para a HashTable
 */
struct FormerMembersHash {
    int operator () (const FormerMember & f) const {
        int v = 0;

        for (int i = 0; i < f.name.size(); i++) {
            v = 37*v + f.name[i];
        }
        return v;
    }
    bool operator () (const FormerMember & f1, const FormerMember & f2) const {
        return f1.nif == f2.nif;
    }
};

/**
 * @brief HashTable para guardar info de antigos condóminos
 */
typedef unordered_set<FormerMember, FormerMembersHash, FormerMembersHash> tabHFormerMembers;

/**
 * @brief Priority Queue para guardar info de transportes
 */
typedef priority_queue<Transporte> HEAP_TRANSPORT;

/**
 * @brief Classe Condomínio
 */
class Condominio {
    static int id;                          //!< ID do condominio

    string conFileName;                     //!< Filename do condominio
    string memFileName;                     //!< Filename dos condóminos
    string trFileName;                      //!< Filename dos transportes
    string frFileName;                      //!< Filename dos antigos condóminos

    string designation;                     //!< Designação do Condomínio
    string location;                        //!< Localização do Condomínio
    static set<string> prestLimpeza;        //!< Set com os prestadores de limpeza atuais
    unsigned int numPrestLimpeza;           //!< Número de prestadores de limpeza do condomínio
    vector<Habitacao *> habitacoes;         //!< Vetor de apontadores para objetos Habitação
    vector<Condomino *> condominos;         //!< Vetor de apontadores para objetos Condómino
    vector<Servico *> servicosPrestados;    //!< Vetor de apontadores para objetos Serviço

    HEAP_TRANSPORT transport;               //!< Priority Queue com os pontos de paragem relativos ao condominio em questão
    tabHFormerMembers formerMembers;        //!< Hash Table com os membros antigos do Condomínio em questão


public:
    /** @brief Construtor da Classe Comdoninio sem leitura de ficheiros
     *
     * @param numPrestLimpeza Número de prestadores de limpeza do condomínio
     * @param designation Designação do Condomínio
     * @param location Localização do Condomínio
     */
    Condominio(string designation, string location, unsigned int numPrestLimpeza);

    /** @brief Construtor da Classe Comdoninio com leitura de ficheiros
     *
     * @param filename Nome do ficheiro de texto com as informações do condomínio
     */
    Condominio(string filename);


    // Métodos GET

    /**
     * @return Designação do Condomínio
     */
    string getDesignation();

    /**
     * @return Localização do Condomínio
     */
    string getLocation();

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
    unsigned int getNumHabitacoes() const;

    /**
     *
     * @return Número de Vivendas do Condomínio
     */
    unsigned int getNumVivendas() const;

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
     * @brief Ordena Condóminos
     * @param protocol Portocolo de ordenação
     * protocol "id" sort by id (descendant)
     * protocol "area-descendant" sort by habitation's area (lower to higher)
     * protocol "area-ascendant" sort by habitation's area (higher to lower)
     * protocol "pay-descendant" sort by monthly payment (lower to higher)
     * protocol "pay-ascendant" sort by montly payment (lower to higher)
     */
    void ordernarHab(const string& protocol);

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
    void removeCondomino(Condomino *con, unsigned time);

    /**
     * @brief Ordena Condóminos
     * @param protocol Portocolo de ordenação
     * protocol "name" sort by name (A-Z)
     * protocol "number-descendant" sort by number of houses (lower to higher)
     * protocol "number-ascendant" sort by number of houses (higher to lower)
     * protocol "pay-descendant" sort by monthly payment (lower to higher)
     * protocol "pay-ascendant" sort by montly payment (lower to higher)
     */
    void ordenarCond(const string& protocol);

    /**
     *
     * @param id ID da habitação a encontrar
     * @return Apontador para habitação encontrada ou exception
     */
    Habitacao* findHab(const string& id);

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
    Servico* findServ(float custo, const string& prestador, const string& servico);

    /** @brief Função para escrita em ficheiros
     *
     * @param condominio Filename do condomínio
     * @param condominos Filename dos condóminos
     */
    void writeToFiles();

    /**
     *
     * @return Prestadores de Serviço de Limpeza
     */
    set<string> prestLimpezaAtuais() { return prestLimpeza; }

    // Mensalidades

    /**
    * @return O total de receitas no condomínio
    */
    float calcReceitas() const;


    // HEAP

    /**
     * @brief Metodo SET para atribuir transportes
     * @param transports vetor de transportes a adicionar à priority queue
     */
    void setTransports(vector<Transporte>* transports);

    /**
     * @brief Metodo GET devolve priority queue dos transportes
     * @return HEAP com transportes
     */
    HEAP_TRANSPORT getTransports() const;

    /**
     * @brief Metodo GET devolve vetor com transportes para um destino
     * @param destiny Destino especifico
     * @return vetor com transportes para um determinado destino
     */
    vector<Transporte> getTransports(string destiny) const;

    /**
     * @brief Metodo GET devolve vetor com transportes
     * @return vetor com todos os transportes
     */
    vector<Transporte> getVectorTransports() const;

    /**
     * @brief Metodo adiciona uma paragem nova
     * @param t1 Nova paragem a adicionar
     */
    void addTransportStop(const Transporte& t1);

    /**
     * @brief Metodo remove um paragem
     * @param t1 Paragem a remover
     * @return true - paragem existente e removida
     * @return false - paragem inexistente
     */
    bool removeTransportStop(const Transporte& t1);

    /**
     * @brief Metodo devolve um transporte especifico
     * @param loc   Localização para a paragem a procurar
     * @param dist  Distancia para a paragem a procurar
     * @param dest  Destino para a paragem a procurar
     * @return  Transporte diferente de Transporte() caso encontre
     */
    Transporte getTransport(const string& loc, unsigned int dist, const string& dest);

    // HASH TABLE

    /**
     * @brief Metodo GET devolve hashtab dos antigos membros
     * @return HashTab dos antigos membros
     */
    tabHFormerMembers getFormerMembers() const;

    /**
     * @brief Função para encontrar um antigo condómino dado um NIF
     * @param nif NIF do antigo condómino a econtrar
     * @return antigo condómino
     * Levanta uma exceção quando não consegue encontrar o antigo condómino
     */
    FormerMember findFormerMember(unsigned int nif);

    /**
     * @brief Membro para encontrar antigos condóminos que estiveram ligados ao condominio por um tempo minimo time
     * @param time tempo minimo
     * @return vetor com os membros antigos
     */
    vector<FormerMember> getformerMembers(unsigned int time);

    // operators

    /**
     * @brief Overload do operador '<<'
     * Apresenta informações basicas do Condominio em formato 'user-friendly'
     */
    friend ostream& operator<<(ostream& os, const Condominio& con);

    /**
     * @brief Overload do operador '<'
     * Ordenaão feita por numero de habitações e em caso de empate por numero de vivendas
     */
    bool operator<(const Condominio &con1) const;

    /**
     * @brief Overload do operador '=='
     * Dois condominios são iguais se tiverem as mesmas designação e localização
     */
    bool operator==(const Condominio &con1) const;
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
class InvalidNIF {
    unsigned int nif;
public:
    InvalidNIF(unsigned int nif) { this->nif = nif; }
    unsigned int getNIF() { return this->nif; }
};

/**
 * @brief Exception Class para não conseguimos encontrar um antigo condómino
 */
class NoSuchFormerMember {
    unsigned int nif;
public:
    NoSuchFormerMember(unsigned int nif) { this->nif = nif; }
    unsigned int getNIF() { return this->nif; }
};

#endif //PARTE2_CONDOMINIO_H
