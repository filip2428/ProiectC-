//
// Created by András on 03/06/2025.
//

#include "Absente.h"

Absente::Absente(string d) {
    this->data = d;
    this->motivat=0;
}
void Absente::motiveaza() {
    this->motivat=1;
}
