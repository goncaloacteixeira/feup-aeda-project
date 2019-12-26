#include <iostream>


#include "classes/Condominio.h"

int main() {


    auto c = Condominio("Con1","Porto",20);

    c.writeToFiles("con1.txt","mem1.txt");

    return 0;
}
