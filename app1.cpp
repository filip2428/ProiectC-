#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Elev.h"
#include "IO.h"

/// \file app1.cpp
/// \brief Aplicatie pentru operatii de modificare a catalogului.

using namespace std;

/// Vector global cu toti elevii din catalog
vector<Elev> catalog;

/// Gaseste un elev dupa CNP
Elev* cautaElev(string cnp) {
    for (auto& e : catalog)
        if (e.getCNP() == cnp) return &e;
    return nullptr;
}

/// Verifica daca un sir contine doar cifre
bool esteNumarValid(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

/// Calculeaza media unui vector generic
template <typename T>
double calculeazaMedie(const vector<T>& valori) {
    if (valori.empty()) return 0.0;
    double suma = 0;
    for (const auto& v : valori) suma += v;
    return suma / valori.size();
}

/// Punctul de intrare al aplicatiei
int main(int argc, char* argv[]) {
    citesteTotCatalogul();

    if (argc < 2) {
        cout << "Utilizare: ./app1 [comanda] [parametri...]\n";
        cout << "Comenzi disponibile:\n";
        cout << "  adaugaMaterie CNP Materie\n";
        cout << "  stergeMaterie CNP Materie\n";
        cout << "  adaugaNota CNP Nota Materie [Data]\n";
        cout << "  stergeNota CNP Nota Materie [Data]\n";
        cout << "  adaugaAbsenta CNP Data Materie\n";
        return 1;
    }

    string operatie = argv[1];

    if (operatie == "adaugaMaterie" && argc >= 4) {
        string cnp = argv[2], materie = argv[3];
        Elev* e = cautaElev(cnp);
        if (e) { e->adaugaMaterie(materie); scrieElevIndividual(*e); }
    }

    else if (operatie == "adaugaNota" && argc >= 5) {
        string cnp = argv[2], val = argv[3], materie = argv[4];
        string data = (argc >= 6 ? argv[5] : "");
        Elev* e = cautaElev(cnp);
        if (e) { e->adaugaNota(stoi(val), materie, data); scrieElevIndividual(*e); }
    }

    else if (operatie == "stergeNota" && argc >= 5) {
        string cnp = argv[2], val = argv[3], materie = argv[4];
        string data = (argc >= 6 ? argv[5] : "");
        Elev* e = cautaElev(cnp);
        if (e) { e->stergeNota(stoi(val), materie, data); scrieElevIndividual(*e); }
    }

    else if (operatie == "adaugaAbsenta" && argc >= 5) {
        string cnp = argv[2], data = argv[3], materie = argv[4];
        Elev* e = cautaElev(cnp);
        if (e) { e->adaugaAbsenta(data, materie); scrieElevIndividual(*e); }
    }

    else if (operatie == "motiveazaAbsenta" && argc >= 5) {
        cout << "Operatie neacceptata in app1. Folositi app2." << endl;
    }

    else if (operatie == "afiseazaElev" || operatie == "afiseazaCatalog") {
        cout << "Operatie neacceptata in app1. Folositi app2." << endl;
    }

    else cout << "Comanda necunoscuta.\n";

    return 0;
}
