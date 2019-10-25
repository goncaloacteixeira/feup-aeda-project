//
// Created by skidr on 12/10/2019.
//

#include <iostream>

#include "classes/condomino.h"
#include "classes/morada.h"

using namespace std;


int testCondominoOrdenarHabitacoes()
{
    Morada mor1("rua 1","migusa",40, {30,40});
    Morada mor2("rua 2","migusasasd",20, {25,40});
    Morada mor3("rua 4","porto",323, {400,23});
    Apartamento ap1(mor1,25,"t1",1);
    Apartamento ap2(mor2,74,"t4",0);
    Apartamento ap3(mor3,15,"t6",2);

    ap1.mensalidade = 1000;
    ap2.mensalidade = 1500;
    ap3.mensalidade = 900;

    Condomino cond("joao",231241234);

    cond.adicionaHabitacao(&ap1);
    cond.adicionaHabitacao(&ap2);
    cond.adicionaHabitacao(&ap3);

    cout << cond.info() << endl << endl;

    cond.ordenarHabitacoesArea(true);
    cond.ordenarHabitacoesMensalidade(true);

    Apartamento *ap = new Apartamento(mor3,15,"t6",2);

    cond.removeHabitacao(&ap3);
    cout << cond.info();
    return 0;
}

int main() {
    testCondominoOrdenarHabitacoes();
}