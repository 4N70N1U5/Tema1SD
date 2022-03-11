#include "numbers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <vector>

std::ifstream i("teste.in");
std::ofstream o("rezultate.out");

numbers::numbers()
{
    i >> n >> m >> b;
    srand(time(NULL));
    for (long long i = 0; i < n; i++)
    {
        V.push_back(rand() % m);
        BCK.push_back(V[i]);
    }
}

void numbers::reset()
{
    for (long long i = 0; i < n; i++)
        V[i] = BCK[i];
}

bool numbers::sorted()
{
    for (long long i = 0; i < n - 1; i++)
        if (V[i] > V[i + 1])
            return false;
    return true;
}

void numbers::radixSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    long long mx = V[0];
    for (long long i = 1; i < n; i++)
        if (mx < V[i])
            mx = V[i];

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Radix Sort\n";

    o << "Durata Radix Sort in secunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0  << " secunde.\n";
    o << "Durata Radix Sort in microsecunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())  << " microsecunde.\n";
    o << "Durata Radix Sort in nanosecunde: " <<  (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count())<< " nanosecunde.\n";

    o << '\n';

    reset();
}

void numbers::merge(long long lft, long long mid, long long rgt)
{
    long long n_lft = mid - lft + 1, n_rgt = rgt - mid;

    std::vector <long long> V_lft(n_lft), V_rgt(n_rgt);

    for (long long i = 0; i < n_lft; i++)
        V_lft[i] = V[lft + i];

    for (long long i = 0; i < n_rgt; i++)
        V_rgt[i] = V[mid + i + 1];

    long long i = lft, i_lft = 0, i_rgt = 0;

    while (i_lft < n_lft && i_rgt < n_rgt)
    {
        if (V_lft[i_lft] <= V_rgt[i_rgt])
        {
            V[i] = V_lft[i_lft];
            i_lft++;
        }
        else
        {
            V[i] = V_rgt[i_rgt];
            i_rgt++;
        }
        i++;
    }

    while (i_lft < n_lft)
    {
        V[i] = V_lft[i_lft];
        i_lft++;
        i++;
    }

    while (i_rgt < n_rgt)
    {
        V[i] = V_rgt[i_rgt];
        i_rgt++;
        i++;
    }
}

void numbers::mergeSort(long long lft, long long rgt)
{
    if (lft >= rgt)
        return;

    long long mid = lft + (rgt - lft) / 2;
    mergeSort(lft, mid);
    mergeSort(mid + 1, rgt);
    merge(lft, mid, rgt);
}

void numbers::mergeSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    mergeSort(0, n - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Merge Sort\n";

    o << "Durata Merge Sort in secunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0  << " secunde.\n";
    o << "Durata Merge Sort in microsecunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())  << " microsecunde.\n";
    o << "Durata Merge Sort in nanosecunde: " <<  (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count())<< " nanosecunde.\n";

    o << '\n';

    reset();
}

void numbers::shellSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int g = n / 2; g > 0; g /= 2)
    {
        for (int i = g; i < n; i++)
        {
            int aux = V[i];

            int j;           
            for (j = i; j >= g && V[j - g] > aux; j -= g)
                V[j] = V[j - g];
            
            V[j] = aux;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Shell Sort\n";

    o << "Durata Shell Sort in secunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0  << " secunde.\n";
    o << "Durata Shell Sort in microsecunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())  << " microsecunde.\n";
    o << "Durata Shell Sort in nanosecunde: " <<  (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count())<< " nanosecunde.\n";

    o << '\n';

    reset();
}

void numbers::cppSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::sort(V.begin(), V.end());

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - C++ Sort\n";

    o << "Durata C++ Sort in secunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0  << " secunde.\n";
    o << "Durata C++ Sort in microsecunde: " <<  (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count())  << " microsecunde.\n";
    o << "Durata C++ Sort in nanosecunde: " <<  (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count())<< " nanosecunde.\n";

    o << '\n';

    reset();
}
