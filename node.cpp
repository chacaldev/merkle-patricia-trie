#include <iostream>
#include "cryptUtils.hpp"
#include "emptyNode.hpp"

using namespace std;

string Node::hash(Node *n) {
    EmptyNode empty;
    if(n == NULL) {
      return empty.hash();
    }
    else {
      return n->hash();
    }
}

string Node::serialize(Node *n) {
    string raw;
    EmptyNode empty;
    if(n == NULL) {
        raw = empty.raw();
    }
    else {
        raw = n->raw();
    }
    return CryptUtils::RLPEncode(raw);
}
