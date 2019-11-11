//
// Created by skidr on 12/10/2019.
//

#include <iostream>
#include <chrono>

#include "menus.h"

using namespace std;


int test()
{
    string filename = "condominio.txt";
    auto start = chrono::steady_clock::now();
    Condominio C(filename);
    auto end = chrono::steady_clock::now();
    cout << "The reading took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";


    start = chrono::steady_clock::now();
    C.writeToFiles("condominio.txt", "condominos.txt");
    end = chrono::steady_clock::now();
    cout << "The writing took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";

    cout << endl << endl << C.getHabitacoes()[0]->mensalidade;
}

int main() {

    Condominio C("condominio.txt");

    addHabMenu(&C);
    cout << C.getHabitacoes()[C.getNumHabitacoes()-1]->getMorada();

    return 0;
}