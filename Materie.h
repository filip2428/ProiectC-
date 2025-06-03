//
// Created by András on 03/06/2025.
//

#ifndef MATERIE_H
#define MATERIE_H
#include "Absente.h"
#include <vector>

class Materie {
    public:
    string nume;
    vector<Absente> abs;
    vector<int>note;
    Materie(string);
    void addAbsenta(string);
    void delAbsenta(string);
};



#endif //MATERIE_H
