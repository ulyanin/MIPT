//
// Created by ulyanin on 14.10.17.
//

#include <iostream>


int main()
{
    int z;
    std::cin >> z;
    int x = 1;
    while ((1 << x) - 2 < z) {
        ++x;
    }
    std::cout << 32 - x << std::endl;
}