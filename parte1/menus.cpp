//
// Created by skidr on 10/11/2019.
//

#include "menus.h"
#include <iomanip>

#include "fort.hpp"

void wait() {
    cout << "\n\tPress ENTER key to continue....";
    getchar();
}

int mainMenu() {

    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(70);
    cout << "Condominium Management" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";

    cout << tab << "Name: Condomix\n";

    cout << tab << "[1] Create Condominium from scratch\n";
    cout << tab << "[2] Read from files\n\n";

    cout << tab << "[0] Exit\n";

    int choice;

    cout << tab << "Choice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 2) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a number please\n";
        cout << tab << "Choice: ";

        cin >> choice;
    }
    cin.ignore();

    return choice;
}

string filenameMenu() {
    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(65);
    cout << "Read From Files" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";

    cout << tab << "Name: Condomix\n";

    string filename;

    while (true) {
        cout << tab << "Filename: ";
        getline(cin, filename);

        cout << endl << tab << "Is this filename correct? (Y/N): ";
        string option;
        getline(cin, option);

        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << endl << tab << "Type 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (option == "Y" || option == "y") break;
    }
    return filename;
}

Condominio newCondominium() {
    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(65);
    cout << "New Condominium" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";

    cout << tab << "Name: Condomix\n";

    cout << tab << "Number of Cleaning providers: ";

    int numLimp;

    cin >> numLimp;
    while (!cin.good() || numLimp <= 0) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Number of Cleaning providers: ";

        cin >> numLimp;
    }
    cin.ignore();


    cout << endl << endl << tab << tab << "New Condominium successfully added!" << endl;
    wait();
    return Condominio(numLimp);
}

int condominiumMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(65);
    cout << "Condominium Menu" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";


    // options
    cout << tab << "[1] Condominium Members Menu\n";
    cout << tab << "[2] Add Habitation\n";
    cout << tab << "[3] Remove Habitation\n";
    cout << tab << "[4] Assign Habitation\n";
    cout << tab << "[5] View all Apartments\n";
    cout << tab << "[6] View all Villas\n\n";


    cout << tab << "[7] View Services provided\n";
    cout << tab << "[8] View Income\n\n";

    cout << tab << "[0] Exit\n";

    int choice;

    cout << tab << "Choice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 8) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Choice: ";

        cin >> choice;
    }
    cin.ignore();

    return choice;
}

int membersMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(65);
    cout << "Members Menu" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";


    if (con->getNumCondominos() == 0) {
        cout << tab << "No Members yet\n\n";
    }

    else {
        unsigned int numCon = con->getNumCondominos();
        fort::char_table table;
        table.set_border_style(FT_DOUBLE2_STYLE);

        table << fort::header
              << "Name" << "VAT" << "Habitations" << "Services" << "Monthly Payment" << fort::endr;

        for (unsigned int i = 0; i < numCon; i++) {
            table << con->getCondominos()[i]->getNome() << con->getCondominos()[i]->getNIF();
            int numHab = con->getCondominos()[i]->getNumHabitacoes();
            if (numHab == 0)
                table << 0;
            else {
                string habs = "";
                for (int j = 0; j < numHab; j++) {
                    habs += con->getCondominos()[i]->getHabitacoes()[j]->getID();
                    if (j != numHab - 1) habs += " : ";
                }
                table << habs;
            }

            int numServ = con->getCondominos()[i]->getServicos().size();
            if (numServ == 0)
                table << 0;
            else {
                string servs = "";
                for (int j = 0; j < numServ; j++) {
                    servs += con->getCondominos()[i]->getServicos()[j]->getTipo();
                    if (j != numServ - 1) servs += " : ";
                }
                table << servs;
            }
            table << con->getCondominos()[i]->mensalidadeTotal() << fort::endr;
        }
        table.set_cell_text_align(fort::text_align::center);
        cout << table.to_string() << endl;
    }

    cout << tab << "[1] Add Member\n";
    cout << tab << "[2] Remove Member\n";
    cout << tab << "[3] Sort Members\n";
    cout << tab << "[4] Request a Service for a Member\n\n";

    cout << tab << "[5] Back\n";
    cout << tab << "[0] Exit\n";

    int choice;

    cout << tab << "Choice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 5) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Choice: ";

        cin >> choice;
    }
    cin.ignore();

    return choice;
}

// Checking Functions and Exceptions Classes
bool checkNIF(unsigned int nif) {
    return to_string(nif).size() == 9;
}



void addConMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n";
    cout.width(65);
    cout << "New Member" << endl;
    cout << "\t\t\t\t\t\t\t\t" << "------------------------------------------------------\n\n";

    string name;
    unsigned int nif;

    while (true) {
        cout << tab << "Name: ";
        getline(cin, name);


        cout << endl << tab << "Is this name correct? (Y/N): ";
        string option;
        getline(cin, option);

        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << endl << tab << "Type 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (option == "Y" || option == "y") break;
    }



    while (true) {
        try {
            cout << tab << "VAT number: ";
            cin >> nif;
            while (!cin.good() || nif <= 0 || !checkNIF(nif)) {
                cin.clear();
                cin.ignore();

                cout << endl << tab << "Type a valid number please\n";
                cout << tab << "VAT number: ";

                cin >> nif;
            }
            cin.ignore();
            con->adicionaCondomino(new Condomino(name, nif));
        }
        catch (RepeatedCondomino &e) {
            cout << tab << "That VAT: " << e.getNIF() << " already exists in members\n";
            continue;
        }
        break;
    }

    cout << endl << endl << tab << tab << "Member successfully added!" << endl;
    wait();
}




