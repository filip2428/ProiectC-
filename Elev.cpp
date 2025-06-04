//
// Created by András on 03/06/2025.
//

#include "Elev.h"

#include <iostream>
#include <ostream>


Elev::Elev(string nume, string prenume, string cnp) {
    this->nume = nume;
    this->prenume = prenume;
    this->cnp = cnp;
}

ostream& operator<<(ostream& os, const Elev& elev) {
    os<<elev.nume<<' '<<elev.prenume<<' '<<elev.cnp;
    return os;
}

void Elev::adaugaAbsenta(string data, string materie) {
    for (auto& i : materii) {
        if (i.nume == materie) {
            i.addAbsenta(data);
            return;
        }
    }
    cout << "Nu s-a gasit materia\n";
}

void Elev::stergeAbsenta(string data, string materie) {
    for (auto& i : materii) {
        if (i.nume == materie) {
            i.delAbsenta(data);
            return;
        }
    }
    cout << "Nu s-a gasit materia\n";
}

void Elev::motiveazaAbsenta(string data, string materie) {
    for (auto& i : materii) {
        if (i.nume == materie) {
            for (auto& abs : i.abs) {
                if (abs.data == data) {
                    abs.motiveaza();
                    return;
                }
            }
        }
    }
    cout << "Nu s-a gasit materia sau absenta\n";
}

void Elev::adaugaNota(int nota, string materie) {
    for (auto& i : materii) {
        if (i.nume == materie) {
            i.note.push_back(nota);
            return;
        }
    }
    cout << "Nu s-a gasit materia\n";
}

void Elev::stergeNota(int nota, string materie) {
    for (auto& i : materii) {
        if (i.nume == materie) {
            auto it = find(i.note.begin(), i.note.end(), nota);
            if (it != i.note.end()) {
                i.note.erase(it);
            } else {
                cout << "Nota nu a fost gasita\n";
            }
            return;
        }
    }
    cout << "Nu s-a gasit materia\n";
}

void Elev::adaugaMaterie(const string& numeMaterie) {
    for (const auto& m : materii) {
        if (m.nume == numeMaterie) {
            cout << "Materia " << numeMaterie << " exista deja.\n";
            return;
        }
    }
    materii.emplace_back(numeMaterie);
    cout << "Materia " << numeMaterie << " a fost adaugata elevului " << nume << " " << prenume << ".\n";
}

void Elev::stergeMaterie(const string& numeMaterie) {
    auto it = std::remove_if(materii.begin(), materii.end(),
                             [&](const Materie& m) { return m.nume == numeMaterie; });

    if (it != materii.end()) {
        materii.erase(it, materii.end());
        cout << "Materia " << numeMaterie << " a fost stearsa.\n";
    } else {
        cout << "Materia " << numeMaterie << " nu a fost gasita.\n";
    }
}


