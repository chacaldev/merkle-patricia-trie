#include "cryptUtils.hpp"

using namespace std;
using namespace CryptoPP;


string CryptUtils::keccak256(string value){
    string digest, vdec, vcod;
    StringSource ssi(value, true,
        new HexDecoder(
            new StringSink(vdec)
        ) // HexDecoder
    ); // StringSource

    Keccak_256 hash;
    hash.Update((const CryptoPP::byte*)vdec.data(), vdec.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);

    // Encoding result hash
    StringSource sso(digest, true,
        new HexEncoder(
            new StringSink(vcod)
        )
    );
    
    return vcod;
}

string CryptUtils::RLPEncode(string value){
    RLP rlp;
    return rlp.encode(value);
}