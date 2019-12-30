//
// Created by skidr on 27/12/2019.
//

#ifndef PARTE2_CAGENCY_H
#define PARTE2_CAGENCY_H

#include "bst.h"
#include "Condominio.h"

/**
 * @file CAgency.h
 * @brief Classe da Agência de Gestão de Condomínios e respetivos Métodos
 */

/**
 * @brief Classe CAgency
 */
class CAgency {
    string name;                    //!< Nome do proprietário ou gestor da agencia de condominios
    unsigned nif;                   //!< NIF do proproetário
    vector<string> ids;             //!< ID's de habitações ja existentes na agencia
    BST<Condominio*> condominios;   //!< Binary Search Tree para
public:
    /**
     * @brief Construtor da classe CAgency
     * @param name  nome do proprietário
     * @param nif   NIF do proprietário
     */
    CAgency(string name, unsigned int nif) :
        condominios(new Condominio("","",0)),
        name(name), nif(nif) { ids = {}; };

    /**
     * @brief Método para adicionar varios condominios
     * @param cons Vetor de apontadores para Condominios
     * @return numero de condominios adicionados
     */
    int addCondominios(const vector<Condominio*>& cons);

    /**
     * @brief Método para adicionar um condominio
     * @param con Apontador para o condominio a ser adicionado
     */
    void addCondominio(Condominio* con);

    /**
     * @brief Método para remover um condominio
     * @param con Apontador para o condominio a ser removido
     */
    void removeCondominio(Condominio* con);

    /**
     * @brief Procura no vetor ids se existe o ID passado como parametro
     * @param id ID a procurar
     * @return true - existe
     * @return false - não existe
     */
    bool findID(string id);

    /**
     * @brief Método GET devolve vetor de apontadores de condominios
     * @param nHabsMax Numero maximo de Habitaçoes
     * @return vetor de apontadores de condominios com no maximo nHabsMax habitações
     */
    vector<Condominio*> getCondominios(int nHabsMax);

    /**
     * @brief Método para procurar um condominio
     * @param des Designação do condominio a procurar
     * @param loc Localização do condominio a procurar
     * @return Apontador para o condominio encontrado
     * @return nullptr caso o condominio não exista
     */
    Condominio* findCondominio(string des, string loc);

    /**
     * @brief Overload do operador '<<'
     * Apresenta as informações da Agencia e respetivos condominios associados em formato 'user-friendly'
     */
    friend ostream& operator<<(ostream& os, const CAgency& dt);

    /**
     * @brief Método GET devolve BST com os condominios
     * @return BST com os condominios associados à agencia
     */
    BST<Condominio*> getCondominios();

    /**
     * @brief Escrita em ficheiros
     * Método para escrever as informações dos varios condominios associados em ficheiros
     */
    void writeToFiles();

};


#endif //PARTE2_CAGENCY_H
