#ifndef NOTA_H
#define NOTA_H
#include <string>
/// \brief Structura pentru o nota.
class Nota {
public:
    /// Valoarea notei.
    int valoare;

    /// Data la care a fost obtinuta nota.
    std::string data;

    /// Constructor.
    Nota(int valoare = 0, const std::string& data = "");
};
#endif // NOTA_H
