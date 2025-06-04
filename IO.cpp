//
// Created by hacfi on 04.06.2025.
//

#include "IO.h"
// citire_scriere_catalog.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Elev.h"
using namespace std;

extern vector<Elev> catalog;

//=================== CITIRE ===================
void citesteElevi(const string& numeFisier) {
    ifstream in(numeFisier);
    if (!in.is_open()) return;
    string nume, prenume, cnp;
    while (in >> nume >> prenume >> cnp) {
        catalog.emplace_back(nume, prenume, cnp);
    }
    in.close();
}

void citesteMaterii(const string& numeFisier) {
    ifstream in(numeFisier);
    if (!in.is_open()) return;
    string linie;
    while (getline(in, linie)) {
        istringstream ss(linie);
        string cnp, materie, noteStr, absenteStr;
        ss >> cnp >> materie;
        Elev* elev = nullptr;
        for (auto& e : catalog) {
            if (e.getCNP() == cnp) {
                elev = &e;
                break;
            }
        }
        if (!elev) continue;
        size_t pos = linie.find("note:");
        if (pos != string::npos) {
            size_t next = linie.find(" ", pos);
            noteStr = linie.substr(pos + 5, next - pos - 5);
        }
        pos = linie.find("absente:");
        if (pos != string::npos) {
            absenteStr = linie.substr(pos + 8);
        }
        elev->adaugaNota(-1, materie); // for init only
        if (!noteStr.empty()) {
            istringstream noteSS(noteStr);
            string nota;
            while (getline(noteSS, nota, ',')) {
                if (!nota.empty()) elev->adaugaNota(stoi(nota), materie);
            }
        }
        if (!absenteStr.empty()) {
            istringstream absSS(absenteStr);
            string abs;
            while (getline(absSS, abs, ',')) {
                bool motivat = false;
                if (!abs.empty() && abs.back() == '*') {
                    motivat = true;
                    abs.pop_back();
                }
                elev->adaugaAbsenta(abs, materie);
                if (motivat) elev->motiveazaAbsenta(abs, materie);
            }
        }
    }
    in.close();
}

//=================== SCRIERE ===================
void scrieElevi(const string& numeFisier) {
    ofstream out(numeFisier);
    int i = 0;
    for (auto& e : catalog) {
        i++;
        if (i>1)
            out<<'\n';
        out << e;
    }
    out.close();
}

void scrieMaterii(const string& numeFisier) {
    ofstream out(numeFisier);
    for (auto& e : catalog) {
        string cnp = e.getCNP();
        for (const auto& m : e.getMaterii()) {
            out << cnp << " " << m.nume << " note:";
            for (size_t i = 0; i < m.note.size(); i++) {
                out << m.note[i];
                if (i + 1 < m.note.size()) out << ",";
            }
            out << " absente:";
            for (size_t i = 0; i < m.abs.size(); i++) {
                out << m.abs[i].data;
                if (m.abs[i].motivat) out << "*";
                if (i + 1 < m.abs.size()) out << ",";
            }
            out << "\n";
        }
    }
    out.close();
}

#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void citesteTotCatalogul() {
    catalog.clear();
    for (const auto& entry : fs::directory_iterator("elevi")) {
        ifstream in(entry.path());
        if (!in.is_open()) continue;

        string nume, prenume, cnp;
        string linie;

        getline(in, linie); // Nume
        nume = linie.substr(6); // dupa "Nume: "

        getline(in, linie); // Prenume
        prenume = linie.substr(9); // dupa "Prenume: "

        getline(in, linie); // CNP
        cnp = linie.substr(5); // dupa "CNP: "

        Elev elev(nume, prenume, cnp);

        while (getline(in, linie)) {
            if (linie.empty()) continue;

            if (linie.rfind("Materie:", 0) == 0) {
                string materie = linie.substr(9);
                elev.adaugaMaterie(materie);

                getline(in, linie); // Note:
                if (linie.rfind("Note:", 0) == 0) {
                    string noteStr = linie.substr(6);
                    istringstream ss(noteStr);
                    string nota;
                    while (getline(ss, nota, ',')) {
                        if (!nota.empty())
                            elev.adaugaNota(stoi(nota), materie);
                    }
                }

                getline(in, linie); // Absente:
                if (linie.rfind("Absente:", 0) == 0) {
                    string absStr = linie.substr(9);
                    istringstream ss(absStr);
                    string abs;
                    while (getline(ss, abs, ',')) {
                        bool motivat = false;
                        if (!abs.empty() && abs.back() == '*') {
                            motivat = true;
                            abs.pop_back();
                        }
                        elev.adaugaAbsenta(abs, materie);
                        if (motivat) elev.motiveazaAbsenta(abs, materie);
                    }
                }
            }
        }
        in.close();
        catalog.push_back(elev);
    }
}
void scrieElevIndividual(const Elev& e) {
    string filename = "elevi/" + e.getCNP() + ".txt";
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Eroare la deschiderea fisierului pentru scriere: " << filename << "\n";
        return;
    }

    out << "Nume: " << e.getNume() << "\n";
    out << "Prenume: " << e.getPrenume() << "\n";
    out << "CNP: " << e.getCNP() << "\n\n";

    for (const auto& m : e.getMaterii()) {
        out << "Materie: " << m.nume << "\n";

        out << "Note: ";
        for (size_t i = 0; i < m.note.size(); ++i) {
            out << m.note[i];
            if (i + 1 < m.note.size()) out << ",";
        }
        out << "\n";

        out << "Absente: ";
        for (size_t i = 0; i < m.abs.size(); ++i) {
            out << m.abs[i].data;
            if (m.abs[i].motivat) out << "*";
            if (i + 1 < m.abs.size()) out << ",";
        }
        out << "\n\n";
    }

    out.close();
}

//=================== UTILIZARE ===================
// Apelează aceste funcții în main.cpp:
// citesteElevi("elevi.txt");
// citesteMaterii("materii.txt");
// scrieElevi("elevi.txt");
// scrieMaterii("materii.txt");
