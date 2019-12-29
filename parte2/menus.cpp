//
// Created by skidr on 28/12/2019.
//

#include "menus.h"

void wait() {
    cout << "\n\tPress ENTER key to continue....";
    getchar();
}

string tittleBars(string tittle) {
    string res = "";
    for (auto &i : tittle)
        res += "-";
    return res+"\n";
}

CAgency firstMenu() {
    cout << endl << tittleBars("Condominium Management");
    cout << "Condominium Management" << endl;
    cout << tittleBars("Condominium Management") << endl;

    string name, nif = "";
    cout << "\tName: ";
    getline(cin,name);


    while (!checkNIF(nif)) {
        cout << "\tVAT: ";
        getline(cin, nif);
        if (!checkNIF(nif))
            cout << "\tType a valid VAT number please\n";
    }

    return CAgency(name, stoi(nif));
}

int agencyMenu(CAgency *agency) {
    cout << endl << tittleBars("Agency Menu");
    cout << "Agency Menu" << endl;
    cout << tittleBars("Agency Menu") << endl;

    cout << "\t[1] View Condominiums\n";
    cout << "\t[2] Add Condominium\n";
    cout << "\t[3] Remove Condominium\n\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 3) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 3) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }

    return choice;
}

int addCondo(CAgency *agency) {
    cout << endl << tittleBars("Add Condominium");
    cout << "Add Condominium" << endl;
    cout << tittleBars("Add Condominium") << endl;

    cout << "\t[1] Add condominium from scatch\n";
    cout << "\t[2] Add condominium from file\n\n";
    cout << "\t[3] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 3) {
        cin.clear();

        cout << "\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 3) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }

    if (choice == 1) {
        cout << endl << tittleBars("New Condominium");
        cout << "New Condominium" << endl;
        cout << tittleBars("New Condominium") << endl;

        string des, loc;

        cout << "\tDesignation: ";
        getline(cin,des);
        cout << "\tLocation: ";
        getline(cin, loc);

        int numLimp = 0;

        while (!cin.good() || numLimp <= 0) {
            cout << "\tNumber of Cleaning providers: ";
            cin >> numLimp;
            if (!cin.good() || numLimp <= 0) {
                cout << "\tType a valid number please\n";
                cin.clear();
                cin.ignore();
            }
        }
        cin.ignore();

        agency->addCondominio(new Condominio(des,loc,numLimp));
        cout << "\n\tCondominium added successfully!\n";
        wait();
        return 1;
    }
    else if (choice == 2) {
        cout << endl << "----------------------\n";
        cout << "Read Condominium" << endl;
        cout << "----------------------\n\n";

        string filename;

        while (true) {
            cout << "Filename (type -1 to CANCEL): ";
            getline(cin, filename);

            if (filename == "-1") return 3;

            cout << endl << "Is this filename correct? (Y/N): ";
            string option;
            getline(cin, option);

            bool flag = false;
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;

            while (!flag) {
                cout << endl << "Type 'Y' or 'N' please: ";

                getline(cin, option);
                if (option == "Y" || option == "N" || option == "y" || option == "n")
                    flag = true;
            }

            if (option == "Y" || option == "y") break;
        }

        agency->addCondominio(new Condominio(filename));
        cout << "\n\tCondominium added successfully!\n";
        wait();
        return 2;
    }
    else if (choice == 3) {
        return 3;
    }
    else if (choice == 0) {
        return 0;
    }
}

void removeCondo(CAgency *agency) {
    cout << endl << tittleBars("Remove Condominium");
    cout << "Remove Condominium" << endl;
    cout << tittleBars("Remove Condominium") << endl;

    string des, loc;

    cout << "\tDesignation: ";
    getline(cin,des);
    cout << "\tLocation: ";
    getline(cin,loc);

    if (agency->findCondominio(des,loc) != nullptr) {
        agency->removeCondominio(agency->findCondominio(des,loc));
        cout << "\n\tCondominium successfully removed!\n";
        wait();
    }
    else {
        cout << "\n\tThat condominium does not exist!\n";
        wait();
    }
}

int viewCondos(CAgency *agency) {
    cout << endl << tittleBars("View Condominiums");
    cout << "View Condominiums" << endl;
    cout << tittleBars("View Condominiums") << endl;

    cout << printTable(agency->getCondominios()) << endl;

    cout << "\t[1] Select a specific condominium\n\n";
    cout << "\t[2] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 2) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 2) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }
    return choice;
}

Condominio *speficifyCondo(CAgency *agency) {
    string des,loc;
    cout << "\n\tDesignation: ";
    getline(cin,des);
    cout << "\tLocation: ";
    getline(cin,loc);

    if (agency->findCondominio(des,loc) == nullptr) {
        cout << "\n\tCouldn't find that condominium!\n";
        return nullptr;
    }
    else {
        return agency->findCondominio(des,loc);
    }
}

int condoMenu() {
    cout << endl << tittleBars("Manage Condominium");
    cout << "Manage Condominium" << endl;
    cout << tittleBars("Manage Condominium") << endl;

    cout << "\t[1] Members Menu\n";
    cout << "\t[2] Habitations Menu\n";
    cout << "\t[3] Services Menu\n";
    cout << "\t[4] Revenue\n\n";
    cout << "\t[5] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 5) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 5) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }
    return choice;
}

// Members Menu ---

int membersMenu(Condominio* cond) {
    cout << endl << tittleBars("Manage Members");
    cout << "Manage Members" << endl;
    cout << tittleBars("Manage Members") << endl;

    cout << endl << printTable(cond->getCondominos()) << endl;

    cout << "\t[1] Add Member\n";
    cout << "\t[2] Remove Member\n";
    cout << "\t[3] Sort Members\n";
    cout << "\t[4] Request a Service for a member\n\n";
    cout << "\t[5] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 5) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 5) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }
    return choice;
}

void addMemberMenu(Condominio *cond) {
    cout << endl << tittleBars("Add Member");
    cout << "Add Member" << endl;
    cout << tittleBars("Add Member") << endl;

    string name;
    string nif;

    while (true) {
        cout << "\tName (type -1 to CANCEL): ";
        getline(cin, name);

        if (name == "-1") {
            return;
        }

        cout << "\tIs this name correct? (Y/N): ";
        string option;
        getline(cin, option);

        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << endl << "\tType 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (option == "Y" || option == "y") break;
    }

    while (true) {
        try {
            cout << "\tVAT number (type -1 to CANCEL): ";
            getline(cin,nif);
            if (nif == "-1")
                return;
            while (!cin.good() || stoi(nif) <= 0 || !checkNIF(nif)) {
                cout << "\tType a valid number please\n";
                cout << "\tVAT number (type -1 to CANCEL): ";
                getline(cin,nif);
                if (nif == "-1")
                    return;
            }
            cond->adicionaCondomino(new Condomino(name, stoi(nif)));
        }
        catch (InvalidNIF &e) {
            cout << "That VAT number: " << e.getNIF() << " already exists in members\n";
            continue;
        }
        break;
    }

    cout << endl << "\t\tMember successfully added!" << endl;
    wait();
}

void removeMemberMenu(Condominio *cond) {
    cout << endl << tittleBars("Remove Member");
    cout << "Remove Member" << endl;
    cout << tittleBars("Remove Member") << endl;

    string nif;
    Condomino *toRemove;


    while (true) {
        try {
            cout << "\tVAT number (type -1 to CANCEL): ";
            getline(cin,nif);
            if (nif == "-1")
                return;
            while (!cin.good() || stoi(nif) <= 0 || !checkNIF(nif)) {
                cout << "\tType a valid number please\n";
                cout << "\tVAT number (type -1 to CANCEL): ";
                getline(cin,nif);
                if (nif == "-1")
                    return;
            }
            toRemove = cond->findCon(stoi(nif));
        }
        catch (NoSuchCondomino &e) {
            cout << "That VAT number: " << e.getNIF() << " does not exist in members\n";
            continue;
        }
        break;
    }

    if (toRemove->getNumHabitacoes() != 0) {
        cout << "\tCAREFUL: You are removing a member who has habitations assigned!\n";
        cout << "\tProceed (y/n)? ";
        bool flag = false;
        string option;
        getline(cin, option);

        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << "\tType 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (option == "Y" || option == "y") {
            for (auto &h : toRemove->getHabitacoes()) {
                toRemove->removeHabitacao(h);
            }
            cout << "\tHow long have that member been assigned to this condominium? ";
            string time;
            getline(cin, time);
            cond->removeCondomino(toRemove, stoi(time));
            cout << endl << "\t\tMember successfully removed!" << endl;
            wait();
            return;
        }
        else {
            return;
        }
    }

    cout << "\tHow long have that member been assigned to this condominium?: ";
    string time;
    getline(cin, time);
    cond->removeCondomino(toRemove, stoi(time));

    cout << endl << "\t\tMember successfully removed!" << endl;
    wait();
}

int sortMembersMenu(Condominio *cond) {
    cout << endl << tittleBars("Sort Members");
    cout << "Sort Members" << endl;
    cout << tittleBars("Sort Members") << endl;

    cout << "\t[1] Sort by Name (A-Z)\n";
    cout << "\t[2] Sort by Number of Properties (descendant)\n";
    cout << "\t[3] Sort by Number of Properties (ascendant)\n";
    cout << "\t[4] Sort by Monthly Payment (descendant)\n";
    cout << "\t[5] Sort by Monthly Payment (ascendant)\n\n";
    cout << "\t[6] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 6) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 6) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }

    switch (choice) {
        case 1:
            cond->ordenarCond("name");
            break;
        case 2:
            cond->ordenarCond("number-descendant");
            break;
        case 3:
            cond->ordenarCond("number-ascendant");
            break;
        case 4:
            cond->ordenarCond("pay-descendant");
            break;
        case 5:
            cond->ordenarCond("pay-ascendant");
            break;
        default:
            return choice;
    }
    return choice;
}




