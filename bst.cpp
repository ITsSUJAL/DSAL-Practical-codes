#include <iostream>
using namespace std;

struct node {
    int data;
    node *L;
    node *R;
};

class bst {
    node *root;
    int count;

public:
    bst() {
        root = NULL;
        count = 0;
    }

    void create();
    void insert(node* &root, node* temp);
    void disin(node* root);
    void dispre(node* root);
    void dispost(node* root);
    void search(node* root);
    int height(node* root);
    void mirror(node* root);
    void min(node* root);
    void run();  // main program logic

    node* getRoot() { return root; }  // getter for root
};

void bst::create() {
    char ans;
    do {
        node* temp = new node;
        cout << "Enter the data: ";
        cin >> temp->data;
        temp->L = temp->R = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp);
        }

        cout << "Do you want to insert more values? (y/n): ";
        cin >> ans;
        count++;
        cout << endl;
    } while (ans == 'y');

    cout << "Total number of nodes: " << count << endl;
}

void bst::insert(node* &root, node* temp) {
    if (temp->data > root->data) {
        if (root->R == NULL)
            root->R = temp;
        else
            insert(root->R, temp);
    } else {
        if (root->L == NULL)
            root->L = temp;
        else
            insert(root->L, temp);
    }
}

void bst::disin(node* root) {
    if (root != NULL) {
        disin(root->L);
        cout << root->data << "\t";
        disin(root->R);
    }
}

void bst::dispre(node* root) {
    if (root != NULL) {
        cout << root->data << "\t";
        dispre(root->L);
        dispre(root->R);
    }
}

void bst::dispost(node* root) {
    if (root != NULL) {
        dispost(root->L);
        dispost(root->R);
        cout << root->data << "\t";
    }
}

void bst::search(node* root) {
    int key;
    cout << "Enter the key to search: ";
    cin >> key;
    node* temp = root;
    while (temp != NULL) {
        if (key == temp->data) {
            cout << "KEY FOUND\n";
            return;
        }
        if (key > temp->data)
            temp = temp->R;
        else
            temp = temp->L;
    }
    cout << "KEY NOT FOUND\n";
}

int bst::height(node* root) {
    if (root == NULL) return 0;
    int hl = height(root->L);
    int hr = height(root->R);
    return max(hl, hr) + 1;
}

void bst::min(node* root) {
    if (root == NULL) {
        cout << "Tree is empty.\n";
        return;
    }
    node* temp = root;
    while (temp->L != NULL)
        temp = temp->L;
    cout << temp->data << endl;
}

void bst::mirror(node* root) {
    if (root != NULL) {
        mirror(root->L);
        mirror(root->R);
        node* temp = root->L;
        root->L = root->R;
        root->R = temp;
    }
}

void bst::run() {
    int ch;
    char ans;
    do {
        cout << "\nMenu:\n";
        cout << "1) Insert new node\n";
        cout << "2) Number of nodes in longest path (Height)\n";
        cout << "3) Minimum value\n";
        cout << "4) Mirror tree\n";
        cout << "5) Search\n";
        cout << "6) Inorder\n";
        cout << "7) Preorder\n";
        cout << "8) Postorder\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: create(); break;
            case 2:
                cout << "Height of the tree: " << height(root) << endl;
                break;
            case 3:
                cout << "Minimum element: ";
                min(root);
                break;
            case 4:
                mirror(root);
                cout << "Mirrored tree (Inorder): ";
                disin(root);
                break;
            case 5: search(root); break;
            case 6:
                cout << "*INORDER*\n";
                disin(root);
                break;
            case 7:
                cout << "*PREORDER*\n";
                dispre(root);
                break;
            case 8:
                cout << "*POSTORDER*\n";
                dispost(root);
                break;
            default:
                cout << "Invalid choice.\n";
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ans;
    } while (ans == 'y');
}

int main() {
    bst t;
    t.run();
    return 0;
}
