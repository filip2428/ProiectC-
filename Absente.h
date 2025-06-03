//
// Created by András on 03/06/2025.
//

#ifndef ABSENTE_H
#define ABSENTE_H
#include<iostream>
#include<string>
using namespace std;


class Absente {
    public:
    string data;
    bool motivat;
    Absente(string);
    void motiveaza();
    bool operator==(const Absente& other) const {
        return this->data == other.data;
    }
};



#endif //ABSENTE_H
