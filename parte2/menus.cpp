//
// Created by skidr on 28/12/2019.
//

#include "menus.h"

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
    }
    else {
        cout << "\n\tThat condominium does not exist!\n";
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

int membersMenu(Condominio* cond) {
    cout << endl << tittleBars("Manage Condominium");
    cout << "Manage Condominium" << endl;
    cout << tittleBars("Manage Condominium") << endl;

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

