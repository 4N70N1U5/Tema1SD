#include "numbers.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <vector>

std::ifstream i("teste.in");
std::ofstream o("rezultate.out");

Numbers::Numbers()
{
    i >> n >> m;
    srand(time(NULL));
    for (long long i = 0; i < n; i++)
    {
        V.push_back(rand() % m);
        BCK.push_back(V[i]);
    }
}

void Numbers::reset()
{
    for (long long i = 0; i < n; i++)
        V[i] = BCK[i];
}

bool Numbers::sorted()
{
    for (long long i = 0; i < n - 1; i++)
        if (V[i] > V[i + 1])
            return false;
    return true;
}

void Numbers::bucketSortForRadix(long long rb, long long pwr)
{
    std::vector < std::vector <long long> > B(1 << rb);

    for (int i = 0; i < n; i++)
    {
        B[(V[i] >> pwr) % (1 << rb)].push_back(V[i]);
    }

    long long i = 0;

    for (long long j = 0; j < 1 << rb; j++)
    {
        for (long long k = 0; k < B[j].size(); k++)
        {
            V[i++] = B[j][k];
        }
    }
}

void Numbers::radixSort()
{
    int rbs[4] = { 2, 4, 8, 16 };

    for (int aux = 0; aux < 4; aux++)
    {
        int rb = rbs[aux];

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        long long mx = V[0], d = 0, pwr = 0;
        
        for (long long i = 1; i < n; i++)
            if (mx < V[i])
                mx = V[i];

        for (mx; mx; mx = mx >> rb)
            d++;

        for (int i = 0; i < d; i++)
        {
            bucketSortForRadix(rb, pwr);
            pwr += rb;
        }

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        
        if (!sorted())
            o << "!!! Vectorul nu este sortat! - Radix Sort cu baza 2^" << rb << '\n';

        o << "Durata Radix Sort cu baza 2^" << rb << " in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
        o << "Durata Radix Sort cu baza 2^" << rb << " in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
        o << "Durata Radix Sort cu baza 2^" << rb << " in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

        o << '\n';

        std::cout << "Radix Sort with base 2^" << rb << " done!\n";

        reset();
    }

    
}

void Numbers::merge(long long lft, long long mid, long long rgt)
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

void Numbers::mergeSort(long long lft, long long rgt)
{
    if (lft >= rgt)
        return;

    long long mid = lft + (rgt - lft) / 2;
    
    mergeSort(lft, mid);
    mergeSort(mid + 1, rgt);
    merge(lft, mid, rgt);
}

void Numbers::mergeSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    mergeSort(0, n - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Merge Sort\n";

    o << "Durata Merge Sort in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
    o << "Durata Merge Sort in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
    o << "Durata Merge Sort in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

    o << '\n';

    std::cout << "Merge Sort done!\n";

    reset();
}

void Numbers::shellSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (long long g = n / 2; g > 0; g /= 2)
    {
        for (long long i = g; i < n; i++)
        {
            long long aux = V[i];

            long long j;           
            for (j = i; j >= g && V[j - g] > aux; j -= g)
                V[j] = V[j - g];
            
            V[j] = aux;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Shell Sort\n";

    o << "Durata Shell Sort in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
    o << "Durata Shell Sort in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
    o << "Durata Shell Sort in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

    o << '\n';

    std::cout << "Shell Sort done!\n";

    reset();
}

long long Numbers::partition(long long lft, long long rgt)
{
    long long p = V[rgt], i = lft - 1, j = rgt;

    while (true)
    {
        while (V[++i] < p);
        while (V[--j] > p);

        if (i >= j)
            break;

        std::swap(V[i], V[j]);
    }

    V[rgt] = V[i];
    V[i] = p;

    return i;
}

void Numbers::quickSort(long long lft, long long rgt)
{
    if (lft < rgt)
    {
        long long pvt = partition(lft, rgt);

        quickSort(lft, pvt - 1);
        quickSort(pvt + 1, rgt);
    }
}

void Numbers::quickSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    quickSort(0, n - 1);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Quick Sort\n";

    o << "Durata Quick Sort in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
    o << "Durata Quick Sort in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
    o << "Durata Quick Sort in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

    o << '\n';

    std::cout << "Quick Sort done!\n";

    reset();
}

void Numbers::countingSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    long long mn, mx;

    mn = mx = V[0];
    for (long long i = 1; i < n; i++)
    {
        if (mx < V[i])
            mx = V[i];
        if (mn > V[i])
            mn = V[i];
    }

    std::vector<long long> C(mx - mn + 1);

    for (long long i = 0; i < n; i++)
    {
        C[V[i] - mn]++;
    }

    long long i = 0;
    for (long long j = 0; j < mx - mn + 1; j++)
    {
        while (C[j])
        {
            V[i] = j + mn;
            C[j]--;
            i++;
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (!sorted())
        o << "!!! Vectorul nu este sortat! - Counting Sort\n";

    o << "Durata Counting Sort in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
    o << "Durata Counting Sort in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
    o << "Durata Counting Sort in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

    o << '\n';

    std::cout << "Counting Sort done!\n";

    reset();
}

void Numbers::cppSort()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::sort(V.begin(), V.end());

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    if (!sorted())
        o << "!!! Vectorul nu este sortat! - C++ Sort\n";

    o << "Durata C++ Sort in secunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " secunde.\n";
    o << "Durata C++ Sort in microsecunde: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) << " microsecunde.\n";
    o << "Durata C++ Sort in nanosecunde: " << (std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) << " nanosecunde.\n";

    o << '\n';

    std::cout << "C++ Sort done!\n";

    reset();
}
