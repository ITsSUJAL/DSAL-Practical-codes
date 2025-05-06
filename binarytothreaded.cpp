#include <iostream>
#include <cstring>
using namespace std;

struct node {
    char k[20];
    char m[20];
    node *left;
    node *right;
};

class dict {
public:
    node *root;

    dict() {
        root = NULL;
    }

    void create();
    void disp(node *);
    void insert(node *, node *);
    int search(node *, char []);
    int update(node *, char []);
    node* del(node *, char []);
    node* min(node *);
};

void dict::create() {
    node *temp;
    int ch;
    do {
        temp = new node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;
        temp->left = temp->right = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp);
        }

        cout << "\nDo you want to add more? (1 = Yes / 0 = No): ";
        cin >> ch;
    } while (ch == 1);
}

void dict::insert(node *root, node *temp) {
    if (strcmp(temp->k, root->k) < 0) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    } else {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

void dict::disp(node *root) {
    if (root != NULL) {
        disp(root->left);
        cout << "\nKeyword: " << root->k << "\tMeaning: " << root->m;
        disp(root->right);
    }
}

int dict::search(node *root, char k[20]) {
    int c = 0;
    while (root != NULL) {
        c++;
        if (strcmp(k, root->k) == 0) {
            cout << "\nNumber of Comparisons: " << c;
            return 1;
        } else if (strcmp(k, root->k) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return -1;
}

int dict::update(node *root, char k[20]) {
    while (root != NULL) {
        if (strcmp(k, root->k) == 0) {
            cout << "\nEnter New Meaning for Keyword \"" << root->k << "\": ";
            cin >> root->m;
            return 1;
        } else if (strcmp(k, root->k) < 0)
            root = root->left;
        else
            root = root->right;
    }
    return -1;
}

node* dict::min(node *q) {
    while (q->left != NULL) {
        q = q->left;
    }
    return q;
}

node* dict::del(node *root, char k[20]) {
    if (root == NULL) {
        cout << "\nElement Not Found";
        return NULL;
    }

    if (strcmp(k, root->k) < 0) {
        root->left = del(root->left, k);
    } else if (strcmp(k, root->k) > 0) {
        root->right = del(root->right, k);
    } else {
        // Node found
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node *temp = root->left;
            delete root;
            return temp;
        } else {
            node *temp = min(root->right);
            strcpy(root->k, temp->k);
            strcpy(root->m, temp->m);
            root->right = del(root->right, temp->k);
        }
    }
    return root;
}

int main() {
    int ch;
    dict d;

    do {
        cout << "\n\nMenu:\n1. Create\n2. Display\n3. Search\n4. Update\n5. Delete\nEnter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                d.create();
                break;
            case 2:
                if (d.root == NULL) {
                    cout << "\nNo Keywords Added.";
                } else {
                    d.disp(d.root);
                }
                break;
            case 3:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty.";
                } else {
                    char key[20];
                    cout << "\nEnter Keyword to Search: ";
                    cin >> key;
                    if (d.search(d.root, key))
                        cout << "\nKeyword Found.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 4:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty.";
                } else {
                    char key[20];
                    cout << "\nEnter Keyword to Update: ";
                    cin >> key;
                    if (d.update(d.root, key))
                        cout << "\nMeaning Updated.";
                    else
                        cout << "\nKeyword Not Found.";
                }
                break;
            case 5:
                if (d.root == NULL) {
                    cout << "\nDictionary is Empty.";
                } else {
                    char key[20];
                    cout << "\nEnter Keyword to Delete: ";
                    cin >> key;
                    d.root = d.del(d.root, key);
                }
                break;
            default:
                cout << "\nInvalid Choice.";
                break;
        }
    } while (ch >= 1 && ch <= 5);

    return 0;
}
