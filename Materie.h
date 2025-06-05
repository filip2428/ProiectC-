//
// Created by András on 03/06/2025.
//

#ifndef MATERIE_H
#define MATERIE_H
#include "Absente.h"
#include "Nota.h"
#include <vector>

class Materie {
    public:
    string nume;
    vector<Absente> abs;
    vector<Nota> note;
    Materie(string);
    vector<int> getNoteValori() const;
    void addAbsenta(string);
    void delAbsenta(string);
    void addNota(int valoare, const string& data="");
    void delNota(int valoare, const string& data="");
};



#endif //MATERIE_H
