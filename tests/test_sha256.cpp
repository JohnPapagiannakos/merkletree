#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "Hash/HashingFunctions.hpp"

int main()
{
    std::cout << sha256("1234567890_1") << std::endl;
    return 0;
}
