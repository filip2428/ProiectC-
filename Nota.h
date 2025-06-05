#ifndef NOTA_H
#define NOTA_H
#include <string>
class Nota {
public:
    int valoare;
    std::string data;
    Nota(int valoare = 0, const std::string& data = "");
};
#endif // NOTA_H
