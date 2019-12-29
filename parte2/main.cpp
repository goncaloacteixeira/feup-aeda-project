#include <iostream>


#include "classes/CAgency.h"
#include "output-formats.h"
#include "classes/utils.h"
#include "menus.h"

void generateData() {
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
            if (j == 0) {
                auto h = new Apartamento(addr[rand() % addr.size()],rand() % 400 + 30, type[rand() % type.size()], rand() % 10 + 1, rand() % 850 + 150);
                c.adicionaHabitacao(h);
            }
            if (j == 1) {
                auto h = new Vivenda(addr[rand() % addr.size()], rand() % 600 + 50, rand() % 100 + 10, yes_no[rand() % yes_no.size()], rand() % 1500 + 350);
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
            c.addTransportStop(Transporte(loc,rand() & 1000 + 5,dest));
        }

        c.writeToFiles();
    }

}


void testFunc() {
    auto *c1 = new Condominio("con1.txt");
//    auto *c2 = new Condominio("con2.txt");
//    auto *c3 = new Condominio("con3.txt");


    CAgency a("Joao",919234123);
    a.addCondominio(c1);
//    a.addCondominio(c2);
//    a.addCondominio(c3);

    rqService(c1);
    cout << printTable(c1->getServicos());

}


int main() {
    testFunc();
    return 0;

    auto *c1 = new Condominio("con1.txt");
//    auto *c2 = new Condominio("con2.txt");
//    auto *c3 = new Condominio("con3.txt");


    CAgency a("Joao",919234123);
    a.addCondominio(c1);
//    a.addCondominio(c2);
//    a.addCondominio(c3);



    int choice = -1;

    CAgency agency = firstMenu();
    while (choice != 0) {
        choice = agencyMenu(&agency);
        if (choice == 1) {
            while (true) {
                choice = viewCondos(&agency);
                if (choice == 1) {
                    auto cond = speficifyCondo(&agency);
                    if (cond == nullptr) {
                        continue;
                    } else {
                        // TODO - MENUS PARA CONDOMINIO (COPIAR DA PARTE 1)
                    }
                } else if (choice == 2) {
                    break;
                } else if (choice == 0) {
                    break;
                }
            }
        }
        else if (choice == 2) {
            choice = addCondo(&agency);
        }
        else if (choice == 3) {
            removeCondo(&agency);
        }
    }



    return 0;
}
