#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "Hash/HashingFunctions.hpp"

int main()
{
    std::cout << sha256("text 2 be hashed") << std::endl;

    std::cout << sha256(concat("text 2 be hashed", "new")) << std::endl;

    return 0;
}
