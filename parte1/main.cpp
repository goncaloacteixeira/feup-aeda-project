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

/*
    start = chrono::steady_clock::now();
    C.writeToFiles("condominio.txt", "condominos.txt");
    end = chrono::steady_clock::now();
    cout << "The writing took: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " microseconds -> " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milliseconds \n";
*/

    Condomino *con1, *con2;
    try {
        con1 = C.findCon(123123123);
    }
    catch (NoSuchCondomino &e){
        cout << "Condómino não existente: " << e.getNIF() << endl;
    }

    bool error;
    do {
        cout << "nif: ";
        unsigned nif;
        cin >> nif;

        error = false;
        try {
            con2 = C.findCon(nif);
        }
        catch (NoSuchCondomino &e){
            error = true;
            cout << "Condómino não existente: " << e.getNIF() << endl;
        }
        if (!error) cout << con2->getNome() << endl;
    } while(error);

    return 0;
}

int main() {
    test();
    return 0;
}