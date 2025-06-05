//
// Created by András on 03/06/2025.
//

#ifndef ABSENTE_H
#define ABSENTE_H
#include<iostream>
#include<string>
using namespace std;


/// \brief Reprezinta o absenta a unui elev.
class Absente {
public:
    /// Data absentei.
    string data;

    /// Flag ce indica daca absenta este motivata.
    bool motivat;

    /// Constructor.
    explicit Absente(string data);

    /// Marcheaza absenta ca motivata.
    void motiveaza();

    /// Comparatie dupa data.
    bool operator==(const Absente& other) const {
        return this->data == other.data;
    }
};



#endif //ABSENTE_H
