#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Elev.h"
#include "IO.h"
using namespace std;

vector<Elev> catalog;

// cauta elevul dupa CNP si returneaza pointer (sau nullptr)
Elev* cautaElev(string cnp) {
    for (auto& e : catalog) {
        if (e.getCNP() == cnp) return &e;
    }
    return nullptr;
}

int main(int argc, char* argv[]) {

    citesteElevi("elevi.txt");
    citesteMaterii("materii.txt");

    if (argc < 2) {
        cout << "Utilizare: ./ProiectC_ [student1|student2] [optiuni...]\n";
        return 1;
    }

    string rol = argv[1];

    if (rol == "student1") {
        if (argc < 5) {
            cout << "Utilizare: ./ProiectC_ student1 [adaugaNota|stergeNota|adaugaAbsenta|stergeAbsenta] CNP Valoare Materie\n";
            return 1;
        }
        string operatie = argv[2];
        string cnp = argv[3];
        string valoare = argv[4];
        string materie = argv[5];

        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }

        if (operatie == "adaugaNota") {
            elev->adaugaNota(stoi(valoare), materie);
            scrieMaterii("materii.txt");
        } else if (operatie == "stergeNota") {
            elev->stergeNota(stoi(valoare), materie);
            scrieMaterii("materii.txt");
        } else if (operatie == "adaugaAbsenta") {
            elev->adaugaAbsenta(valoare, materie);
            scrieMaterii("materii.txt");
        } else if (operatie == "stergeAbsenta") {
            elev->stergeAbsenta(valoare, materie);
            scrieMaterii("materii.txt");
        } else {
            cout << "Operatie necunoscuta pentru student1.\n";
        }
    }
    else if (rol == "student2") {
        if (argc < 4) {
            cout << "Utilizare: ./ProiectC_ student2 [adaugaElev|stergeElev|motiveazaAbsenta] [date]\n";
            return 1;
        }

        string operatie = argv[2];

        if (operatie == "adaugaElev") {
            if (argc < 6) {
                cout << "Utilizare: ./ProiectC_ student2 adaugaElev Nume Prenume CNP\n";
                return 1;
            }
            string nume = argv[3];
            string prenume = argv[4];
            string cnp = argv[5];
            catalog.emplace_back(nume, prenume, cnp);
            scrieElevi("elevi.txt");
        }
        else if (operatie == "stergeElev") {
            string cnp = argv[3];
            auto it = remove_if(catalog.begin(), catalog.end(), [&](Elev& e) {
                return e.getCNP() == cnp;
            });
            if (it != catalog.end()) {
                catalog.erase(it, catalog.end());
            } else {
                cout << "Elevul nu a fost gasit.\n";
            }
            scrieElevi("elevi.txt");
        }
        else if (operatie == "motiveazaAbsenta") {
            if (argc < 6) {
                cout << "Utilizare: ./ProiectC_ student2 motiveazaAbsenta CNP Data Materie\n";
                return 1;
            }
            string cnp = argv[3];
            string data = argv[4];
            string materie = argv[5];
            Elev* elev = cautaElev(cnp);
            if (elev) {
                elev->motiveazaAbsenta(data, materie);
                scrieMaterii("materii.txt");
            } else {
                cout << "Elevul nu a fost gasit.\n";
            }
        }
        else {
            cout << "Operatie necunoscuta pentru student2.\n";
        }
    }
    else {
        cout << "Rol necunoscut. Foloseste student1 sau student2.\n";
        return 1;
    }

    return 0;
}
