#include "leaf.hpp"

using namespace std;

Leaf::Leaf(string path, string value) {
    this->path = path;
    this->value = value;
}

string Leaf::hash() {
    return CryptUtils::keccak256(this->serialize());
}

string Leaf::raw() {
    string prefix, prefixed;
    if(this->path.length() % 2 > 0) {
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

    return prefixed + this->value;
}

string Leaf::serialize() {
    return Node::serialize(this);
}

string Leaf::getPath() {
    return this->path;
}

string Leaf::getValue() {
    return this->value;
}

void Leaf::setPath(string path) {
    this->path = path;
}

void Leaf::setValue(string value) {
    this->value = value;
}