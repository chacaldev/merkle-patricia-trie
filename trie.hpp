#include "node.hpp"
#include "emptyNode.hpp"
#include "cryptUtils.hpp"

using namespace std;

class Trie {
    private:
        Node *root;
    public:
        Node *root;
        string hash();
        string get(string key);
        void put(string key, string value);
};