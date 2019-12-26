#include <iostream>


#include "classes/Condominio.h"

int main() {

    auto c = Condominio("con1.txt");

    cout << c.getDesignation();

    return 0;
}
