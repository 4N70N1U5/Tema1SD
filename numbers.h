#ifndef numbers_H
#define numbers_H

#include <vector>

class Numbers
{
private:
    std::vector<long long> V, BCK;
    long long n, m, b;
public:
    Numbers();
    void reset();
    bool sorted();
    void radixSort();
    void merge(long long, long long, long long);
    void mergeSort(long long, long long);
    void mergeSort();
    void shellSort();
    void cppSort();
};

#endif