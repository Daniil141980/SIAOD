#include <iostream>
#include <Windows.h>

using namespace std;

struct Node {
    string data;
    Node *right = nullptr;
    Node *left = nullptr;

};

class BinTree {
private:
    Node *root;
    int deep = -1;
    int find = -1;
public:

    BinTree(string rootData) {
        this->root = new Node;
        root->data = rootData;
    }


    void addElement(string data) {
        Node *newElement = new Node();
        newElement->data = data;
        Node *currentNode = this->root;
        while (true) {
            if (newElement->data > currentNode->data) {
                if (currentNode->right == nullptr) {
                    currentNode->right = newElement;
                    return;
                } else {
                    currentNode = currentNode->right;
                }
            } else if (newElement->data < currentNode->data) {
                if (currentNode->left == nullptr) {
                    currentNode->left = newElement;
                    return;
                } else {
                    currentNode = currentNode->left;
                }
            } else {
                return;
            }
        }
    }

    void preOrder(Node *root) {
        if (root) {
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void inOrder(Node *root) {
        if (root) {
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);
        }
    }

    void findDeep(Node *root, int deep, string value) {
        if (root) {
            if (root->data == value) {
                find = deep;
            }
            findDeep(root->left, deep + 1, value);
            findDeep(root->right, deep + 1, value);
        }
        if (root == this->root) {
            cout << "Длина пути: " << this->find << endl;
        }
    }

    void maxDeep(Node *root, int deep) {
        if (root) {
            maxDeep(root->left, deep + 1);
            maxDeep(root->right, deep + 1);
            this->deep = max(deep, this->deep);
        }
        if (root == this->root) {
            cout << "Высота дерева: " << this->deep << endl;
        }
    }

    Node *getRoot() {
        return root;
    }
};


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BinTree *tree = new BinTree("d");
    tree->addElement("e");
    tree->addElement("b");
    tree->addElement("c");
    tree->addElement("c");
    tree->addElement("r");
    tree->addElement("a");
    tree->addElement("g");
    tree->preOrder(tree->getRoot());
    cout << endl;
    tree->inOrder(tree->getRoot());
    cout << endl;
    string val = "a";
    tree->findDeep(tree->getRoot(), 1, val);
    tree->maxDeep(tree->getRoot(), 1);
}