#include <iostream>
#include "node.hpp"
#include "cryptUtils.hpp"

using namespace std;

class Leaf: public Node {
    private:
        string path;
        string value;
    public:
        Leaf(string path, string value);
        string hash();
        string raw();
        string serialize();
        string getPath();
        string getValue();
        void setPath(string path);
        void setValue(string value);
};
