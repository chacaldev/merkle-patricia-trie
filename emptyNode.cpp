#include "emptyNode.hpp"

using namespace std;
using namespace CryptoPP;

string EmptyNode::raw() {
    return "";
}

string EmptyNode::hash() {
    string resp;
    StringSource ss("56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421", true,
        new HexDecoder(
            new StringSink(resp)
        ) // HexDecoder
    ); // StringSource

    return resp;
}