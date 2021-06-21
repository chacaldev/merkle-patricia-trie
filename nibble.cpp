#include "nibble.hpp"

using namespace std;

int Nibble::MatchedLength(string n1, string n2) {
    int matched = 0;
    for(int i = 0; i < n1.length() && i < n2.length(); i++) {
        if(n1[i] == n2[i]){
            matched++;
        }
        else {
            break;
        }
    }
    return matched;
}