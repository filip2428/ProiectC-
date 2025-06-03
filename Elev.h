//
// Created by András on 03/06/2025.
//

#ifndef ELEV_H
#define ELEV_H
#include <string>
#include <vector>
#include <algorithm>
#include "Absente.h"
#include "Materie.h"
using namespace std;

class Elev {
private:
    string nume, prenume, cnp;
    vector<Materie> materii;

public:
    Elev(string nume, string prenume, string cnp);
    void adaugaAbsenta(string,string);
    void stergeAbsenta(string,string);
    void motiveazaAbsenta(string,string);
    void adaugaNota(int nota, string materie);
    void stergeNota(int nota, string materie);
    string getCNP() const{ return cnp; };
    friend ostream& operator <<(ostream& os, const Elev&);
};

#endif //ELEV_H
