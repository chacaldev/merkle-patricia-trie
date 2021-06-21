#include <cryptopp/keccak.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include "lib/RLP.h"

using namespace std;
using namespace CryptoPP;

class CryptUtils {
    public:
        static string keccak256(string value);
        static string RLPEncode(string value);
};
