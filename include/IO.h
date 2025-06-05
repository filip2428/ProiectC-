/// \file IO.h
/// \brief Functii de citire si scriere pentru catalog.
#ifndef IO_H
#define IO_H
#include <filesystem>
#include <string>
#include "Elev.h"
using namespace std;
namespace fs = std::filesystem;

/// Citeste elevii dintr-un fisier text.
void citesteElevi(const string& numeFisier);

/// Citeste materiile si notele dintr-un fisier text.
void citesteMaterii(const string& numeFisier);

/// Scrie toti elevii intr-un fisier text.
void scrieElevi(const string& numeFisier);

/// Scrie materiile intr-un fisier text.
void scrieMaterii(const string& numeFisier);

/// Scrie fisierul individual al unui elev.
void scrieElevIndividual(const Elev& e);

/// Citeste toate fisierele din directorul de date.
void citesteTotCatalogul();

#endif
