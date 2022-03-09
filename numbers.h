#ifndef numbers_H
#define numbers_H

#include <vector>

class numbers
{
private:
    std::vector<long long> V, BCK;
    long long n, m, b;
public:
    numbers();
    // ~numbers();
    void reset();
    void afisare();
};

#endif