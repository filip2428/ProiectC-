#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "Elev.h"
#include "IO.h"

/// \file app2.cpp
/// \brief Aplicatie pentru operatii de vizualizare si administrare generala.

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
        cout << "Utilizare: ./app2 [comanda] [parametri...]\n";
        cout << "Comenzi disponibile:\n";
        cout << "  adaugaElev Nume Prenume CNP\n";
        cout << "  stergeElev CNP\n";
        cout << "  motiveazaAbsenta CNP Data Materie\n";
        cout << "  afiseazaElev CNP\n";
        cout << "  afiseazaCatalog\n";
        return 1;
    }

    string operatie = argv[1];

    if (operatie == "adaugaElev" && argc >= 5) {
        string nume = argv[2], prenume = argv[3], cnp = argv[4];
        if (!esteNumarValid(cnp)) return cout << "CNP invalid.\n", 1;
        catalog.emplace_back(nume, prenume, cnp);
        scrieElevIndividual(catalog.back());
    }

    else if (operatie == "stergeElev" && argc >= 3) {
        string cnp = argv[2];
        auto it = remove_if(catalog.begin(), catalog.end(), [&](Elev& e) { return e.getCNP() == cnp; });
        if (it != catalog.end()) {
            catalog.erase(it, catalog.end());
            remove(("data/elevi/" + cnp + ".txt").c_str());
        }
    }

    else if (operatie == "adaugaMaterie" || operatie == "stergeMaterie" ||
             operatie == "adaugaNota" || operatie == "stergeNota" ||
             operatie == "adaugaAbsenta") {
        cout << "Operatie neacceptata in app2. Folositi app1." << endl;
    }

    else if (operatie == "motiveazaAbsenta" && argc >= 5) {
        string cnp = argv[2], data = argv[3], materie = argv[4];
        Elev* e = cautaElev(cnp);
        if (e) { e->motiveazaAbsenta(data, materie); scrieElevIndividual(*e); }
    }

    else if (operatie == "afiseazaElev" && argc >= 3) {
        string cnp = argv[2];
        Elev* e = cautaElev(cnp);
        if (e) {
            cout << *e << "\n";
            vector<double> medii;
            for (const auto& m : e->getMaterii()) {
                cout << "  Materie: " << m.nume << "\n";
                cout << "    Note: ";
                for (const auto& n : m.note)
                    cout << n.valoare << (n.data.empty() ? " " : ":" + n.data + " ");
                vector<int> v = m.getNoteValori();
                double medie = calculeazaMedie(v);
                if (!v.empty()) medii.push_back(medie);
                cout << "\n    Media: " << medie << "\n";
                cout << "    Absente: ";
                for (const auto& a : m.abs)
                    cout << a.data << (a.motivat ? "*" : "") << " ";
                cout << "\n";
            }
            cout << "Media generala: " << calculeazaMedie(medii) << "\n";
        }
    }

    else if (operatie == "afiseazaCatalog") {
        for (const auto& e : catalog) {
            cout << e << "\n";
            for (const auto& m : e.getMaterii()) {
                cout << "  Materie: " << m.nume << "\n";
                cout << "    Note: ";
                for (const auto& n : m.note)
                    cout << n.valoare << (n.data.empty() ? " " : ":" + n.data + " ");
                cout << "\n    Absente: ";
                for (const auto& a : m.abs)
                    cout << a.data << (a.motivat ? "*" : "") << " ";
                cout << "\n";
            }
        }
    }

    else cout << "Comanda necunoscuta.\n";

    return 0;
}
