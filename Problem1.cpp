#include <bits/stdc++.h>
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
    Node *left;
    Node *right;
};

class BSTBook
{
private:
    Node *root;

public:
    BSTBook()
    {
        root = nullptr;
    }

    void insert(Book book)
    {
        Node *newNode = new Node;
        newNode->data = book;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (root == nullptr) // first time
        {
            root = newNode;
            return;
        }

        Node *current = root;
        Node *parent = nullptr;
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

    Node *search(int id)
    {

        Node *current = root;
        Node *parent = nullptr;
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
        Node *current = root;
        Node *parent = nullptr;

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
            Node *successorParent = current;
            Node *successor = current->right;

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
        Node *child = (current->left != nullptr) ? current->left : current->right;

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
    void display(Node *root)
    {
        if (root == nullptr)
            return;

        display(root->left);
        visit(root);
        display(root->right);
    }
    void visit(Node *root)
    {
        cout << "------------------------\n";
        cout << "ID     : " << root->data.id << "\n";
        cout << "Title  : " << root->data.title << "\n";
        cout << "Author : " << root->data.author << "\n";
        cout << "------------------------\n\n";
    }
};
class AVLBook
{
private:
    Node *root;
    AVLBook()
    {
        root = nullptr;
    }

public:
    



Node *search(int id)
    {

        Node *current = root;
        Node *parent = nullptr;
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
    tree.insert({10, "C++ Basics", "Bjarne"});
    tree.insert({5, "DSA", "Mark"});
    tree.insert({20, "Algorithms", "CLRS"});
    tree.insert({3, "OOP", "Ali"});
    tree.insert({7, "Pointers", "John"});
    tree.insert({15, "Graphs", "Tarjan"});
    tree.insert({30, "AI", "Russell"});

    cout << "\n=== AFTER INSERT ===\n";
    tree.display();

    // SEARCH
    cout << "\n=== SEARCH 7 ===\n";
    Node *res = tree.search(7);
    if (res)
        cout << "Found: " << res->data.title << "\n";
    else
        cout << "Not found\n";

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
}