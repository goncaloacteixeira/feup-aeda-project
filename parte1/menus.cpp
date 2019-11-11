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

int firstMenu() {

    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Condominium Management" << endl;
    cout << "------------------------------------------------------\n\n";

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

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "      Read from files" << endl;
    cout << "------------------------------------------------------\n\n";
    cout << tab << "Name: Condomix\n";

    string filename;

    while (true) {
        cout << tab << "Filename (type -1 to CANCEL): ";
        getline(cin, filename);

        if (filename == "-1") return filename;

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

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    New Condominium" << endl;
    cout << "------------------------------------------------------\n\n";
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

int mainMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Condominium Menu" << endl;
    cout << "------------------------------------------------------\n\n";

    // options
    cout << tab << "[01] Condominium Members Menu\n";
    cout << tab << "[02] Add Habitation\n";
    cout << tab << "[03] Remove Habitation\n";
    cout << tab << "[04] Assign Habitation\n";
    cout << tab << "[05] Unassign Habitation\n";
    cout << tab << "[06] Sort Habitations\n";
    cout << tab << "[07] View all Habitations\n";
    cout << tab << "[08] View all Apartments\n";
    cout << tab << "[09] View all Villas\n\n";


    cout << tab << "[10] View Services provided\n";
    cout << tab << "[11] View Income\n\n";

    cout << tab << "[0] Exit\n";

    int choice;

    cout << tab << "Choice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 11) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Choice: ";

        cin >> choice;
    }
    cin.ignore();

    return choice;
}

void printTable(vector<Condomino *> condominos) {
    unsigned int numCon = condominos.size();
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    table << fort::header
          << "Name" << "VAT" << "Habitations" << "Services" << "Monthly Payment" << fort::endr;

    for (unsigned int i = 0; i < numCon; i++) {
        table << condominos[i]->getNome() << condominos[i]->getNIF();
        int numHab = condominos[i]->getNumHabitacoes();
        if (numHab == 0)
            table << 0;
        else {
            string habs;
            for (int j = 0; j < numHab; j++) {
                habs += condominos[i]->getHabitacoes()[j]->getID();
                if (j != numHab - 1) habs += " : ";
            }
            table << habs;
        }

        int numServ = condominos[i]->getServicos().size();
        if (numServ == 0)
            table << 0;
        else {
            string servs;
            for (int j = 0; j < numServ; j++) {
                servs += condominos[i]->getServicos()[j]->getTipo();
                if (j != numServ - 1) servs += " : ";
            }
            table << servs;
        }
        table << condominos[i]->mensalidadeTotal() << fort::endr;
    }
    table.set_cell_text_align(fort::text_align::center);
    cout << table.to_string() << endl;
}

void printTable(vector<Habitacao *> habitacoes) {
    unsigned int numHabs = habitacoes.size();
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    table << fort::header
          << "ID" << "Type of Habitation" << "Address" << "Habitation's Area" << "Status" << "External Area" << "Typology" << "Pool" << "Floor" << "Monthly Payment" << fort::endr;

    for (unsigned int i = 0; i < numHabs; i++) {
        table << habitacoes[i]->getID();
        (habitacoes[i]->getID()[0] == 'V') ? table << "Villa" : table << "Apartment";

        table << habitacoes[i]->getMorada();
        table << habitacoes[i]->getAreaHabitacional();

        (habitacoes[i]->getEstado()) ? table << "occupied" : table << "unoccupied";

        if (habitacoes[i]->getID()[0] == 'V') {
            table << habitacoes[i]->extraInfo()[0] << "-" << habitacoes[i]->extraInfo()[1] << "-";
        } else {
            table << "-" << habitacoes[i]->extraInfo()[0] << "-" << habitacoes[i]->extraInfo()[1];
        }
        table << habitacoes[i]->mensalidade << fort::endr;
    }
    table.set_cell_text_align(fort::text_align::center);
    cout << table.to_string() << endl;
}

void printTable(vector<Servico *> servicos) {
    unsigned int numServ = servicos.size();
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    table << fort::header
          << "Service" << "Provider" << "Cost" << fort::endr;

    for (auto serv : servicos)
        table << serv->getTipo() << serv->getPrestador() << serv->getCusto() << fort::endr;

    table.set_cell_text_align(fort::text_align::center);
    cout << table.to_string() << endl;
}

int membersMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Members Menu" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumCondominos() == 0) {
        cout << tab << "No Members yet\n\n";
    }

    else {
        printTable(con->getCondominos());
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

int addConMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    New Member" << endl;
    cout << "------------------------------------------------------\n\n";
    string name;
    unsigned int nif;

    while (true) {
        cout << tab << "Name (type -1 to CANCEL): ";
        getline(cin, name);

        if (name == "-1") return -1;

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
            cout << tab << "VAT number (type -1 to CANCEL): ";
            cin >> nif;
            if (nif == -1) return -1;
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

int rmConMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Remove Member" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumCondominos() == 0) {
        cout << tab << "Nothing to Remove\n";
    }
    else {
        int nif;

        while (true) {
            try {
                cout << tab << "VAT number (type -1 to CANCEL): ";
                cin >> nif;

                if (nif == -1) return -1;

                while (!cin.good() || nif <= 0 || !checkNIF(nif)) {
                    cin.clear();
                    cin.ignore();

                    cout << endl << tab << "Type a valid number please\n";
                    cout << tab << "VAT number: ";

                    cin >> nif;
                }
                cin.ignore();
                Condomino* condomino = con->findCon(nif);
                con->removeCondomino(condomino);
            }
            catch (NoSuchCondomino &e) {
                cout << tab << "Person with VAT: " << e.getNIF() << " does not exist in members\n";
                continue;
            }
            break;
        }

        cout << endl << endl << tab << tab << "Member successfully removed!" << endl;
    }
    wait();
    return 0;
}

int sortConMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Sort Members" << endl;
    cout << "------------------------------------------------------\n\n";

    cout << tab << "[1] Sort Members by Monthly Payment in descending order\n";
    cout << tab << "[2] Sort Members by Monthly Payment in ascending order\n";
    cout << tab << "[3] Sort Members by Name in descending order\n";
    cout << tab << "[4] Sort Members by Name in ascending order\n";

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


    if (choice == 1)
        con->ordenarCond("pay-descending");
    else if (choice == 2)
        con->ordenarCond("pay-ascending");
    else if (choice == 3)
        con->ordenarCond("name-descending");
    else if (choice == 4)
        con->ordenarCond("name-ascending");

    if (choice != 0 && choice != 5)
        cout << endl << endl << tab << tab << "Members successfully sorted!" << endl;

    return choice;
}

int rqServiceMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Request Service" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumCondominos() == 0) {
        cout << tab << "No members!\n";
    } else {
        int nif;

        Condomino *condomino;
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
                condomino = con->findCon(nif);
            }
            catch (NoSuchCondomino &e) {
                cout << tab << "Person with VAT: " << e.getNIF() << " does not exist in members\n";
                continue;
            }
            break;
        }

        cout << tab << tab << "Request a service for " << condomino->getNome() << endl << endl;

        cout << tab << "[01] Cleaning\n";
        cout << tab << "[02] Hairdresser\n";
        cout << tab << "[03] Car Cleaner\n";
        cout << tab << "[04] Security\n";
        cout << tab << "[05] Babysitter\n";
        cout << tab << "[06] Plumber\n";
        cout << tab << "[07] Gardener\n";
        cout << tab << "[08] Electrician\n";

        // todo - add more services


        cout << tab << "[09] Back\n";
        cout << tab << "[0] Exit\n";


        int choice;

        cout << tab << "Choice: ";

        cin >> choice;
        while (!cin.good() || choice < 0 || choice > 9) {
            cin.clear();
            cin.ignore();

            cout << endl << tab << "Type a valid number please\n";
            cout << tab << "Choice: ";

            cin >> choice;
        }
        cin.ignore();


        if (choice == 0 || choice == 9)
            return choice;

        bool flag = false;
        string prestador;
        string type;

        switch (choice) {
            case 1:
                while (!flag) {
                    cout << tab << "Provider: ";
                    getline(cin, prestador);
                    if (con->getNumPrestLimpeza() == con->prestLimpezaAtuais().size()) {
                        for (const string &provider : con->prestLimpezaAtuais())
                            if (provider == prestador) {
                                flag = true;
                                break;
                            }
                        if (!flag)
                            cout << tab << "That provider cannot be added. Maximum cleaning providers reached!\n";
                    }
                    flag = true;
                }
                type = "Cleaning";
                break;
            case 2:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Hairdresser";
                break;
            case 4:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Security";
                break;
            case 5:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Babysitter";
                break;
            case 6:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Plumber";
                break;
            case 7:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Gardener";
                break;
            case 8:
                cout << tab << "Provider: ";
                getline(cin, prestador);
                type = "Electrician";
                break;
            default:
                break;
        }

        float custo;
        cout << tab << "Custo: ";
        cin >> custo;
        while (!cin.good() || choice < 0) {
            cin.clear();
            cin.ignore();

            cout << endl << tab << "Type a valid number please\n";
            cout << tab << "Custo: ";

            cin >> custo;
        }
        cin.ignore();


        auto *servico = new Servico(custo, prestador, type);
        condomino->adicionaServico(servico);
        con->adicionaServico(servico);

        cout << endl << endl << tab << tab << "Service successfully requested!" << endl;
        wait();
        return choice;
    }
    return -1;
}

int addHabMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    New Habitation" << endl;
    cout << "------------------------------------------------------\n\n";

    int choice;

    cout << tab << "[1] Apartment\n";
    cout << tab << "[2] Villa\n\n";

    cout << tab << "[3] Back\n";
    cout << tab << "[0] Exit\n";

    cout << tab << "Choice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 9) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Choice: ";

        cin >> choice;
    }
    cin.ignore();

    if (choice == 0 || choice == 3) return choice;

    string address;

    while (true) {
        cout << tab << "Address (Street, Location, Number, Zip-Code: ";
        getline(cin, address);


        cout << "\tIs this address correct and as asked? (Y/N): ";
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

    cout << tab << "Habitation's Area: ";
    float habArea;
    cin >> habArea;
    while (!cin.good() || choice < 0) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Habitation's Area: ";

        cin >> habArea;
    }
    cin.ignore();

    cout << tab << "Monthly Payment: ";
    float mensalidade;
    cin >> mensalidade;
    while (!cin.good() || choice < 0) {
        cin.clear();
        cin.ignore();

        cout << endl << tab << "Type a valid number please\n";
        cout << tab << "Monthly Payment: ";

        cin >> mensalidade;
    }
    cin.ignore();


    if (choice == 1) {
        string type;
        cout << tab << "Typology (T0, T1, etc.): ";
        getline(cin, type);

        cout << tab << "Floor: ";
        int floor;
        cin >> floor;
        while (!cin.good()) {
            cin.clear();
            cin.ignore();

            cout << endl << tab << "Type a valid number please\n";
            cout << tab << "Floor: ";

            cin >> floor;
        }
        cin.ignore();

        con->adicionaHabitacao(new Apartamento(Morada(address),habArea,type,floor,mensalidade));
    }

    else if (choice == 2) {
        float extArea;
        cout << tab << "External Area: ";
        cin >> extArea;
        while (!cin.good() || extArea < 0) {
            cin.clear();
            cin.ignore();

            cout << endl << tab << "Type a valid number please\n";
            cout << tab << "External Area: ";

            cin >> extArea;
        }
        cin.ignore();

        string option;
        while (true) {
            cout << tab << "Pool? (Y/N): ";

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
            if (flag) break;
        }
        bool pool;
        (option == "Y" || option == "y") ? pool = true : pool = false;

        con->adicionaHabitacao(new Vivenda(Morada(address),habArea,extArea,pool,mensalidade));
    }

    cout << endl << endl << tab << tab << "Habitation successfully added!" << endl;
    wait();
    return choice;
}

int rmHabMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Remove Habitation" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumHabitacoes() == 0) {
        cout << tab << "Nothing to Remove\n";
    }
    else {
        string id;
        while (true) {
            try {
                cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
                getline(cin, id);
                if (id == "-1") return -1;
                Habitacao* habitacao = con->findHab(id);
                if (habitacao->getEstado()) {
                    cout << tab << "That habitation is occupied. Cannot remove\n";
                    wait();
                    return -1;
                }
                con->removeHabitacao(habitacao);
            }
            catch (NoSuchHabitation &e) {
                cout << "\tHabitation with ID: " << e.getID() << " does not exist on this condominium\n";
                continue;
            }
            break;
        }
        cout << endl << endl << tab << tab << "Habitation successfully removed!" << endl;
    }
    wait();
}

int assignHab(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Assign Habitation" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumHabitacoes() == 0 || con->getNumCondominos() == 0) {
        cout << tab << "Cannot assign member to habitation\n";
        wait();
        return -1;
    }
    vector<Habitacao *> availableHabs;

    for (unsigned int i = 0; i < con->getNumHabitacoes(); i++) {
        if (!con->getHabitacoes()[i]->getEstado())
            availableHabs.push_back(con->getHabitacoes()[i]);
    }

    if (availableHabs.empty()) {
        cout << tab << "No habitations available to assign\n";
        wait();
        return -1;
    }

    cout << tab << "Choose a member to assign habitation\n";
    printTable(con->getCondominos());

    int nif;

    Condomino* condomino;
    while (true) {
        try {
            cout << tab << "VAT number (-1 to CANCEL): ";
            cin >> nif;
            if (nif == -1) return -1;
            while (!cin.good() || nif <= 0 || !checkNIF(nif)) {
                cin.clear();
                cin.ignore();
                cout << endl << tab << "Type a valid number please\n";
                cout << tab << "VAT number: ";

                cin >> nif;
                if (nif == -1) return -1;
            }
            cin.ignore();
            condomino = con->findCon(nif);
        }
        catch (NoSuchCondomino &e) {
            cout << "\tPerson with VAT: " << e.getNIF() << " does not exist in members\n";
            continue;
        }
        break;
    }


    cout << tab << "Choose an habitation to assign\n";
    printTable(availableHabs);

    string id;
    Habitacao* habitacao;
    while (true) {
        try {
            cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
            getline(cin, id);
            if (id == "-1") return -1;

            bool flag = false;
            for (auto & availableHab : availableHabs) {
                if (id == availableHab->getID()) {
                    flag = true;
                    break;
                }
            }
            if (!flag) throw id;
            habitacao = con->findHab(id);
        }
        catch (NoSuchHabitation &e) {
            cout << "\tHabitation with ID: " << e.getID() << " does not exist on this condominium\n";
            continue;
        }
        catch (string &e) {
            cout << "\tHabitation with ID: " << e << " is not available\n";
            continue;
        }
        break;

    }

    condomino->adicionaHabitacao(habitacao);
    cout << endl << endl << tab << tab << "Habitation successfully assigned!" << endl;
    wait();
    return 0;
}

int unassignHab(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Unassign Habitation" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getNumHabitacoes() == 0 || con->getNumCondominos() == 0) {
        cout << tab << "Cannot assign member to habitation\n";
        wait();
        return -1;
    }

    vector<Habitacao *> availableHabs;

    for (unsigned int i = 0; i < con->getNumHabitacoes(); i++) {
        if (con->getHabitacoes()[i]->getEstado())
            availableHabs.push_back(con->getHabitacoes()[i]);
    }

    if (availableHabs.empty()) {
        cout << tab << "No habitations available to unassign\n";
        wait();
        return -1;
    }

    vector<Condomino *> condominos;
    for (unsigned int i = 0; i < con->getNumCondominos(); i++) {
        if (con->getCondominos()[i]->getHabitacoes().size() != 0)
            condominos.push_back(con->getCondominos()[i]);
    }
    if (condominos.empty()) {
        cout << tab << "No members available to unassign\n";
        wait();
        return -1;
    }

    int nif;
    Condomino* condomino;
    printTable(condominos);
    while (true) {
        try {
            cout << tab << "VAT number (-1 to CANCEL): ";
            cin >> nif;
            if (nif == -1) return -1;
            while (!cin.good() || nif <= 0 || !checkNIF(nif)) {
                cin.clear();
                cin.ignore();
                cout << endl << tab << "Type a valid number please\n";
                cout << tab << "VAT number: ";

                cin >> nif;
                if (nif == -1) return -1;
            }

            bool flag = false;
            for (auto & c : condominos) {
                if (nif == c->getNIF()) {
                    flag = true;
                    break;
                }
            }
            if (!flag) throw nif;

            cin.ignore();
            condomino = con->findCon(nif);
        }
        catch (NoSuchCondomino &e) {
            cout << "\tPerson with VAT: " << e.getNIF() << " does not exist in members\n";
            continue;
        }
        catch (int &e) {
            cout << "\tPerson with VAT: " << e  << " has no habitations assigned\n";
            continue;
        }
        break;
    }

    availableHabs.clear();

    for (auto hab : condomino->getHabitacoes())
        availableHabs.push_back(hab);

    cout << tab << "Choose an habitation to unassign\n";
    printTable(availableHabs);

    string id;
    Habitacao* habitacao;
    while (true) {
        try {
            cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
            getline(cin, id);
            if (id == "-1") return -1;

            bool flag = false;
            for (auto & availableHab : availableHabs) {
                if (id == availableHab->getID()) {
                    flag = true;
                    break;
                }
            }
            if (!flag) throw id;
            habitacao = con->findHab(id);
        }
        catch (NoSuchHabitation &e) {
            cout << "\tHabitation with ID: " << e.getID() << " does not exist on this condominium\n";
            continue;
        }
        catch (string &e) {
            cout << "\tHabitation with ID: " << e << " is not available\n";
            continue;
        }
        break;
    }
    condomino->removeHabitacao(habitacao);

}

int sortHabMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Sort Habitation" << endl;
    cout << "------------------------------------------------------\n\n";

    cout << tab << "[1] Sort Habitations by Monthly Payment in descending order\n";
    cout << tab << "[2] Sort Habitations by Monthly Payment in ascending order\n";
    cout << tab << "[3] Sort Habitations by Habitation's Area in descending order\n";
    cout << tab << "[4] Sort Habitations by Habitation's Area in ascending order\n";


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


    if (choice == 1)
        con->ordernarHab("pay-descending");
    else if (choice == 2)
        con->ordernarHab("pay-ascending");
    else if (choice == 3)
        con->ordernarHab("area-descending");
    else if (choice == 4)
        con->ordernarHab("area-ascending");

    if (choice != 0 && choice != 5) {
        cout << endl << endl << tab << tab << "Habitations successfully sorted!" << endl;
        wait();
    }

    return choice;
}

void viewHabs(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    View Habitations" << endl;
    cout << "------------------------------------------------------\n\n";

    printTable(con->getHabitacoes());
    wait();
}

void viewAps(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    View Apartments" << endl;
    cout << "------------------------------------------------------\n\n";

    vector<Habitacao *> habs;
    for (auto hab : con->getHabitacoes())
        if (hab->getID()[0] == 'A')
            habs.push_back(hab);

    printTable(habs);
    wait();
}

void viewVivs(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    View Villas" << endl;
    cout << "------------------------------------------------------\n\n";

    vector<Habitacao *> habs;
    for (auto hab : con->getHabitacoes())
        if (hab->getID()[0] == 'V')
            habs.push_back(hab);

    printTable(habs);
    wait();
}

void servicesProvided(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Services Provided" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getServicos().empty()) {
        cout << tab << "Nothing to show\n";
        wait();
        return;
    }

    printTable(con->getServicos());
    wait();
}

void incomeMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Income Menu" << endl;
    cout << "------------------------------------------------------\n\n";

    if (con->getServicos().empty()) {
        cout << tab << "Nothing to show\n";
        wait();
        return;
    }

    cout << tab << "Monthly Profits: " << con->calcReceitas();
    wait();
}

int exitMenu(Condominio *con) {
    string tab = "\t\t\t";

    cout << endl << "------------------------------------------------------\n";
    cout << tab << "    Exit Menu" << endl;
    cout << "------------------------------------------------------\n\n";

    string option;
    while (true) {
        cout << "\tDo you want to save the information (Y/N)? (type -1 to CANCEL): ";
        getline(cin, option);

        if (option == "-1") return -1;


        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << endl << tab << "Type 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (flag) break;
    }

    if (option == "y" || option == "Y")
        return 0;
    else
        return 1;
}
