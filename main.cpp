#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Elev.h"
#include "IO.h"
using namespace std;

vector<Elev> catalog;

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
        cout << "Utilizare: ./main.exe [comanda] [parametri...]\n";
        cout << "Comenzi disponibile:\n";
        cout << "  adaugaElev Nume Prenume CNP\n";
        cout << "  stergeElev CNP\n";
        cout << "  adaugaNota CNP Valoare Materie\n";
        cout << "  stergeNota CNP Valoare Materie\n";
        cout << "  adaugaAbsenta CNP Data Materie\n";
        cout << "  stergeAbsenta CNP Data Materie\n";
        cout << "  motiveazaAbsenta CNP Data Materie\n";
        return 1;
    }

    string operatie = argv[1];

    if (operatie == "adaugaElev") {
        if (argc < 5) {
            cout << "Utilizare: adaugaElev Nume Prenume CNP\n";
            return 1;
        }
        string nume = argv[2];
        string prenume = argv[3];
        string cnp = argv[4];
        catalog.emplace_back(nume, prenume, cnp);
        scrieElevi("elevi.txt");
    }
    else if (operatie == "stergeElev") {
        if (argc < 3) {
            cout << "Utilizare: stergeElev CNP\n";
            return 1;
        }
        string cnp = argv[2];
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
    else if (operatie == "adaugaNota" || operatie == "stergeNota" ||
             operatie == "adaugaAbsenta" || operatie == "stergeAbsenta" ||
             operatie == "motiveazaAbsenta") {

        if (argc < 5) {
            cout << "Utilizare: " << operatie << " CNP Valoare/Dată Materie\n";
            return 1;
        }

        string cnp = argv[2];
        string val = argv[3];
        string materie = argv[4];

        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }

        if (operatie == "adaugaNota") elev->adaugaNota(stoi(val), materie);
        else if (operatie == "stergeNota") elev->stergeNota(stoi(val), materie);
        else if (operatie == "adaugaAbsenta") elev->adaugaAbsenta(val, materie);
        else if (operatie == "stergeAbsenta") elev->stergeAbsenta(val, materie);
        else if (operatie == "motiveazaAbsenta") elev->motiveazaAbsenta(val, materie);

        scrieMaterii("materii.txt");
    }
    else {
        cout << "Comanda necunoscuta. Foloseste ./main.exe pentru instructiuni.\n";
        return 1;
    }

    return 0;
}
