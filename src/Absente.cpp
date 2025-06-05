/// \file Absente.cpp
/// \brief Implementarea clasei Absente.

#include "Absente.h"

/// Constructor
Absente::Absente(string d) {
    this->data = d;
    this->motivat=0;
}
/// Marcheaza absenta ca motivata
void Absente::motiveaza() {
    this->motivat=1;
}
