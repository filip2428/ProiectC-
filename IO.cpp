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

//=================== UTILIZARE ===================
// Apelează aceste funcții în main.cpp:
// citesteElevi("elevi.txt");
// citesteMaterii("materii.txt");
// scrieElevi("elevi.txt");
// scrieMaterii("materii.txt");
