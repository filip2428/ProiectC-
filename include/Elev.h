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

/// \brief Reprezinta un elev cu note, absente si materii.
class Elev {
private:
    string nume, prenume, cnp;
    vector<Materie> materii;

public:
    /// \brief Constructor.
    /// \param nume Numele elevului.
    /// \param prenume Prenumele elevului.
    /// \param cnp Codul numeric personal.
    Elev(string nume, string prenume, string cnp);
    string getNume() const {
        return nume;
    };
    string getPrenume() const {
        return prenume;
    };
    /// Adauga o absenta la o materie.
    void adaugaAbsenta(string data, string materie);

    /// Marcheaza o absenta ca motivata.
    void motiveazaAbsenta(string data, string materie);

    /// Adauga o nota la o materie.
    void adaugaNota(int nota, const string& materie, const string& data="");

    /// Sterge o nota dintr-o materie.
    void stergeNota(int nota, const string& materie, const string& data="");

    /// Adauga o materie noua.
    void adaugaMaterie(const string& numeMaterie, bool silent=false);

    /// Sterge o materie existenta.
    void stergeMaterie(const string& numeMaterie);
    string getCNP() const{ return cnp; };
    const vector<Materie>& getMaterii() const {
        return materii;
    }
    /// Operator de afisare.
    friend ostream& operator<<(ostream& os, const Elev& e);
};

#endif //ELEV_H
