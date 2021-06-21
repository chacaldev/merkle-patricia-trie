#include "node.hpp"
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

using namespace std;

class EmptyNode: public Node{
    public:
        string raw();
        string hash();        
};