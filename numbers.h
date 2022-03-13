#ifndef numbers_H
#define numbers_H

#include <vector>

class Numbers
{
private:
    std::vector <long long> V, BCK;
    long long n, m;
public:
    Numbers();
    void reset();
    bool sorted();
    void bucketSortForRadix(long long, long long);
    void radixSort();
    void merge(long long, long long, long long);
    void mergeSort(long long, long long);
    void mergeSort();
    void shellSort();
    long long partition(long long, long long);
    void quickSort(long long, long long);
    void quickSort();
    void countingSort();
    void cppSort();
};

#endif