//
// Created by skidr on 12/10/2019.
//

#include <iostream>


#include "menus.h"

using namespace std;


int main() {
    Condominio c = Condominio(0);

    int option = firstMenu();
    if (option == 0)
        return 0;
    else if (option == 1)
        c = newCondominium();
    else if (option == 2)
        c = Condominio(filenameMenu());

    while (true) {
        option = mainMenu(&c);
        if (option == 0) {
            option = exitMenu(&c);
            if (option == 0) {
                string file1, file2;
                cout << "\tCondominium filename (with .txt): ";
                getline(cin, file1);
                cout << "\tMembers filename (with .txt): ";
                getline(cin, file2);
                c.writeToFiles(file1, file2);
                wait();
                return 0;
            }
            if (option == 1) {
                return 0;
            }
            if (option == -1) {
                continue;
            }
        }
        if (option == 1) {
            int option2;
            while (true) {
                option2 = membersMenu(&c);
                if (option2 == 0) {
                    option2 = exitMenu(&c);
                    if (option2 == 0) {
                        string file1, file2;
                        cout << "\tCondominium filename (with .txt): ";
                        getline(cin, file1);
                        cout << "\tMembers filename (with .txt): ";
                        getline(cin, file2);
                        c.writeToFiles(file1, file2);
                        wait();
                        return 0;
                    }
                    if (option2 == 1) {
                        return 0;
                    }
                    if (option2 == -1) {
                        continue;
                    }
                }
                else if (option2 == 1) {
                    addConMenu(&c);
                    continue;
                }
                else if (option2 == 2) {
                    rmConMenu(&c);
                    continue;
                }
                else if (option2 == 3) {
                    option2 = sortConMenu(&c);
                    if (option2 == 0) {
                        option2 = exitMenu(&c);
                        if (option2 == 0) {
                            string file1, file2;
                            cout << "\tCondominium filename (with .txt): ";
                            getline(cin, file1);
                            cout << "\tMembers filename (with .txt): ";
                            getline(cin, file2);
                            c.writeToFiles(file1, file2);
                            wait();
                            return 0;
                        }
                        if (option2 == 1) {
                            return 0;
                        }
                        if (option2 == -1) {
                            continue;
                        }
                    }
                    continue;
                }
                else if (option2 == 4) {
                    option2 = rqServiceMenu(&c);
                    if (option2 == 0) {
                        option2 = exitMenu(&c);
                        if (option2 == 0) {
                            string file1, file2;
                            cout << "\tCondominium filename (with .txt): ";
                            getline(cin, file1);
                            cout << "\tMembers filename (with .txt): ";
                            getline(cin, file2);
                            c.writeToFiles(file1, file2);
                            wait();
                            return 0;
                        }
                        if (option2 == 1) {
                            return 0;
                        }
                        if (option2 == -1) {
                            continue;
                        }
                    }
                    continue;
                }
                else if (option2 == 5) {
                    break;
                }
            }
        }
        else if (option == 2) {
            option = addHabMenu(&c);
            if (option == 0) {
                option = exitMenu(&c);
                if (option == 0) {
                    string file1, file2;
                    cout << "\tCondominium filename (with .txt): ";
                    getline(cin, file1);
                    cout << "\tMembers filename (with .txt): ";
                    getline(cin, file2);
                    c.writeToFiles(file1, file2);
                    wait();
                    return 0;
                }
                if (option == 1) {
                    return 0;
                }
                if (option == -1) {
                    continue;
                }
            }
            continue;
        }
        else if (option == 3) {
            rmHabMenu(&c);
            continue;
        }
        else if (option == 4) {
            assignHab(&c);
            continue;
        }
        else if (option == 5) {
            unassignHab(&c);
            continue;
        }
        else if (option == 6) {
            sortHabMenu(&c);
            continue;
        }
        else if (option == 7) {
            viewHabs(&c);
            continue;
        }
        else if (option == 8) {
            viewAps(&c);
            continue;
        }
        else if (option == 9) {
            viewVivs(&c);
            continue;
        }
        else if (option == 10) {
            servicesProvided(&c);
            continue;
        }
        else if (option == 11) {
            incomeMenu(&c);
            continue;
        }
    }
}