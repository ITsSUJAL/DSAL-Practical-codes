#include<iostream>
#include<cstring>
using namespace std;

class node {
public:
    char keyword[20];
    char meaning[20];
    node *left, *right;
    int ht;

    node() {
        strcpy(keyword, "");
        strcpy(meaning, "");
        left = right = NULL;
        ht = 0;
    }
};

class tree {
private:
    node *root;

public:
    tree() {
        root = NULL;
    }

    int height(node *T) {
        if (T == NULL) return -1;
        return T->ht;
    }

    int BF(node *T) {
        return height(T->left) - height(T->right);
    }

    node* Rotate_Left(node *T) {
        node *temp = T->right;
        T->right = temp->left;
        temp->left = T;

        T->ht = max(height(T->left), height(T->right)) + 1;
        temp->ht = max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }

    node* Rotate_Right(node *T) {
        node *temp = T->left;
        T->left = temp->right;
        temp->right = T;

        T->ht = max(height(T->left), height(T->right)) + 1;
        temp->ht = max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }

    node* insert(node *T, char word[20], char mean[20]) {
        if (T == NULL) {
            T = new node();
            strcpy(T->keyword, word);
            strcpy(T->meaning, mean);
            T->ht = 0;
            return T;
        }

        if (strcmp(word, T->keyword) < 0) {
            T->left = insert(T->left, word, mean);
            if (BF(T) == 2) {
                if (strcmp(word, T->left->keyword) < 0)
                    T = Rotate_Right(T);
                else {
                    T->left = Rotate_Left(T->left);
                    T = Rotate_Right(T);
                }
            }
        } else if (strcmp(word, T->keyword) > 0) {
            T->right = insert(T->right, word, mean);
            if (BF(T) == -2) {
                if (strcmp(word, T->right->keyword) > 0)
                    T = Rotate_Left(T);
                else {
                    T->right = Rotate_Right(T->right);
                    T = Rotate_Left(T);
                }
            }
        } else {
            cout << "\nKeyword already exists. Skipping...\n";
        }

        T->ht = max(height(T->left), height(T->right)) + 1;
        return T;
    }

    void insert1(char key[20], char mean[20]) {
        root = insert(root, key, mean);
    }

    void inorder(node *T) {
        if (T != NULL) {
            inorder(T->left);
            cout << T->keyword << " : " << T->meaning << "\n";
            inorder(T->right);
        }
    }

    void preorder(node *T) {
        if (T != NULL) {
            cout << T->keyword << " : " << T->meaning << "\n";
            preorder(T->left);
            preorder(T->right);
        }
    }

    void postorder(node *T) {
        if (T != NULL) {
            postorder(T->left);
            postorder(T->right);
            cout << T->keyword << " : " << T->meaning << "\n";
        }
    }

    void search1(node *T, char data[20]) {
        int count = 0;
        while (T != NULL) {
            count++;
            if (strcmp(T->keyword, data) == 0) {
                cout << "Found " << data << " with meaning: " << T->meaning << "\n";
                cout << "Comparisons made: " << count << "\n";
                return;
            } else if (strcmp(data, T->keyword) < 0)
                T = T->left;
            else
                T = T->right;
        }
        cout << "Word not found.\n";
    }

    void display() {
        int ch;
        do {
            cout << "\nMenu:\n1. Preorder\n2. Inorder\n3. Postorder\n4. Search\n0. Exit\nChoice: ";
            cin >> ch;
            switch (ch) {
                case 1:
                    preorder(root);
                    break;
                case 2:
                    inorder(root);
                    break;
                case 3:
                    postorder(root);
                    break;
                case 4: {
                    char word[20];
                    cout << "Enter word to search: ";
                    cin >> word;
                    search1(root, word);
                    break;
                }
                case 0:
                    break;
                default:
                    cout << "Invalid choice\n";
            }
        } while (ch != 0);
    }
};

int main() {
    tree b;
    char key[20], mean[20];
    int ans;

    do {
        cout << "Enter keyword and meaning: ";
        cin >> key >> mean;
        b.insert1(key, mean);
        cout << "Continue? (1/0): ";
        cin >> ans;
    } while (ans == 1);

    b.display();
    return 0;
}
