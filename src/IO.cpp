#include "IO.h"
/// \file IO.cpp
/// \brief Functii de citire si scriere pentru catalog.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Elev.h"
#include "Materie.h"
using namespace std;

extern vector<Elev> catalog;

/// Calculeaza media valorilor dintr-un vector
template <typename T>
double calculeazaMedie(const vector<T>& valori) {
    if (valori.empty()) return 0.0;
    double suma = 0;
    for (const auto& v : valori) {
        suma += v;
    }
    return suma / valori.size();
}

//=================== CITIRE ===================
/// Citeste elevii din fisier
void citesteElevi(const string& numeFisier) {
    ifstream in(numeFisier);
    if (!in.is_open()) return;
    string nume, prenume, cnp;
    while (in >> nume >> prenume >> cnp) {
        catalog.emplace_back(nume, prenume, cnp);
    }
    in.close();
}

/// Citeste materiile din fisier
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
        elev->adaugaMaterie(materie, true);
        if (!noteStr.empty()) {
            istringstream noteSS(noteStr);
            string nota;
            while (getline(noteSS, nota, ',')) {
                if (!nota.empty()) {
                    string valPart = nota;
                    string dataPart;
                    size_t col = nota.find(':');
                    if (col != string::npos) {
                        valPart = nota.substr(0, col);
                        dataPart = nota.substr(col + 1);
                    }
                    elev->adaugaNota(stoi(valPart), materie, dataPart);
                }
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


/// Scrie materiile in fisier
void scrieMaterii(const string& numeFisier) {
    ofstream out(numeFisier);
    for (auto& e : catalog) {
        string cnp = e.getCNP();
        for (const auto& m : e.getMaterii()) {
            out << cnp << " " << m.nume << " note:";
            for (size_t i = 0; i < m.note.size(); i++) {
                out << m.note[i].valoare;
                if (!m.note[i].data.empty()) out << ":" << m.note[i].data;
                if (i + 1 < m.note.size()) out << ",";
            }
            out << " absente:";
            for (size_t  i = 0; i < m.abs.size(); i++) {
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

/// Citeste toate fisierele elevilor
void citesteTotCatalogul() {
    catalog.clear();

    for (const auto& entry : fs::directory_iterator("data/elevi")) {
        ifstream in(entry.path());
        if (!in.is_open()) continue;

        string nume, prenume, cnp, linie;

        getline(in, linie);  nume    = linie.substr(6);
        getline(in, linie);  prenume = linie.substr(9);
        getline(in, linie);  cnp     = linie.substr(5);

        Elev elev(nume, prenume, cnp);

        while (getline(in, linie)) {
            if (linie.empty()) continue;

            if (linie.rfind("Materie:", 0) == 0) {
                string materie = linie.substr(9);
                elev.adaugaMaterie(materie, true);

                /* -------- NOTE -------- */
                getline(in, linie);                // "Note:"
                if (linie.rfind("Note:", 0) == 0) {
                    string noteStr = linie.substr(6);
                    istringstream ss(noteStr);
                    string nota;
                    while (getline(ss, nota, ',')) {
                        if (!nota.empty()) {
                            string val = nota, data;
                            size_t col = nota.find(':');
                            if (col != string::npos) {
                                val  = nota.substr(0, col);
                                data = nota.substr(col + 1);
                            }
                            elev.adaugaNota(stoi(val), materie, data);
                        }
                    }
                }

                /* -------- MEDIA  (linie nouă de ignorat) -------- */
                getline(in, linie);                // poate fi "Media:" sau direct "Absente:"
                if (linie.rfind("Media:", 0) == 0) // dacă e "Media:", mai citeşte o linie
                    getline(in, linie);            // acum e sigur "Absente:"

                /* -------- ABSENTE -------- */
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


/// Scrie fisierul individual al unui elev
void scrieElevIndividual(const Elev& e) {
    string filename = "data/elevi/" + e.getCNP() + ".txt";
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Eroare la deschiderea fisierului pentru scriere: " << filename << "\n";
        return;
    }

    out << " Nume: " << e.getNume() << "\n";
    out << "Prenume: " << e.getPrenume() << "\n";
    out << "CNP: " << e.getCNP() << "\n\n";

    for (const auto& m : e.getMaterii()) {
        out << "Materie: " << m.nume << "\n";

        out << "Note: ";
        for (size_t i = 0; i < m.note.size(); ++i) {
            out << m.note[i].valoare;
            if (!m.note[i].data.empty()) out << ":" << m.note[i].data;
            if (i + 1 < m.note.size()) out << ",";
        }
        out << "\n";

        // Calculeaza si scrie media
        vector<int> valori = m.getNoteValori();
        double medie = calculeazaMedie(valori);
        out << "Media: " << medie << "\n";

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
