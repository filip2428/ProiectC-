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
    string getNume() const {
        return nume;
    };
    string getPrenume() const {
        return prenume;
    };
    void adaugaAbsenta(string,string);
    void motiveazaAbsenta(string,string);
    void adaugaNota(int nota, const string& materie, const string& data="");
    void stergeNota(int nota, const string& materie, const string& data="");
    void adaugaMaterie(const string& numeMaterie, bool silent=false);
    void stergeMaterie(const string& numeMaterie);
    string getCNP() const{ return cnp; };
    const vector<Materie>& getMaterii() const {
        return materii;
    }
    friend ostream& operator <<(ostream& os, const Elev& e);
};

#endif //ELEV_H
