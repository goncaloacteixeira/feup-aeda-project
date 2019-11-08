//
// Created by skidr on 12/10/2019.
//

#include <iostream>
#include <chrono>

#include "classes/Condominio.h"

using namespace std;


int test()
{
    string filename = "condominio.txt";
    auto start = chrono::steady_clock::now();
    Condominio C(filename);
    auto end = chrono::steady_clock::now();
    cout << "The reading took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";


    Habitacao *hab1 = new Apartamento(Morada("Rua 1, Porto, 23, 1234-213"),245,"T2",2);

    C.adicionaHabitacao(hab1);
    C.getCondominos()[0]->adicionaHabitacao(hab1);

    start = chrono::steady_clock::now();
    C.writeToFiles("condominio.txt", "condominos.txt");
    end = chrono::steady_clock::now();
    cout << "The writing took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";

}

int main() {
    test();
    return 0;
}