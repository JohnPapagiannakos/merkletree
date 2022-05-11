#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "Hash/HashingFunctions.hpp"
#include "HashTree.hpp"

std::string random_string(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

int main()
{
    HTree<int> HT;

    std::vector<std::pair<int, HASHTYPE>> datablocks;

    const int blocks_num = 100;

    srand(0);
    // srand(time(0));
    for(int l=0; l<blocks_num; l++)
    {
        HASHTYPE hash = random_string(rand() % 2048);
        std::pair<int, HASHTYPE> tmp = std::make_pair(l, hash);
        datablocks.push_back(tmp);
    }
    HT.construct_tree(datablocks);
    std::cout << HT.compute_hash() << std::endl;
    // HT.topview();

    return 0;
}
