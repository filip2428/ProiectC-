//
// Created by András on 03/06/2025.
//

#include "Materie.h"
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
