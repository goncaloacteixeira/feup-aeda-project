#include <iostream>


#include "classes/CAgency.h"

int main() {

    auto *c1 = new Condominio("con1.txt");
    auto *c2 = new Condominio("con2.txt");
    auto *c3 = new Condominio("con3.txt");

    CAgency a("Joao",919234123);
    a.addCondominio(c1);
    a.addCondominio(c2);
    a.addCondominio(c3);

    Transporte t1("Porto",23,"Gaia");

    vector<Condominio*> temp = a.getCondominios(20);

    cout << t1;

    return 0;
}
