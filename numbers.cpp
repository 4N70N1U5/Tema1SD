#include "numbers.h"
#include <iostream>
#include <vector>
#include <time.h>

numbers::numbers()
{
    std::cin >> n >> m >> b;
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        V.push_back(rand() % m);
        BCK.push_back(V[i]);
    }
}

void numbers::reset()
{
    for (int i = 0; i < n; i++)
        V[i] = BCK[i];
}

void numbers::afisare()
{
    std::cout << n << " " << m << " " << b << '\n';
    for (int i = 0; i < n; i++)
        std::cout << V[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << BCK[i] << " ";
}
