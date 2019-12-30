#include <iostream>


#include "classes/CAgency.h"
#include "output-formats.h"
#include "classes/utils.h"
#include "menus.h"

void generateData() {

    int id_ap = 0;
    int id_vi = 0;

    cout << "How many condominiuns do you want to generate? ";
    string n;
    getline(cin,n);
    string conFileName, memFileName, transFileName;

    for (int y = 1; y < stoi(n)+1; y++) {
        cout << "Designation: ";
        string des;
        getline(cin, des);

        cout << "Localization: ";
        string loc;
        getline(cin, loc);

        cout << "Num prest. limpeza: ";
        string nl;
        getline(cin, nl);

        Condominio c(des,loc,stoi(nl));

        ifstream fn;
        fn.open("../first_names.txt");

        string line;
        vector<string> first_names;
        vector<string> last_names;

        while (getline(fn,line)) {
            first_names.push_back(line.erase(line.size() - 1));
        }
        fn.close();

        ifstream ln;
        ln.open("../last_names.txt");
        line.clear();

        while (getline(ln,line)) {
            last_names.push_back(line.erase(line.size() - 1));
        }
        ln.close();

        vector<string> services = { "Cleaning", "Plumbing", "Hairdresser", "Gardener",
                                    "Car Wash", "Babysitting", "Petsitting",
                                    "Mechanic", "Security" };
        vector<string> service_providers = {"AFA", "SDHF", "Homes.LDA", "EverytingUNeed", "AlwaysThere", "BeautifulHome", "Easy Home"};


        vector<string> streets;
        ifstream st("../manchester.osm.streets.txt");
        line.clear();
        while (getline(st,line)) {
            streets.push_back(line.erase(line.size() - 1));
        }
        st.close();

        string location = "Manchester";
        vector<string> addr;

        cout << "Seed: ";
        int seed;
        cin >> seed;

        cout << "Number of habitations: ";
        int nHabs;
        cin >> nHabs;

        for (int i = 0; i < nHabs; i++) {
            auto a = streets[rand() % streets.size()]+ ", " + location + ", " + to_string(rand() % 400 + 1) + ", " + "400" + "-" + to_string(rand() % 400 + 20);
            addr.push_back(a);
        }

        vector<string> type = {"T0","T1","T2","T3","T4","T5","T6","T6+"};
        vector<bool> yes_no = {true,false};


        srand(seed);

        for (int i = 0; i < nHabs; i++) {
            int j = rand() % 2;
            string id;
            if (j == 0) {
                id = "A" + to_string(id_ap);
                id_ap++;
                auto h = new Apartamento(addr[rand() % addr.size()],rand() % 400 + 30, type[rand() % type.size()], rand() % 10 + 1, rand() % 850 + 150, id);
                c.adicionaHabitacao(h);
            }
            if (j == 1) {
                id = "V" + to_string(id_vi);
                id_vi++;
                auto h = new Vivenda(addr[rand() % addr.size()], rand() % 600 + 50, rand() % 100 + 10, yes_no[rand() % yes_no.size()], rand() % 1500 + 350, id);
                c.adicionaHabitacao(h);
            }
        }

        cout << "Number of members: ";
        int nConds;
        cin >> nConds;

        for (int i = 0; i < nConds - 1; i++) {
            try {
                string nome = first_names[rand() % first_names.size()] + " " + last_names[rand() % last_names.size()];
                int nif = rand() % 999999999 + 100000000;
                if (nif > 999999999)
                    nif /= 10;
                auto con = new Condomino(nome,nif);
                c.adicionaCondomino(con);
            }
            catch (InvalidNIF &e) {
                i--;
            }
        }


        for (auto& con : c.getCondominos()) {
            int aux = rand() % 3;
            for (int i = 0; i < aux; i++) {
                Habitacao* h = c.getHabitacoes()[rand() % c.getHabitacoes().size()];
                if (!h->getEstado())
                    con->adicionaHabitacao(h);
                else {
                    if (i != 0) {
                        i--;
                    }
                }

            }
        }

        for (auto& con : c.getCondominos()) {
            int aux = rand() % 3;
            for (int i = 0; i < aux; i++) {
                auto* c = new Servico(rand() % 100 + 10, service_providers[rand() % service_providers.size()],services[rand() % services.size()]);
                con->adicionaServico(c);
            }
        }

        cin.ignore();
        cout << "Number of transports: ";
        string nTrans;
        getline(cin,nTrans);

        for (int i = 0; i < stoi(nTrans); i++) {
            string loc = streets[rand() % streets.size()];
            string dest = streets[rand() % streets.size()];
            while (loc == dest) {
                dest = streets[rand() % streets.size()];
            }
            c.addTransportStop(Transporte(loc,rand() & 1000 + 5,dest,true));
        }

        c.writeToFiles();
    }

}


void testFunc() {

    auto* c1 = new Condominio("con1.txt");
    auto* c2 = new Condominio("con2.txt");

    CAgency ca("Gonçalo Teixeira",123123123);

    ca.addCondominio(c1);
    ca.addCondominio(c2);

    ca.writeToFiles();

}


int main() {

    int choice = -1;

    CAgency agency = firstMenu();
    while (choice != 0) {
        choice = agencyMenu(&agency);
        if (choice == 1) {
            while (true) {
                choice = viewCondos(&agency);

                if (choice == 3) {  // não tem condominios para mostrar
                    break;
                }

                if (choice == 1) {
                    auto cond = speficifyCondo(&agency);
                    if (cond == nullptr) {
                        continue;
                    } else {
                        while (true) {
                            choice = condoMenu();
                            if (choice == 0) {
                                choice = exitMenu();
                                if (choice == 0) {
                                    BSTItrIn<Condominio*> it(agency.getCondominios());
                                    while (!it.isAtEnd()) {
                                        it.retrieve()->writeToFiles();
                                        it.advance();
                                    }
                                    return 0;
                                }
                                else if (choice == 1) {
                                    cout << "\tNo changes made!";
                                    return 0;
                                }
                                choice = -1;
                                continue;
                            }
                            else if (choice == 7) {
                                break;
                            }
                            else if (choice == 1) {
                                while (choice != 5) {
                                    choice = membersMenu(cond);
                                    if (choice == 0) {
                                        choice = exitMenu();
                                        if (choice == 0) {
                                            agency.writeToFiles();
                                            return 0;
                                        }
                                        else if (choice == 1) {
                                            cout << "\tNo changes made!";
                                            return 0;
                                        }
                                        choice = -1;
                                        continue;
                                    }
                                    else if (choice == 5) {
                                        choice = -1;
                                        break;
                                    }
                                    else if (choice == 1) {
                                        addMemberMenu(cond);
                                        continue;
                                    }
                                    else if (choice == 2) {
                                        removeMemberMenu(cond);
                                        continue;
                                    }
                                    else if (choice == 3) {
                                        choice = sortMembersMenu(cond);
                                        if (choice == 0) {
                                            choice = exitMenu();
                                            if (choice == 0) {
                                                agency.writeToFiles();
                                                return 0;
                                            }
                                            else if (choice == 1) {
                                                cout << "\tNo changes made!";
                                                return 0;
                                            }
                                            choice = -1;
                                            continue;
                                        }
                                        choice = 3;
                                    }
                                    else if (choice == 4) {
                                        choice = rqService(cond);
                                        if (choice == 0) {
                                            choice = exitMenu();
                                            if (choice == 0) {
                                                agency.writeToFiles();
                                                return 0;
                                            }
                                            else if (choice == 1) {
                                                cout << "\tNo changes made!";
                                                return 0;
                                            }
                                            choice = -1;
                                            continue;
                                        }
                                    }
                                }
                            }
                            else if (choice == 2) {
                                while (choice != 8) {
                                    choice = habitationsMenu(cond);
                                    if (choice == 0) {
                                        choice = exitMenu();
                                        if (choice == 0) {
                                            agency.writeToFiles();
                                            return 0;
                                        }
                                        else if (choice == 1) {
                                            cout << "\tNo changes made!";
                                            return 0;
                                        }
                                        choice = -1;
                                        continue;
                                    }
                                    else if (choice == 8) {
                                        choice = -1;
                                        break;
                                    }
                                    else if (choice == 1) {
                                        choice = addHabMenu(&agency, cond);
                                        if (choice == 0) {
                                            choice = exitMenu();
                                            if (choice == 0) {
                                                agency.writeToFiles();
                                                return 0;
                                            }
                                            else if (choice == 1) {
                                                cout << "\tNo changes made!";
                                                return 0;
                                            }
                                            choice = -1;
                                            continue;
                                        }
                                        continue;
                                    }
                                    else if (choice == 2) {
                                        rmHabMenu(cond);
                                        continue;
                                    }
                                    else if (choice == 3) {
                                        assignHabMenu(cond);
                                        continue;
                                    }
                                    else if (choice == 4) {
                                        unassignHabMenu(cond);
                                        continue;
                                    }
                                    else if (choice == 5) {
                                        choice = sortHabMenu(cond);
                                        if (choice == 0) {
                                            choice = exitMenu();
                                            if (choice == 0) {
                                                agency.writeToFiles();
                                                return 0;
                                            }
                                            else if (choice == 1) {
                                                cout << "\tNo changes made!";
                                                return 0;
                                            }
                                            choice = -1;
                                            continue;
                                        }
                                        choice = 5;
                                        continue;
                                    }
                                    else if (choice == 6) {
                                        viewOnlyAps(cond);
                                        continue;
                                    }
                                    else if (choice == 7) {
                                        viewOnlyVillas(cond);
                                        continue;
                                    }
                                }
                            }
                            else if (choice == 3) {
                                servicesMenu(cond);
                                continue;
                            }
                            else if (choice == 4) { // antigos condominos
                                choice = -1;
                                while (choice != 4) {
                                    choice = fmMenu(cond);
                                    if (choice == 0) {
                                        choice = exitMenu();
                                        if (choice == 0) {
                                            agency.writeToFiles();
                                            return 0;
                                        }
                                        else if (choice == 1) {
                                            cout << "\tNo changes made!";
                                            return 0;
                                        }
                                        choice = -1;
                                        continue;
                                    }
                                }
                            }
                            else if (choice == 5) { // transportes
                                choice = -1;
                                while (choice != 6) {
                                    choice = transportMenu(cond);
                                    if (choice == 0) {
                                        choice = exitMenu();
                                        if (choice == 0) {
                                            agency.writeToFiles();
                                            return 0;
                                        }
                                        else if (choice == 1) {
                                            cout << "\tNo changes made!";
                                            return 0;
                                        }
                                        choice = -1;
                                        continue;
                                    }
                                    else if (choice == 1) {
                                        viewStopsDestiny(cond);
                                        continue;
                                    }
                                    else if (choice == 2) {
                                        viewAllStops(cond);
                                        continue;
                                    }
                                    else if (choice == 3) {
                                        changeStop(cond);
                                        continue;
                                    }
                                    else if (choice == 4) {
                                        deactivateStop(cond);
                                        continue;
                                    }
                                    else if (choice == 5) {
                                        activateStop(cond);
                                        continue;
                                    }
                                }
                            }
                            else if (choice == 6) { // revenue
                                revenueMenu(cond);
                            }
                        }
                    }
                } else if (choice == 2) {
                    break;
                } else if (choice == 0) {
                    choice = exitMenu();
                    if (choice == 0) {
                        agency.writeToFiles();
                        return 0;
                    }
                    else if (choice == 1) {
                        cout << "\tNo changes made!";
                        return 0;
                    }
                    choice = -1;
                    continue;
                }
            }
        }
        else if (choice == 2) {
            choice = addCondo(&agency);
            continue;
        }
        else if (choice == 3) {
            removeCondo(&agency);
        }
        else if (choice == 0) {
            choice = exitMenu();
            if (choice == 0) {
                agency.writeToFiles();
                return 0;
            } else if (choice == 1) {
                cout << "\tNo changes made!";
                return 0;
            }
            choice = -1;
        }
    }

    return 0;
}
