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

bool esteNumarValid(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

int main(int argc, char* argv[]) {
    citesteTotCatalogul();

    if (argc < 2) {
        cout << "Utilizare: ./main.exe [comanda] [parametri...]\n";
        cout << "Comenzi disponibile:\n";
        cout << "  adaugaElev [Nume] [Prenume] [CNP]\n";
        cout << "  stergeElev [CNP]\n";
        cout << "  adaugaMaterie [CNP] [Materie]\n";
        cout << "  stergeMaterie [CNP] [Materie]\n";
        cout << "  adaugaNota [CNP] [Nota] [Materie] [Data]\n";
        cout << "  stergeNota [CNP] [Nota] [Materie] [Data]\n";
        cout << "  adaugaAbsenta [CNP] [Data] [Materie]\n";
        cout << "  motiveazaAbsenta [CNP] [Data] [Materie]\n";
        cout << "  afiseazaElev [CNP]\n";
        cout << "  afiseazaCatalog\n";
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

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        catalog.emplace_back(nume, prenume, cnp);
        scrieElevIndividual(catalog.back());
    }

    else if (operatie == "stergeElev") {
        if (argc < 3) {
            cout << "Utilizare: stergeElev CNP\n";
            return 1;
        }
        string cnp = argv[2];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        auto it = remove_if(catalog.begin(), catalog.end(), [&](Elev& e) {
            return e.getCNP() == cnp;
        });
        if (it != catalog.end()) {
            catalog.erase(it, catalog.end());
            string filename = "elevi/" + cnp + ".txt";
            if (remove(filename.c_str()) == 0)
                cout << "Elevul si fisierul au fost sterse.\n";
            else
                cout << "Elevul a fost sters, dar fisierul nu a putut fi sters.\n";
        } else {
            cout << "Elevul nu a fost gasit.\n";
        }
    }

    else if (operatie == "adaugaMaterie") {
        if (argc < 4) {
            cout << "Utilizare: adaugaMaterie CNP Materie\n";
            return 1;
        }
        string cnp = argv[2];
        string materie = argv[3];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->adaugaMaterie(materie);
        scrieElevIndividual(*elev);
    }

    else if (operatie == "stergeMaterie") {
        if (argc < 4) {
            cout << "Utilizare: stergeMaterie CNP Materie\n";
            return 1;
        }
        string cnp = argv[2];
        string materie = argv[3];
        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->stergeMaterie(materie);
        scrieElevIndividual(*elev);
    }

    else if (operatie == "adaugaNota") {
        if (argc < 5) {
            cout << "Utilizare: adaugaNota CNP Nota Materie [Data]\n";
            return 1;
        }
        string cnp = argv[2], val = argv[3], materie = argv[4];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        string data = (argc >= 6) ? argv[5] : "";
        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->adaugaNota(stoi(val), materie, data);
        cout << "Adaugat nota " << val;
        if (!data.empty()) cout << "la data de:" << data;
        cout << " la " << materie << " pentru " << elev->getNume() << " " << elev->getPrenume() << "\n";
        scrieElevIndividual(*elev);
    }

    else if (operatie == "stergeNota") {
        if (argc < 5) {
            cout << "Utilizare: stergeNota CNP Nota Materie [Data]\n";
            return 1;
        }
        string cnp = argv[2], val = argv[3], materie = argv[4];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        string data = (argc >= 6) ? argv[5] : "";
        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->stergeNota(stoi(val), materie, data);
        scrieElevIndividual(*elev);
    }

    else if (operatie == "adaugaAbsenta") {
        if (argc < 5) {
            cout << "Utilizare: adaugaAbsenta CNP Data Materie\n";
            return 1;
        }
        string cnp = argv[2], data = argv[3], materie = argv[4];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->adaugaAbsenta(data, materie);
        scrieElevIndividual(*elev);
    }

    else if (operatie == "motiveazaAbsenta") {
        if (argc < 5) {
            cout << "Utilizare: motiveazaAbsenta CNP Data Materie\n";
            return 1;
        }
        string cnp = argv[2], data = argv[3], materie = argv[4];
        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        elev->motiveazaAbsenta(data, materie);
        scrieElevIndividual(*elev);
    }

    else if (operatie == "afiseazaElev") {
        if (argc < 3) {
            cout << "Utilizare: afiseazaElev CNP\n";
            return 1;
        }
        string cnp = argv[2];

        if (!esteNumarValid(cnp)) {
            cout << "Eroare: CNP-ul trebuie sa contina doar cifre.\n";
            return 1;
        }

        Elev* elev = cautaElev(cnp);
        if (!elev) {
            cout << "Elevul cu CNP " << cnp << " nu a fost gasit.\n";
            return 1;
        }
        cout << *elev << "\n";
        for (const auto& m : elev->getMaterii()) {
            cout << "  Materie: " << m.nume << "\n";
            cout << "    Note: ";
            for (const auto& n : m.note) {
                cout << n.valoare;
                if (!n.data.empty()) cout << ":" << n.data;
                cout << " ";
            }
            cout << "\n    Absente: ";
            for (const auto& a : m.abs)
                cout << a.data << (a.motivat ? "*" : "") << " ";
            cout << "\n";
        }
        cout << "------------------------------\n";
    }

    else if (operatie == "afiseazaCatalog") {
        for (const auto& elev : catalog) {
            cout << elev << "\n";
            for (const auto& m : elev.getMaterii()) {
                cout << "  Materie: " << m.nume << "\n";
                cout << "    Note: ";
                for (const auto& n : m.note) {
                    cout << n.valoare;
                    if (!n.data.empty()) cout << ":" << n.data;
                    cout << " ";
                }
                cout << "\n    Absente: ";
                for (const auto& a : m.abs)
                    cout << a.data << (a.motivat ? "*" : "") << " ";
                cout << "\n";
            }
            cout << "------------------------------\n";
        }
    }

    else {
        cout << "Comanda necunoscuta. Foloseste ./main.exe pentru instructiuni.\n";
        return 1;
    }

    return 0;
}
