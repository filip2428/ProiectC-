// IO.h
#ifndef IO_H
#define IO_H
#include <filesystem>
#include <string>
#include "Elev.h"
using namespace std;
namespace fs = std::filesystem;

void citesteElevi(const string& numeFisier);
void citesteMaterii(const string& numeFisier);
void scrieElevi(const string& numeFisier);
void scrieMaterii(const string& numeFisier);
void scrieElevIndividual(const Elev& e);
void citesteTotCatalogul();

#endif
