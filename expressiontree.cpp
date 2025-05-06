#include <iostream>
#include <cstring>
#include <cctype>  // for isalpha
using namespace std;

struct node {
    char data;
    node *left;
    node *right;
};

class stack1 {
    node *data[30];
    int top;
public:
    stack1() { top = -1; }
    bool empty() { return top == -1; }
    void push(node *p) {
        if (top < 29)
            data[++top] = p;
    }
    node *pop() {
        if (!empty())
            return data[top--];
        return NULL;
    }
};

class tree {
public:
    node *top;
    tree() { top = NULL; }
    void expression(const char[]);
    void display(node *);  // Not used
    void non_rec_postorder(node *);
    void inorder(node *);
};

void tree::expression(const char prefix[]) {
    stack1 s;
    int len = strlen(prefix);

    for (int i = len - 1; i >= 0; i--) {
        node *newNode = new node;
        newNode->left = newNode->right = NULL;

        if (isalpha(prefix[i])) {
            newNode->data = prefix[i];
            s.push(newNode);
        } else if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/') {
            newNode->data = prefix[i];
            node *t1 = s.pop();
            node *t2 = s.pop();
            newNode->left = t1;
            newNode->right = t2;
            s.push(newNode);
        }
    }
    top = s.pop();  // Root of the expression tree
}

void tree::non_rec_postorder(node *top) {
    if (top == NULL) return;

    stack1 s1, s2;
    s1.push(top);

    cout << "\nPostorder Traversal: ";
    while (!s1.empty()) {
        node *temp = s1.pop();
        s2.push(temp);

        if (temp->left)
            s1.push(temp->left);
        if (temp->right)
            s1.push(temp->right);
    }

    while (!s2.empty()) {
        node *temp = s2.pop();
        cout << temp->data << " ";
    }
}

void tree::inorder(node *top) {
    if (top == NULL) return;

    stack1 s;
    node *T = top;

    cout << "\nInorder Traversal: ";
    while (T != NULL || !s.empty()) {
        while (T != NULL) {
            s.push(T);
            T = T->left;
        }
        T = s.pop();
        cout << T->data << " ";
        T = T->right;
    }
}

int main() {
    char expr[20];
    tree t;

    cout << "Enter prefix Expression: ";
    cin >> expr;

    t.expression(expr);
    t.non_rec_postorder(t.top);
    t.inorder(t.top);

    return 0;
}
