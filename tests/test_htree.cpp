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

    const int blocks_num = 7;

    srand(0);
    // srand(time(0));
    for(int l=0; l<blocks_num; l++)
    {
        HASHTYPE hash = random_string(rand() % 64);
        std::pair<int, HASHTYPE> tmp = std::make_pair(l, hash);
        datablocks.push_back(tmp);
    }
    HT.construct_tree(datablocks);
    std::cout << HT.compute_hash() << std::endl;
    // HT.topview();

    // test hashing
    HASHTYPE H01, H23, H45, H67;
    HASHTYPE H0123, H4567;
    HASHTYPE Hroot;

    // Hash each transaction ID before testing
    for (int l = 0; l < blocks_num; l++)
    {
        datablocks[l].second = sha256(datablocks[l].second);
        // std::cout << l << "," << datablocks[l].second << std::endl;
    }

    H01 = sha256(concat(datablocks[0].second, datablocks[1].second));
    H23 = sha256(concat(datablocks[2].second, datablocks[3].second));
    H45 = sha256(concat(datablocks[4].second, datablocks[5].second));
    H67 = sha256(concat(datablocks[6].second, ""));

    H0123 = sha256(concat(H01, H23));
    H4567 = sha256(concat(H45, H67));

    Hroot = sha256(concat(H0123, H4567));

    std::cout << Hroot << std::endl;

    if (Hroot.compare(HT.compute_hash())==0)
        std::cout << "test succeed!" << std::endl;
    else
        std::cout << "test failed!" << std::endl;
    return 0;
}
