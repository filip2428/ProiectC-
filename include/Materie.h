//
// Created by András on 03/06/2025.
//

#ifndef MATERIE_H
#define MATERIE_H
#include "Absente.h"
#include "Nota.h"
#include <vector>

/// \brief Reprezinta o materie studiata de un elev.
class Materie {
public:
    /// Numele materiei.
    string nume;

    /// Lista de absente asociate.
    vector<Absente> abs;

    /// Lista de note obtinute.
    vector<Nota> note;

    /// Constructor.
    explicit Materie(string nume);

    /// Returneaza valorile notelor pentru calculul mediei.
    vector<int> getNoteValori() const;

    /// Adauga o absenta.
    void addAbsenta(string data);

    /// Sterge o absenta.
    void delAbsenta(string data);

    /// Adauga o nota.
    void addNota(int valoare, const string& data="");

    /// Sterge o nota.
    void delNota(int valoare, const string& data="");
};



#endif //MATERIE_H
