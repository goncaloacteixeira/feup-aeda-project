# TEMA 4 - GESTÃO DE CONDOMÍNIO - CONDOMIX

[Documentação (gerada por Doxygen)](project-aeda-p2-g4-t3-1920.epizy.com)

Realizado pelo grupo 4 da turma 3 das aulas práticas de AEDA19/20.

- Gonçalo Teixeira
- Tiago Pinto
- João Ferreira

# Problema

O objetivo desta segunda parte do projeto da U.C. teria como base um acréscimo de funcionalidades relativamente à primeira parte.

- Desta vez queremos gerir vários condomínios ao mesmo tempo, usando uma árvore binária de pesquisa. Esta BST, implementada no ficheiro `bst.h`foi obtida da página da U.C. de AEDA. Os condomínios estão ordenados por número de habitações, e em caso de empate por número de vivendas.
  - Os condomínios existentes devem ser carregados no inicio da execução do programa, a razão disto iremos explicar adiante.

- Uma funcionalidade nova deve ser implementada: rede de transportes, ou melhor, uma forma de um condómino saber que transportes tem à sua disposição e a que distância se encontram.
  - Estes transportes devem ser guardados numa fila de prioridade ordenados pela menor distância.
- Finalmente, queremos ter acesso às informações de antigos condóminos que já não pertençam a nenhum condomínio listado na agência.
  - Para tal efeito usaremos uma tabela de dispersão.



# Solução

A solução consiste numa adaptação da primeira parte.

Depois de alguma consideração, percebemos que a classe `Morada` implementada na primeira parte do projeto seria desnecessária uma vez que em nenhuma parte do programa precisamos de aceder à rua, localidade, etc. individualmente, ao deixarmos de usar esta classe ficamos com menos 2 problemas, a morada agora é uma única string, não precisamos de efetuar nenhum tipo de parsing, o utilizador pode utilizar uma morada fora do formato que queríamos, e o que daria imenso trabalho tornou-se simples e direto.

Antes de procedermos à implementação das novas funcionalidades tivemos o cuidado de verificar se o que já tinhamos feito estava efetivamente livre de erros. Depois de algumas correções e testes, o programa estava finalmente pronto a passar à fase seguinte.

### 1. BST

Uma agência tem o nome do proprietário, o seu NIF e uma BST com os condomínios registados.

Para implementarmos a BST com a finalidade de gerir vários condomínios ao mesmo tempo, utilizamos a implementação das aulas de AEDA, como já referido. 

A BST está composta por pointers para condomínios.

### 2. PRIORITY-QUEUE

Para implementarmos a fila de prioridade para a funcionalidade de transportes primeiro tivemos de escolher como iriamos guardar a informação acerca de uma paragem (transporte).

Criamos uma classe `Transporte` que contem informação acerca da sua localização, distancia entre o condomínio e a paragem, destino e estado de atividade (ativo ou não ativo).

Numa fila de prioridade as paragens (transportes) estão ordenados pela menor distância, conveniente uma vez que o condómino quer percorrer a mínima distância a pé.

Para guardar esta informação em ficheiros, uma nova linha no ficheiro do condomínio é criada com o nome do ficheiro dos transportes (tipicamente tr\<i>.txt em que i é o id do condomínio).

A informação está guardada da seguinte maneira:

​	`<localização> : <distancia> : <destino> : <1 | 0 >` 			*1 representa ativo*



### 3. HASH TABLE

Para implementarmos a tabela de dispersão com a finalidade de guardar informações de antigos condóminos (questões de marketing) utilizamos o `unordered_set` da STL.

Um antigo condómino é representado por uma struct `formerMember` que tem um nome, um NIF e um tempo de ligação com o condomínio.

Naturalmente, um antigo membro é adicionado no momento da sua remoção do condomínio.

Os antigos condóminos, identicamente aos transportes, são guardados num ficheiro separado (tipicamente former\<i>.txt em que i é o id do condomínio). Este filename está numa nova linha no ficheiro do condomínio.

A informação está guardada da seguinte maneira:

​	`<nome> : <NIF> : <tempo>`



### Condomínio

Para diferenciar os condomínios, vamos distingui-los por designação e localização.

#### O ficheiro do condomínio

```
desginaçao
localizaçao
num_prestadores_limpeza
condominos_filename
num_hab
transportes_filename
antigos_membros_filename
ID hab0
ocupado ? (1 - sim / 0 - nao)
morada
area_hab
tipologia / area_ext
piso / piscina (1 - sim / 0 - nao)
mensalidade
::::::::::
ID hab1
ocupado ? (1 - sim / 0 - nao)
morada
area_hab
tipologia / area_ext
piso / piscina (1 - sim / 0 - nao)
mensalidade
... (and so on)
```

 

### Habitação

O ID's das habitações agora são inalteráveis e constantes, desde que são criadas, para não acontecer o seguinte erro.



- As habitações estavam criadas, numa ordem aleatória.
- Ao ler as habitações o programa não lia o ID, em vez disso, existia uma static que atualizava sempre que era criada uma nova habitação.
- Acontecia que se um condómino tivesse associado a habitação V10 por exemplo, ao ordenar as habitações a mesma habitação V10 seria agora V2 por exemplo. Ou então V10 poderia ja nem existir! 

**Soluçao**

- Portanto achamos melhor ler os IDs em si:
- Para não termos descrepancias de IDs, do género V0..V10, os IDs de todas as habitações de todos os condomínios são guardados num vetor da agencia.
- Desta maneira, percorremos o vetor de 0 a INT_MAX, quando existir um ID que ainda não exista, adicionamos esse ID.



# CRUD

- [x] Criar estruturas
- [x] Ler estruturas
- [x] Atualizar estruturas (parcialmente)
- [x] Apagar estruturas



- Exemplos:
  - Criar, apagar, ler, escrever, condóminos e habitações.
  - Criar, apagar, ler, escrever, condomínios e habitações
  - Requisitar serviços para um condómino
  - Consultar informações de transportes (por destino ou todas)
  - Consultar informações de antigos condóminos (por tempo de ligação ou todos)
  - Ordenar habitações por ID, Área Habitacional ou pagamento mensal (tanto ascendente como descendente)
  - Ordenar condóminos por nome, numero de habitações ou pagamento mensal (tanto ascendente como descendente)



## Features

- O utilizador é avisado caso tente remover um condómino que tenha associado a ele uma ou mais habitações, o mesmo acontece do lado das habitações.

- Um NIF tem de ter obrigatoriamente 9 carateres, todos numéricos e não pode ser igual a nenhum outro NIF de outro condómino registado no condomínio.

- Utilizamos uma biblioteca open-source para apresentar informações relevantes:

  - Vetor de habitaçoes

  - Vetor de condóminos
  - HashTab de antigos condóminos
  - Vetor de antigos condóminos
  - Vetor de transportes (paragens)
  - BST de condomínios
  - Vetor de serviços



# Extra

Criamos uma função para gerar dados com a finalidade de agilizar o processo de testes e correção de erros. A função gera um numero de condomínios a definir pelo utilizador e as características são as seguintes:

- Designação e Localização de cada condomínio (a definir pelo utilizador)

- Número de habitações (a definir pelo utilizador)
  - Morada aleatória (ruas de Manchester  - ficheiro manchester.osm.streets.txt)
- Número de condóminos (a definir pelo utilizador)
  - Nome gerado aleatoriamente (ficheiros first_names.txt e last_names.txt)
  - Número aleatório de habitações associadas (0 a 2)
  - Número aleatório de serviços requisitados (0 a 2)
- Número de transportes (a definir pelo utilizador)
  - Ruas de Manchester
  - Distancia aleatória gerada de 5 a 1000 (metros)
  - Sempre ativos



Esta função foi muito importante para o processo de testes e correção de erros. Decidimos incluir no projeto, desta forma o utilizador, no inicio do programa é perguntado se quer gerar dados ou correr o programa principal.



## Dificuldades

Leitura e escrita de dados.
