#include <iostream>
#include <Windows.h>

using namespace std;

struct Node {
    string data;
    Node *rc = nullptr;
    Node *lc = nullptr;

};

class Tree {
private:
    Node *root;
    int deepth = -1;
public:

    Tree(string rootData) {
        this->root = new Node;
        root->data = rootData;
    }


    void addElement(string data) {
        Node *newElement = new Node();
        newElement->data = data;
        Node *currentNode = this->root;
        while (true) {
            if (newElement->data > currentNode->data) {
                if (currentNode->rc == nullptr) {
                    currentNode->rc = newElement;
                    return;
                } else {
                    currentNode = currentNode->rc;
                }
            } else if (newElement->data < currentNode->data) {
                if (currentNode->lc == nullptr) {
                    currentNode->lc = newElement;
                    return;
                } else {
                    currentNode = currentNode->lc;
                }
            } else {
                return;
            }
        }
    }


    void symmetricalTravers(Node *root) {
        if (root) {
            symmetricalTravers(root->lc);
            cout << root->data << " ";
            symmetricalTravers(root->rc);
        }
    }

    void maxDeepth(Node *root, int deepth) {
        if (root) {
            maxDeepth(root->lc, deepth + 1);
            maxDeepth(root->rc, deepth + 1);
            this->deepth = max(deepth, this->deepth);
        }
        if (root == this->root) {
            cout << "\nВысота дерева: " << this->deepth << endl;
        }
    }

    Node *getRoot() {
        return root;
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Tree *tree = new Tree("d");
    tree->addElement("e");
    tree->addElement("b");
    tree->addElement("c");
    tree->addElement("c");
    tree->addElement("r");
    tree->addElement("a");
    tree->addElement("g");


    tree->symmetricalTravers(tree->getRoot());
    tree->maxDeepth(tree->getRoot(), 1);
}