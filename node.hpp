#include <iostream>
using namespace std;
 
class Node {
    public:
        inline static string EMPTY_NODE_HASH = "56e81f171bcc55a6ff8345e692c0f86e5b48e01b996cadc001622fb5e363b421";
        static string hash(Node *n);
        static string serialize(Node *n);
        virtual string hash() = 0;
        virtual string raw() = 0;
};
