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

    if (agency->getCondominios().isEmpty()) {
        cout << endl << "\tNothing to show\n";
        return 3;
    }

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
        wait();
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
    cout << "\t[3] View Provided Services\n";
    cout << "\t[4] Former Members Menu\n";
    cout << "\t[5] Transports Menu\n";
    cout << "\t[6] Revenue\n\n";

    cout << "\t[7] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 7) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 7) {
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
        cout << "\tWARNING: You are removing a member who has habitations assigned!\n";
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

    cout << "\tHow long have that member been assigned to this condominium? ";
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

int rqService(Condominio *cond) {
    cout << endl << tittleBars("Request a Service for a Member");
    cout << "Request a Service for a Member" << endl;
    cout << tittleBars("Request a Service for a Member") << endl;

    if (cond->getNumCondominos() == 0) {
        cout << "No members!\n";
        return 16;
    }

    string nif;
    Condomino *condomino;
    while (true) {
        try {
            cout << "\tVAT number (type -1 to CANCEL): ";
            getline(cin,nif);
            if (nif == "-1")
                return 16;
            while (!cin.good() || stoi(nif) <= 0 || !checkNIF(nif)) {
                cout << "\tType a valid number please\n";
                cout << "\tVAT number (type -1 to CANCEL): ";
                getline(cin,nif);
                if (nif == "-1")
                    return 16;
            }
            condomino = cond->findCon(stoi(nif));
        }
        catch (NoSuchCondomino &e) {
            cout << "That VAT number: " << e.getNIF() << " does not exist in members\n";
            continue;
        }
        break;
    }

    cout << "\tRequest a service for " << condomino->getNome() << endl << endl;

    cout << "\t[01] Cleaning\n";
    cout << "\t[02] Hairdresser\n";
    cout << "\t[03] Car Cleaner\n";
    cout << "\t[04] Security\n";
    cout << "\t[05] Babysitter\n";
    cout << "\t[06] Plumber\n";
    cout << "\t[07] Gardener\n";
    cout << "\t[08] Electrician\n";
    cout << "\t[09] Cook\n";
    cout << "\t[10] Car Usher\n";
    cout << "\t[11] Spa\n";
    cout << "\t[12] Cinema\n";
    cout << "\t[13] Event Organizer\n";
    cout << "\t[14] Petsitter\n";
    cout << "\t[15] Painter\n\n";


    cout << "\t[16] Back\n";
    cout << "\t[0] Exit\n";


    int choice;

    cout << "\tChoice: ";

    cin >> choice;
    while (!cin.good() || choice < 0 || choice > 16) {
        cin.clear();
        cin.ignore();

        cout << "\tType a valid number please\n";
        cout << "\tChoice: ";

        cin >> choice;
    }
    cin.ignore();


    if (choice == 0 || choice == 16)
        return choice;

    bool flag = false;
    string prestador;
    string type;

    switch (choice) {
        case 1:
            while (!flag) {
                cout << "\tProvider: ";
                getline(cin, prestador);
                if (cond->getNumPrestLimpeza() == cond->prestLimpezaAtuais().size()) {
                    for (const string &provider : cond->prestLimpezaAtuais())
                        if (provider == prestador) {
                            flag = true;
                            break;
                        }
                    if (!flag)
                        cout << "\tThat provider cannot be added. Maximum cleaning providers reached!\n";
                }
                flag = true;
            }
            type = "Cleaning";
            break;
        case 2:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Hairdresser";
            break;
        case 3:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Car Cleaner";
            break;
        case 4:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Security";
            break;
        case 5:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Babysitter";
            break;
        case 6:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Plumber";
            break;
        case 7:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Gardener";
            break;
        case 8:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Electrician";
            break;
        case 9:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Cook";
            break;
        case 10:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Car Usher";
            break;
        case 11:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Spa";
            break;
        case 12:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Cinema";
            break;
        case 13:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Event Organizer";
            break;
        case 14:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Petsitter";
            break;
        case 15:
            cout << "\tProvider: ";
            getline(cin, prestador);
            type = "Painter";
            break;
        default:
            break;
    }

    float custo;
    cout << "\tCusto: ";
    cin >> custo;
    while (!cin.good() || choice < 0) {
        cin.clear();
        cin.ignore();

        cout << "\tType a valid number please\n";
        cout << "\tCusto: ";

        cin >> custo;
    }
    cin.ignore();


    auto *servico = new Servico(custo, prestador, type);
    condomino->adicionaServico(servico);
    cond->adicionaServico(servico);

    cout << endl << "\tService successfully requested!" << endl;
    wait();
    return choice;
}


// ---

int habitationsMenu(Condominio *cond) {
    cout << endl << tittleBars("Manage Habitations");
    cout << "Manage Habitations" << endl;
    cout << tittleBars("Manage Habitations") << endl;

    cout << endl << printTable(cond->getHabitacoes()) << endl;

    cout << "\t[1] Add Habitation\n";
    cout << "\t[2] Remove Habitation\n";
    cout << "\t[3] Assign Habitation\n";
    cout << "\t[4] Unasign Habitation\n";
    cout << "\t[5] Sort Habitations\n";
    cout << "\t[6] View only Apartments\n";
    cout << "\t[7] View only Villas\n\n";

    cout << "\t[8] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 8) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 8) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }
    return choice;
}

int addHabMenu(Condominio *cond) {
    cout << endl << tittleBars("Add Habitation");
    cout << "Add Habitation" << endl;
    cout << tittleBars("Add Habitation") << endl;

    cout << "\tSelect type of habitation: \n";
    cout << "\t[1] Apartment\n";
    cout << "\t[2] Villa\n\n";

    cout << "\t[3] Back\n";
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
    if (choice == 0 || choice == 3) {
        return choice;
    }
    string address;

    while (true) {
        cout << "\tAddress (Street, Location, Number, Zip-Code): ";
        getline(cin, address);

        cout << "\tIs this address correct? (Y/N): ";
        string option;
        getline(cin, option);

        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << "\tType 'Y' or 'N' please: ";

            getline(cin, option);
            if (option == "Y" || option == "N" || option == "y" || option == "n")
                flag = true;
        }

        if (option == "Y" || option == "y") break;
    }

    cout  << "\tHabitation's Area: ";
    float habArea;
    cin >> habArea;
    while (!cin.good() || choice < 0) {
        cin.clear();
        cin.ignore();

        cout << "\tType a valid number please\n";
        cout << "\tHabitation's Area: ";

        cin >> habArea;
    }
    cin.ignore();

    cout << "\tMonthly Payment: ";
    float mensalidade;
    cin >> mensalidade;
    while (!cin.good() || choice < 0) {
        cin.clear();
        cin.ignore();

        cout << "\tType a valid number please\n";
        cout << "\tMonthly Payment: ";

        cin >> mensalidade;
    }
    cin.ignore();

    if (choice == 1) {
        string type;
        cout << "\tTypology (T0, T1, etc.): ";
        getline(cin, type);

        cout << "\tFloor: ";
        int floor;
        cin >> floor;
        while (!cin.good()) {
            cin.clear();
            cin.ignore();

            cout << "\tType a valid number please\n";
            cout << "\tFloor: ";

            cin >> floor;
        }
        cin.ignore();
        cond->adicionaHabitacao(new Apartamento(address,habArea,type,floor,mensalidade));
    }

    else if (choice == 2) {
        float extArea;
        cout << "\tExternal Area: ";
        cin >> extArea;
        while (!cin.good() || extArea < 0) {
            cin.clear();
            cin.ignore();

            cout << endl << "\tType a valid number please\n";
            cout << "\tExternal Area: ";

            cin >> extArea;
        }
        cin.ignore();

        string option;
        while (true) {
            cout << "\tPool? (Y/N): ";

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
            if (flag) break;
        }
        bool pool;
        (option == "Y" || option == "y") ? pool = true : pool = false;

        cond->adicionaHabitacao(new Vivenda(address,habArea,extArea,pool,mensalidade));
    }

    cout << endl << "\tHabitation successfully added!" << endl;
    wait();
    return choice;
}

void rmHabMenu(Condominio *cond) {
    cout << endl << tittleBars("Remove Habitation");
    cout << "Remove Habitation" << endl;
    cout << tittleBars("Remove Habitation") << endl;

    if (cond->getNumHabitacoes() == 0) {
        cout << "\tNothing to Remove\n";
    }
    else {
        string id;
        Habitacao* habitacao;
        while (true) {
            try {
                cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
                getline(cin, id);
                if (id == "-1")
                    return;
                habitacao = cond->findHab(id);
            }
            catch (NoSuchHabitation &e) {
                cout << "\tHabitation with ID: " << e.getID() << " does not exist on this condominium\n";
                continue;
            }
            break;
        }

        if (habitacao->getEstado()) {
            cout << "\tWARNING: You are removing an occupied habitation!\n";
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
                for (auto &c : cond->getCondominos()) {
                    for (auto &h : c->getHabitacoes()) {
                        if (h == habitacao) {
                            c->removeHabitacao(h);
                            break;
                        }
                    }
                }
                cond->removeHabitacao(habitacao);
            }
            else {
                return;
            }
        } else {
            cond->removeHabitacao(habitacao);
        }

        cout << endl << "Habitation successfully removed!" << endl;
    }
    wait();
}

void assignHabMenu(Condominio *cond) {
    cout << endl << tittleBars("Assign Habitation");
    cout << "Assign Habitation" << endl;
    cout << tittleBars("Assign Habitation") << endl;

    if (cond->getNumHabitacoes() == 0 || cond->getNumCondominos() == 0) {
        cout << "\tCannot assign any Member to any Habitation\n";
        wait();
        return;
    }

    vector<Habitacao *> availableHabs;
    for (unsigned int i = 0; i < cond->getNumHabitacoes(); i++) {
        if (!cond->getHabitacoes()[i]->getEstado())
            availableHabs.push_back(cond->getHabitacoes()[i]);
    }

    if (availableHabs.empty()) {
        cout << "\tNo habitations available to assign\n";
        wait();
        return;
    }

    cout << "\tChoose a member to assign habitation\n";
    cout << printTable(cond->getCondominos());

    int nif;

    Condomino* condomino;
    while (true) {
        try {
            cout << "\tVAT number (-1 to CANCEL): ";
            cin >> nif;
            if (nif == -1)
                return;
            while (!cin.good() || nif <= 0 || !checkNIF(to_string(nif))) {
                cin.clear();
                cin.ignore();
                cout << "\tType a valid number please\n";
                cout << "\tVAT number: ";

                cin >> nif;
                if (nif == -1)
                    return;
            }
            cin.ignore();
            condomino = cond->findCon(nif);
        }
        catch (NoSuchCondomino &e) {
            cout << "\tPerson with VAT: " << e.getNIF() << " does not exist in members\n";
            continue;
        }
        break;
    }

    cout << "\tChoose an habitation to assign\n";
    cout << printTable(availableHabs);

    string id;
    Habitacao* habitacao;
    while (true) {
        try {
            cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
            getline(cin, id);
            if (id == "-1")
                return;

            bool flag = false;
            for (auto & availableHab : availableHabs) {
                if (id == availableHab->getID()) {
                    flag = true;
                    break;
                }
            }
            if (!flag)  // if the selected habitation is currently occupied
                throw id;
            habitacao = cond->findHab(id);
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
    cout << endl << "\tHabitation successfully assigned!" << endl;
    wait();
}

void unassignHabMenu(Condominio *cond) {
    cout << endl << tittleBars("Unassign Habitation");
    cout << "Unassign Habitation" << endl;
    cout << tittleBars("Unassign Habitation") << endl;

    if (cond->getNumHabitacoes() == 0 || cond->getNumCondominos() == 0) {
        cout << "\tCannot unassign any Member from any Habitation\n";
        wait();
        return;
    }

    vector<Habitacao *> assignedHabs;
    for (unsigned int i = 0; i < cond->getNumHabitacoes(); i++) {
        if (!cond->getHabitacoes()[i]->getEstado())
            assignedHabs.push_back(cond->getHabitacoes()[i]);
    }
    if (assignedHabs.empty()) {
        cout << "\tNo habitations available to unassign\n";
        wait();
        return;
    }

    vector<Condomino*> members;
    for (auto &m : cond->getCondominos()) {
        if (m->getNumHabitacoes() != 0) {
            members.emplace_back(m);
        }
    }
    if (members.empty()) {
        cout << "\tNo members available to unassign\n";
        wait();
        return;
    }

    cout << "\tChoose a member to unassign habitation\n";
    cout << printTable(members);

    int nif;
    Condomino* condomino;
    while (true) {
        try {
            cout << "\tVAT number (-1 to CANCEL): ";
            cin >> nif;
            if (nif == -1)
                return;
            while (!cin.good() || nif <= 0 || !checkNIF(to_string(nif))) {
                cin.clear();
                cin.ignore();
                cout << "\tType a valid number please\n";
                cout << "\tVAT number: ";

                cin >> nif;
                if (nif == -1)
                    return;
            }

            bool flag = false;
            for (auto & c : members) {
                if (nif == c->getNIF()) {
                    flag = true;
                    break;
                }
            }
            if (!flag)
                throw nif;

            cin.ignore();
            condomino = cond->findCon(nif);
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

    assignedHabs.clear();

    for (auto & h : condomino->getHabitacoes()) {
        assignedHabs.emplace_back(h);
    }
    if (assignedHabs.empty()) {
        cout << "\tNo habitations available to unassign\n";
        wait();
        return;
    }

    cout << "\tChoose an habitation to unassign\n";
    cout << printTable(assignedHabs);


    string id;
    Habitacao* habitacao;
    while (true) {
        try {
            cout << "\tID (starts with V for Villa and A for Apartment) (type -1 to CANCEL): ";
            getline(cin, id);
            if (id == "-1")
                return;

            bool flag = false;
            for (auto & availableHab : assignedHabs) {
                if (id == availableHab->getID()) {
                    flag = true;
                    break;
                }
            }
            if (!flag) throw id;
            habitacao = cond->findHab(id);
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
    cout << endl << "\tHabitation successfully unassigned!" << endl;
    wait();
}

int sortHabMenu(Condominio *cond) {
    cout << endl << tittleBars("Sort Habitations");
    cout << "Sort Habitations" << endl;
    cout << tittleBars("Sort Habitations") << endl;

    cout << "\t[1] Sort by ID (descendant)\n";
    cout << "\t[2] Sort by Habitation's Area (descendant)\n";
    cout << "\t[3] Sort by Habitation's Area (ascendant)\n";
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
            cond->ordernarHab("id");
            break;
        case 2:
            cond->ordernarHab("area-descendant");
            break;
        case 3:
            cond->ordernarHab("area-ascendant");
            break;
        case 4:
            cond->ordernarHab("pay-descendant");
            break;
        case 5:
            cond->ordernarHab("pay-ascendant");
            break;
        default:
            return choice;
    }
    return choice;
}

void viewOnlyAps(Condominio *cond) {
    cout << endl << tittleBars("View Apartments");
    cout << "View Apartments" << endl;
    cout << tittleBars("View Apartments") << endl;

    vector<Habitacao*> apps;

    for (auto &h : cond->getHabitacoes()) {
        if (h->getID()[0] == 'A') {
            apps.emplace_back(h);
        }
    }

    cout << printTable(apps);
    wait();
}

void viewOnlyVillas(Condominio *cond) {
    cout << endl << tittleBars("View Villas");
    cout << "View Villas" << endl;
    cout << tittleBars("View Villas") << endl;

    vector<Habitacao*> vivs;

    for (auto &h : cond->getHabitacoes()) {
        if (h->getID()[0] == 'V') {
            vivs.emplace_back(h);
        }
    }

    cout << printTable(vivs);
    wait();
}

// ---

void servicesMenu(Condominio *cond) {
    cout << endl << tittleBars("Services Provided");
    cout << "Services Provided" << endl;
    cout << tittleBars("Services Provided") << endl;

    cout << printTable(cond->getServicos());
    wait();
}

// ---

int fmMenu(Condominio *cond) {
    cout << endl << tittleBars("Former Members");
    cout << "Former Members" << endl;
    cout << tittleBars("Former Members") << endl;

    cout << "\t[1] Search for a Former Member\n";
    cout << "\t[2] View all Former Members\n";
    cout << "\t[3] View all Former Members given a minimum time\n\n";

    cout << "\t[4] Back\n";
    cout << "\t[0] Exit\n";

    int choice = -1;
    while (!cin.good() || choice < 0 || choice > 4) {
        cin.clear();

        cout << "\n\tChoice: ";
        cin >> choice;
        if (!cin.good() || choice < 0 || choice > 4) {
            cout << "\tType a valid number please\n";
        }
        cin.ignore();
    }

    if (choice == 0 || choice == 4)
        return choice;

    if (choice == 1) {
        string nif;
        while (true) {
            try {
                cout << "\tVAT number (type -1 to CANCEL): ";
                getline(cin,nif);
                if (nif == "-1")
                    return 3;
                while (!cin.good() || stoi(nif) <= 0 || !checkNIF(nif)) {
                    cout << "\tType a valid number please\n";
                    cout << "\tVAT number (type -1 to CANCEL): ";
                    getline(cin,nif);
                    if (nif == "-1")
                        return 3;
                }
                FormerMember fm = cond->findFormerMember(stoi(nif));
                cout << endl << fm << endl;
                wait();
            }
            catch (NoSuchCondomino &e) {
                cout << "That VAT number: " << e.getNIF() << " does not exist in former members\n";
                continue;
            }
            break;
        }
    }
    else if (choice == 2) {
        cout << printTable(cond->getFormerMembers());
        wait();
    }
    else if (choice == 3) {
        int time = -1;
        while (!cin.good() || time < 0) {
            cin.clear();
            cout << "\tTime: ";
            cin >> time;
            if (!cin.good() || time < 0) {
                cout << "\tType a valid number please\n";
            }
            cin.ignore();
        }
        cout << printTable(cond->getformerMembers(time));
        wait();
    }
    return choice;
}


// ---


int transportMenu(Condominio *cond) {
    cout << endl << tittleBars("Transports Menu");
    cout << "Transports Menu" << endl;
    cout << tittleBars("Transports Menu") << endl;

    cout << "\t[1] Search stops for a destiny\n";
    cout << "\t[2] View all stops\n";
    cout << "\t[3] Change a stop's destiny\n";
    cout << "\t[4] Deactivate stops\n";
    cout << "\t[5] Activate stops\n\n";

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
    return choice;
}

void viewStopsDestiny(Condominio *cond) {
    cout << endl << tittleBars("View Stops for a Destiny");
    cout << "View Stops for a Destiny" << endl;
    cout << tittleBars("View Stops for a Destiny") << endl;

    cout << "\tDestiny: ";
    string dest;
    getline(cin,dest);

    cout << printTable(cond->getTransports(dest));
    wait();
}

void viewAllStops(Condominio *cond) {
    cout << endl << tittleBars("View All Stops");
    cout << "View All Stops" << endl;
    cout << tittleBars("View All Stops") << endl;

    cout << printTable(cond->getVectorTransports());
    wait();
}

void changeStop(Condominio *cond) {
    cout << endl << tittleBars("Change Stop");
    cout << "Change Stop" << endl;
    cout << tittleBars("Change Stop") << endl;

    cout << printTable(cond->getVectorTransports()) << endl;

    cout << "Location: ";
    string loc;
    getline(cin,loc);
    cout << "Distance: ";
    string dist;
    getline(cin,dist);
    cout << "Current Destiny: ";
    string dest;
    getline(cin,dest);


    Transporte t = cond->getTransport(loc,stoi(dist),dest);

    if (t == Transporte()) {
        cout << "\tThat stop does not exist\n";
        wait();
        return;
    }

    cout << "\tFOUND!\n";
    cout << t << endl;
    cout << "New destiny: ";
    getline(cin,dest);

    cond->removeTransportStop(t);
    t.changeDestiny(dest);
    cond->addTransportStop(t);

    cout << "\n\tStop's Destiny changed successfully!\n";
    wait();
}

void activateStop(Condominio *cond) {
    cout << endl << tittleBars("Activate Stop");
    cout << "Activate Stop" << endl;
    cout << tittleBars("Activate Stop") << endl;

    vector<Transporte> deactivated;

    for (auto &t : cond->getVectorTransports()) {
        if (!t.getState()) {
            deactivated.emplace_back(t);
        }
    }

    cout << printTable(deactivated) << endl;


    cout << "Location: ";
    string loc;
    getline(cin,loc);
    cout << "Distance: ";
    string dist;
    getline(cin,dist);
    cout << "Current Destiny: ";
    string dest;
    getline(cin,dest);

    for (auto &t : deactivated) {
        if (t.getLocalization() == loc) {
            if (t.getDistance() == stoi(dist)) {
                if (t.getDestiny() == dest) {
                    cond->removeTransportStop(t);
                    t.changeState(true);
                    cond->addTransportStop(t);
                    cout << "\n\tStop activated successfully!\n";
                    wait();
                    return;
                }
            }
        }
    }
    cout << "\tThat stop does not exist\n";
    wait();
}

void deactivateStop(Condominio *cond) {
    cout << endl << tittleBars("Deactivate Stop");
    cout << "Deactivate Stop" << endl;
    cout << tittleBars("Deactivate Stop") << endl;

    vector<Transporte> activated;

    for (auto &t : cond->getVectorTransports()) {
        if (t.getState()) {
            activated.emplace_back(t);
        }
    }

    cout << printTable(activated) << endl;


    cout << "Location: ";
    string loc;
    getline(cin,loc);
    cout << "Distance: ";
    string dist;
    getline(cin,dist);
    cout << "Current Destiny: ";
    string dest;
    getline(cin,dest);

    for (auto &t : activated) {
        if (t.getLocalization() == loc) {
            if (t.getDistance() == stoi(dist)) {
                if (t.getDestiny() == dest) {
                    cond->removeTransportStop(t);
                    t.changeState(false);
                    cond->addTransportStop(t);
                    cout << "\n\tStop deactivated successfully!\n";
                    wait();
                    return;
                }
            }
        }
    }
    cout << "\tThat stop does not exist\n";
    wait();
}


// ---


void revenueMenu(Condominio *cond) {
    cout << endl << tittleBars("Revenue");
    cout << "Revenue" << endl;
    cout << tittleBars("Revenue") << endl;

    cout << "\t\t" <<cond->getDesignation() << endl << endl;
    cout << "\tRevenue: " << cond->calcReceitas() << " euro" << endl;
    wait();
}


// ---


int exitMenu() {
    cout << endl << tittleBars("EXIT MENU");
    cout << "EXIT MENU" << endl;
    cout << tittleBars("EXIT MENU") << endl;

    string option;
    while (true) {
        cout << "\tDo you want to save the information (Y/N)? (type -1 to CANCEL): ";
        getline(cin, option);

        if (option == "-1") return -1;


        bool flag = false;
        if (option == "Y" || option == "N" || option == "y" || option == "n")
            flag = true;

        while (!flag) {
            cout << "\tType 'Y' or 'N' please: ";

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












