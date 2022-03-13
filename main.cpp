#include "numbers.h"
#include <iostream>

int main()
{
    int n;

    std::cout << "Number of tests: ";

    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        Numbers l;
        
        l.radixSort();
        
        l.mergeSort();
        
        l.shellSort();
        
        l.quickSort();
        
        l.countingSort();
        
        l.cppSort();
    }
    
    return 0;
}
