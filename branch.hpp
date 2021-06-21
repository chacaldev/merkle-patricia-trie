#include "cryptUtils.hpp"
#include "emptyNode.hpp"
#include <sstream>

using namespace std;

class Branch: public Node{
    private:
        Node *branches[16];
        string value;
    public:
        string raw();
        string hash();
        void setBranch(unsigned char nibble, Node *node);
        void removeBranch(unsigned char nibble);
        void setValue(string value);
        string getValue();
        void removeValue();
        string serialize();
        bool hasValue();
        Node** getBranches();
};