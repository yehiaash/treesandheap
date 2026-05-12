#include <iostream>
#include <string>
#define ll long long
#define nll "\n"
using namespace std;
struct Book
{
    int id;
    string title;
    string author;
};

struct Node
{
    Book data;
    Node* left;
    Node* right;
    int height;
};

class BSTBook
{
private:
    Node* root;

public:
    BSTBook()
    {
        root = nullptr;
    }

    void insert(Book book)
    {
        Node* newNode = new Node;
        newNode->data = book;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) // first time
        {
            root = newNode;
            return;
        }

        Node* current = root;
        Node* parent = nullptr;
        while (current != 0)
        {
            parent = current;
            if (current->data.id > newNode->data.id) // looking for the right node to insert newnode
                current = current->left;
            else
                current = current->right;
        }
        if (parent->data.id > newNode->data.id) // insert newnode
            parent->left = newNode;
        else
            parent->right = newNode;
    }

    Node* search(int id)
    {

        Node* current = root;
        Node* parent = nullptr;
        while (current != 0)
        {
            parent = current;
            if (current->data.id == id)
            {
                return current;
            }
            else if (current->data.id > id)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }
    void deleteBook(int id)
    {
        Node* current = root;
        Node* parent = nullptr;

        // find node + parent
        while (current != nullptr && current->data.id != id)
        {
            parent = current;

            if (id < current->data.id)
                current = current->left;
            else
                current = current->right;
        }

        if (current == nullptr)
            return; // not found

        // CASE 2: two children
        if (current->left != nullptr && current->right != nullptr)
        {
            Node* successorParent = current;
            Node* successor = current->right;

            while (successor->left != nullptr)
            {
                successorParent = successor;
                successor = successor->left;
            }

            current->data = successor->data;
            current = successor;
            parent = successorParent;
        }

        // CASE 1 & 3: one or zero child
        Node* child = (current->left != nullptr) ? current->left : current->right;

        if (parent == nullptr)
        {
            root = child; // deleting root
        }
        else if (parent->left == current)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }

        delete current;
    }
    void display()
    {
        display(root);
    }
    void display(Node* root)
    {
        if (root == nullptr)
            return;

        display(root->left);
        visit(root);
        display(root->right);
    }
    void visit(Node* root)
    {
        cout << "------------------------\n";
        cout << "ID     : " << root->data.id << "\n";
        cout << "Title  : " << root->data.title << "\n";
        cout << "Author : " << root->data.author << "\n";
        cout << "------------------------\n\n";
    }

    void printrange(Node* root, int minID, int maxID) {
        if (root == nullptr) return;

        if (root->data.id > minID) {
            printrange(root->left, minID, maxID);
        }

        if (root->data.id >= minID && root->data.id <= maxID) {
            visit(root);
        }

        if (root->data.id < maxID) {
            printrange(root->right, minID, maxID);
        }
    }

    void printINrange(int minID, int maxID) {
        printrange(root, minID, maxID);
    }

    Node* closest(Node* root, int target) {
        Node* closest = root;
        while (root != nullptr) {
            if (abs(root->data.id - target) < abs(closest->data.id - target)) {
                closest = root;
            }

            if (root->data.id == target)
                return root;
            if (root->data.id > target) {
                root = root->left;
            }
            else
                root = root->right;
        }
        return closest;
    }

    void closestSearch(int target) {
        Node* close = closest(root, target);
        if (close == nullptr)
            cout << "Tree is empty\n";
        else
            visit(close);
    }
};
class AVLBook 
{
private:
    Node* root;

public:
    AVLBook()
    {
        root = nullptr;
    }
    int height(Node* root)
    {
        if (root == nullptr)
            return 0;
        return 1 + max(height(root->right), height(root->left));
    }
    int getBalancedFactor(Node* root)
    {
        if (root == nullptr)
            return 0;
        return height(root->left) - height(root->right);
    }
    Node* insertavl(Node* node, Book book)
    {
        if (node == nullptr)
        {
            Node* newNode = new Node;
            newNode->data = book;
            newNode->left = newNode->right = nullptr;
            return newNode;
        }

        if (book.id < node->data.id)
            node->left = insertavl(node->left, book);
        else if (book.id > node->data.id)
            node->right = insertavl(node->right, book);
        // update height here (if you store height)
        updateHeight(node);
        int bf = getBalancedFactor(node);

        // LEFT LEFT
        if (bf > 1 && book.id < node->left->data.id)
            return rightRotate(node);

        // RIGHT RIGHT
        if (bf < -1 && book.id > node->right->data.id)
            return leftRotate(node);

        // LEFT RIGHT
        if (bf > 1 && book.id > node->left->data.id)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RIGHT LEFT
        if (bf < -1 && book.id < node->right->data.id)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        // rotation
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x; // new root
    }
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        // rotation
        y->left = x;
        x->right = T2;

        // update heights
        updateHeight(x);
        updateHeight(y);

        return y; // new root
    }
    void updateHeight(Node* n)
    {
        n->height = 1 + max(height(n->left), height(n->right));
    }
    Node* deleteavl(Node* node,Book book)
    {
        if (node == nullptr) {
            return nullptr;
        }
        if (book.id < node->data.id)
            node->left = deleteavl(node->left, book);
        else if (book.id > node->data.id)
            node->right = deleteavl(node->right, book);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* child = (node->left != nullptr) ? node->left : node->right;
                if (child == nullptr) {
                    return nullptr;
                }
                else {
                    node = child;
                }
            }
            Node* successor = node->right;

            while (successor->left != nullptr)
            {
                successor = successor->left;
            }
            node->data= successor->data;
            node->right = deleteavl(node->right, successor->data);



        }

        updateHeight(node);
        int factor=getBalancedFactor(node);
        if (factor > 1 && book.id < node->left->data.id)
            return rightRotate(node);

        
        if (factor < -1 && book.id > node->right->data.id)
            return leftRotate(node);

        if (factor > 1 && book.id > node->left->data.id)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

       
        if (factor < -1 && book.id < node->right->data.id)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }


        return node;

    }
    void display()
    {
        display(root);
    }
    void display(Node* root)
    {
        if (root == nullptr)
            return;

        display(root->left);
        visit(root);
        display(root->right);
    }
    void visit(Node* root)
    {
        cout << "------------------------\n";
        cout << "ID     : " << root->data.id << "\n";
        cout << "Title  : " << root->data.title << "\n";
        cout << "Author : " << root->data.author << "\n";
        cout << "------------------------\n\n";
    }

    void printrange(Node* root, int minID, int maxID) {
        if (root == nullptr) return;

        if (root->data.id > minID) {
            printrange(root->left, minID, maxID);
        }

        if (root->data.id >= minID && root->data.id <= maxID) {
            visit(root);
        }

        if (root->data.id < maxID) {
            printrange(root->right, minID, maxID);
        }
    }

    void printINrange(int minID, int maxID) {
        printrange(root, minID, maxID);
    }

    Node* closest(Node* root, int target) {
        Node* closest = root;
        while (root != nullptr) {
            if (abs(root->data.id - target) < abs(closest->data.id - target)) {
                closest = root;
            }

            if (root->data.id == target)
                return root;
            if (root->data.id > target) {
                root = root->left;
            }
            else
                root = root->right;
        }
        return closest;
    }

    void closestSearch(int target) {
        Node* close = closest(root, target);
        if (close == nullptr)
            cout << "Tree is empty\n";
        else
            visit(close);
    }
    Node* search(int id)
    {

        Node* current = root;
        Node* parent = nullptr;
        while (current != 0)
        {
            parent = current;
            if (current->data.id == id)
            {
                return current;
            }
            else if (current->data.id > id)
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }
};

int main()
{
    BSTBook tree;

    // INSERT
    tree.insert({ 10, "C++ Basics", "Bjarne" });
    tree.insert({ 5, "DSA", "Mark" });
    tree.insert({ 20, "Algorithms", "CLRS" });
    tree.insert({ 3, "OOP", "Ali" });
    tree.insert({ 7, "Pointers", "John" });
    tree.insert({ 15, "Graphs", "Tarjan" });
    tree.insert({ 30, "AI", "Russell" });

    cout << "\n=== AFTER INSERT ===\n";
    tree.display();

    // SEARCH
    cout << "\n=== SEARCH 7 ===\n";
    Node* res = tree.search(7);
    if (res)
        cout << "Found: " << res->data.title << "\n";
    else
        cout << "Not found\n";

    // print in rane 
    cout << "\n=== print in range(5,20) ===\n";
    tree.printINrange(5, 20);

    //closestsearch
    cout << "\n=== closest book ID from 5 ===\n";
    tree.closestSearch(5);

    // DELETE LEAF
    cout << "\n=== DELETE 3 (leaf) ===\n";
    tree.deleteBook(3);
    tree.display();

    // DELETE ONE CHILD
    cout << "\n=== DELETE 5 (one child) ===\n";
    tree.deleteBook(5);
    tree.display();

    // DELETE TWO CHILDREN
    cout << "\n=== DELETE 10 (two children) ===\n";
    tree.deleteBook(10);
    tree.display();


    //closestsearch
    cout << "\n=== closest book ID from 5 ===\n";
    tree.closestSearch(5);


}
