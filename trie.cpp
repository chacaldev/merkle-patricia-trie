#include "trie.hpp"
#include "emptyNode.hpp"
#include "leaf.hpp"
#include "nibble.hpp"
#include "branch.hpp"
#include "extension.hpp"
#include <string>

using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T*) {
   return is_base_of<Base, T>::value;
}

string Trie::hash() {
    if(this->root == NULL) {
        return EmptyNode::EMPTY_NODE_HASH;
    }
    else {
        return this->root->hash();
    }
}

string Trie::get(string key) {
    string nibbles;
    Node *node = this->root;

    StringSource ss(key, true,
        new HexDecoder(
            new StringSink(nibbles)
        ) // HexDecoder
    ); // StringSource

    while(true) {
        if(node == NULL){
            return "";
        }

        if(instanceof<Leaf>(node)) {
            Leaf *l = (Leaf*) node;
            string path = l->getPath();
            int matched = Nibble::MatchedLength(path, nibbles);
            if(matched != path.length() || matched != nibbles.length()) {
                return "";
            }
            else {
                return l->getValue();
            }
        }

        if(instanceof<Branch>(node)) {
            Branch *branch = (Branch*) node;
            if(nibbles.length() == 0) {
                return branch->getValue();
            }
            string b(1, nibbles[0]);
            nibbles = nibbles.substr(1, nibbles.length()-1);
            node = branch->getBranches()[stoi(b)];
            continue;
        }

        if(instanceof<Extension>(node)) {
            Extension *ext = (Extension *) node;
            string path = ext->getPath();
            int matched = Nibble::MatchedLength(path, nibbles);
            if(matched < path.length()) {
                return "";
            }
            
            nibbles = nibbles.substr(matched, nibbles.length()-matched);
            node = ext->getNext();
            continue;
        }

    }
}

void Trie::put(string key, string value) {
    string nibbles;
    Node *node = this->root;

    StringSource ss(key, true,
        new HexDecoder(
            new StringSink(nibbles)
        ) // HexDecoder
    ); // StringSource

    while(true) {
        if(node == NULL) {
            node = new Leaf(nibbles, value);
            return;
        }

        if(instanceof<Leaf>(node)) {
            Leaf *l = (Leaf*) node;
            string path = l->getPath();
            int matched = Nibble::MatchedLength(path, nibbles);
            if(matched == nibbles.length() && matched == path.length()) {
                node = new Leaf(path, value);
                return;
            }

            Branch *b = new Branch();

            if(matched == path.length()) {
                b->setValue(l->getValue());
            }

            if(matched == nibbles.length()) {
                b->setValue(value);
            }

            if(matched > 0) {
                Extension *ext = new Extension(path.substr(0,matched), b);
                node = ext;
            }
            else {
                node = b;
            }

            if(matched < path.length()) {
                string branchNibble(1, path[matched]);
                string leafNibbles = path.substr(matched, path.length()-matched);
                Leaf *newLeaf = new Leaf(leafNibbles, l->getValue());
                b->setBranch((char)branchNibble.c_str(), newLeaf);
            }

            if(matched < nibbles.length()) {
                string branchNibble(1, nibbles[matched]);
                string leafNibbles = nibbles.substr(matched, nibbles.length()-matched);
                Leaf *newLeaf = new Leaf(leafNibbles, value);
                b->setBranch((char)branchNibble.c_str(), newLeaf);
            }

            return;
        }

        if(instanceof<Branch>(node)) {
            Branch *branch = (Branch*) node;
            if(nibbles.length() == 0) {
                branch->setValue(value);
                return;
            }

            string b(1, nibbles[0]);
            string remaining = nibbles.substr(1, nibbles.length()-1);
            nibbles = remaining;
            node = branch->getBranches()[stoi(b)];
            continue;
        }

        if(instanceof<Extension>(node)) {
            Extension *ext = (Extension*) node;
            string path = ext->getPath();
            int matched = Nibble::MatchedLength(path, nibbles);
            if(matched < path.length()) {
                string extNibbles = path.substr(0,matched-1);
                string branchNibble(1, path[matched]);
                string extRemainingNibbles = path.substr(matched, path.length()-matched);
                string nodeBranchNibble(1, nibbles[matched]);
                string nodeLeafNibbles = nibbles.substr(matched, nibbles.length()-matched);
                Branch *b = new Branch();
                if(extRemainingNibbles.length() == 0) {
                    b->setBranch((char)branchNibble.c_str(), ext->getNext());
                }
                else {
                    Extension *newExt = new Extension(extRemainingNibbles, ext->getNext());
                    b->setBranch((char)branchNibble.c_str(), newExt);
                }

                Leaf *remainingLeaf = new Leaf(nodeLeafNibbles, value);
                b->setBranch((char)nodeBranchNibble.c_str(), remainingLeaf);

                if(extNibbles.length() == 0) {
                    node = b;
                }
                else {
                    node = new Extension(extNibbles, b);
                }
                return;
            }

            nibbles = nibbles.substr(matched, nibbles.length()-matched);
            node = ext->getNext();
            continue;
        }
    }
}