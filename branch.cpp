#include "branch.hpp"

using namespace std;

int nibtoi(unsigned char nibble) {
    unsigned int nib;   
    stringstream ss;
    ss << hex << nibble;
    ss >> nib;
    return nib;
}

string Branch::raw() {
    string hashes[17];
    EmptyNode empty;
    for(int i = 0; i < 16; i++) {
        if(this->branches[i] == NULL) {
            hashes[i] = empty.raw();
        }
        else {
            Node *n = this->branches[i];
            if(Node::serialize(n).length() >= 32) {
                hashes[i] = n->hash();
            }
            else {
                hashes[i] = n->raw();
            }
        }
    }
    hashes[16] = this->value;
    string resp;
    for(int i = 0; i < 17; i++){
        resp = resp + hashes[i];
    }
    return resp;
}

string Branch::hash(){
    return CryptUtils::keccak256(this->serialize());
}
void Branch::setBranch(unsigned char nibble, Node *node) {
    this->branches[nibtoi(nibble)] = node;
}

void Branch::removeBranch(unsigned char nibble) {
    this->branches[nibtoi(nibble)] = NULL;
}

void Branch::setValue(string value) {
    this->value = value;
}

string Branch::getValue() {
    return this->value;
}

void Branch::removeValue() {
    this->value = "";
}

string Branch::serialize() {
    return Node::serialize(this);
}

bool Branch::hasValue() {
    return this->value.length() != 0;
}

Node** Branch::getBranches() {
    return this->branches;
}