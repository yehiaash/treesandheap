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
    int height;
};

class BSTBook
{
private:
    Node *root;

public:
    Node *getRoot() { return root; }
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
        int greater = -1;
        int min = root->data.id;
       current = root;
       parent = nullptr;
        while (current != 0)
        {
            parent = current;

            if (current->data.id > id)
            {
                if (greater == -1 || current->data.id < greater)
                    greater = current->data.id;
                current = current->left;
            }
            else
            {
                if (current->data.id > min)
                    min = current->data.id;
                current = current->right;
            }
        }
        cout << "closest id is: " << greater << " " << min;

        return nullptr;
    }

    void search(Node *root, int start, int end) // search in range
    {
        if (root == nullptr)
            return;
        if (root->data.id > start)
            search(root->left, start, end);
        if (root->data.id >= start && root->data.id <= end)
        {
            cout << "------------------------\n";
            cout << "ID     : " << root->data.id << "\n";
            cout << "Title  : " << root->data.title << "\n";
            cout << "Author : " << root->data.author << "\n";
            cout << "------------------------\n\n";
        }
        if (root->data.id < end)
            search(root->right, start, end);
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



int main()
{

}