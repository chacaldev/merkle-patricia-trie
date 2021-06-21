#include "extension.hpp"

Extension::Extension(string path, Node *next){
    this->path = path;
    this->next = next;
}
string Extension::hash() {
    return CryptUtils::keccak256(CryptUtils::RLPEncode(this->serialize()));
}

string Extension::raw() {
    string prefixed, prefix;

    // Odd
    if(this->path.length() % 2 >0) {
        prefix = "1";
    }
    else {
        prefix = "00";
    }

    prefix = prefix + this->path;

    StringSource ss(prefix, true,
        new HexDecoder(
            new StringSink(prefixed)
        ) // HexDecoder
    ); // StringSource

    if(Node::serialize(this->next).length() >= 32) {
        prefixed = prefixed + this->next->hash();
    }
    else {
        prefixed = prefixed + this->next->raw();
    }

    return prefixed;
}

string Extension::serialize() {
    return Node::serialize(this);
}

string Extension::getPath() {
    return this->path;
}

Node* Extension::getNext() {
    return this->next;
}