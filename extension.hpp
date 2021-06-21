#include <iostream>
#include "node.hpp"
#include "cryptUtils.hpp"

using namespace std;

class Extension: public Node {
    private:
        string path;
        Node *next;
    public:
        Extension(string path, Node *next);
        string hash();
        string raw();
        string serialize();
        string getPath();
        Node* getNext();
};