#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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

    Node* search(int id, int& steps)
    {
        steps = 0;
        Node* current = root;
        while (current != nullptr)
        {
            steps++;
            if (current->data.id == id)   return current;
            else if (current->data.id > id) current = current->left;
            else                            current = current->right;
        }
        return nullptr;
    }

    int getHeight()
    {
        return heightHelper(root);
    }
    int heightHelper(Node* n)
    {
        if (n == nullptr) return 0;
        return 1 + max(heightHelper(n->left), heightHelper(n->right));
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

    int getHeight()
    {
        return height(root);
    }

    Node* search(int id, int& steps)
    {
        steps = 0;
        Node* current = root;
        while (current != nullptr)
        {
            steps++;
            if (current->data.id == id)    return current;
            else if (current->data.id > id) current = current->left;
            else                            current = current->right;
        }
        return nullptr;
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

void runComparison(const string& caseLabel, vector<Book>& books, vector<int>& searchIDs)
{
    cout << "\n" << caseLabel << "\n";

    BSTBook bst;
    AVLBook avl;

    for (auto& b : books)
    {
        bst.insert(b);
        avl.insert(b);
    }

    cout << "Books inserted : " << books.size() << "\n";
    cout << "BST Height     : " << bst.getHeight() << "\n";
    cout << "AVL Height     : " << avl.getHeight() << "\n\n";

    cout << left << setw(8) << "ID"
        << setw(14) << "BST Steps"
        << "AVL Steps\n";
    cout << string(36, '-') << "\n";

    int totalBST = 0, totalAVL = 0;
    for (int id : searchIDs)
    {
        int bstSteps = 0, avlSteps = 0;
        bst.search(id, bstSteps);
        avl.search(id, avlSteps);
        totalBST += bstSteps;
        totalAVL += avlSteps;

        cout << left << setw(8) << id
            << setw(14) << bstSteps
            << avlSteps << "\n";
    }
    cout << string(36, '-') << "\n";
    cout << left << setw(8) << "TOTAL"
        << setw(14) << totalBST
        << totalAVL << "\n";
}

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
	int steps = 0;
    Node* res = tree.search(7 , steps);
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

    vector<Book> randomBooks = {
    {42,"C++ Basics","Bjarne"},   {17,"DSA","Mark"},
    {88,"Algorithms","CLRS"},     {5,"OOP","Ali"},
    {63,"Pointers","John"},       {31,"Graphs","Tarjan"},
    {74,"AI","Russell"},          {19,"Clean Code","Martin"},
    {56,"Design Patterns","GoF"}, {92,"OS Concepts","Silberschatz"},
    {11,"Compilers","Aho"},       {47,"Networks","Tanenbaum"},
    {83,"Databases","Ramakrishnan"},{28,"Probability","Feller"},
    {65,"Linear Algebra","Strang"},{3,"Calculus","Stewart"},
    {70,"Discrete Math","Rosen"}, {35,"Machine Learning","Mitchell"},
    {58,"Deep Learning","Goodfellow"},{96,"Statistics","Freedman"},
    {22,"Cryptography","Schneier"},{79,"Computer Vision","Szeliski"},
    {44,"NLP","Jurafsky"},        {13,"Robotics","Siciliano"},
    {51,"Quantum Computing","Nielsen"}
    };
    vector<int> randomSearch = { 42, 5, 96, 28, 11, 65, 51, 79 };
    runComparison("Random IDs", randomBooks, randomSearch);

    vector<Book> sortedBooks = {
        {1,"C++ Basics","Bjarne"},    {2,"DSA","Mark"},
        {3,"Algorithms","CLRS"},      {4,"OOP","Ali"},
        {5,"Pointers","John"},        {6,"Graphs","Tarjan"},
        {7,"AI","Russell"},           {8,"Clean Code","Martin"},
        {9,"Design Patterns","GoF"},  {10,"OS Concepts","Silberschatz"},
        {11,"Compilers","Aho"},       {12,"Networks","Tanenbaum"},
        {13,"Databases","Ramakrishnan"},{14,"Probability","Feller"},
        {15,"Linear Algebra","Strang"},{16,"Calculus","Stewart"},
        {17,"Discrete Math","Rosen"}, {18,"Machine Learning","Mitchell"},
        {19,"Deep Learning","Goodfellow"},{20,"Statistics","Freedman"},
        {21,"Cryptography","Schneier"},{22,"Computer Vision","Szeliski"},
        {23,"NLP","Jurafsky"},        {24,"Robotics","Siciliano"},
        {25,"Quantum Computing","Nielsen"}
    };
    vector<int> sortedSearch = { 1, 5, 10, 15, 20, 25, 13, 22 };
    runComparison("Sorted IDs", sortedBooks, sortedSearch);


}
