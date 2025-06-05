//
// Created by András on 03/06/2025.
//

#include "Materie.h"
#include "Nota.h"
#include <algorithm>

Materie::Materie(string a) {
    this->nume=a;
}

void Materie::addAbsenta(string data) {
    this->abs.push_back(Absente(data));
}

void Materie::delAbsenta(string data) {
    auto it = std::find_if(abs.begin(), abs.end(),
        [&](const Absente& a) { return a.data == data; });
    if (it != abs.end()) {
        abs.erase(it);
    }
}

void Materie::addNota(int valoare, const string& data) {
    note.emplace_back(valoare, data);
}

void Materie::delNota(int valoare, const string& data) {
    auto it = std::find_if(note.begin(), note.end(), [&](const Nota& n){
        return n.valoare == valoare && (data.empty() || n.data == data);
    });
    if (it != note.end()) {
        note.erase(it);
    }
}

vector<int> Materie::getNoteValori() const {
    vector<int> valori;
    for (const auto& n : note) {
        valori.push_back(n.valoare);
    }
    return valori;
}
