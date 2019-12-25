#include <iostream>


#include "classes/Condominio.h"

int main() {

    string des, loc;
    unsigned npl;

    cout << "Designation: ";
    getline(cin,des);
    cout << "Localization: ";
    getline(cin,loc);
    cout << "Number of cleaning providers: ";
    cin >> npl;

    auto c = Condominio(des,loc,npl);

    cout << "hi\n";

    return 0;
}
