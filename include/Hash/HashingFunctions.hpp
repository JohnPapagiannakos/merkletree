#ifndef HASHINGFUNCTIONS_HPP
#define HASHINGFUNCTIONS_HPP

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

std::string sha256(const std::string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Quick & Dirty hashing based on Szudzik's function.
int pseudo_hash(const int a, const int b)
{
    return a >= b ? a * a + a + b : a + b * b;
}

#endif