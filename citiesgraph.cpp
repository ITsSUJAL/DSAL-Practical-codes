#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;

struct node {
    string vertex;
    int time;
    node* next;
};

class adjmatlist {
    int m[20][20], n;
    string v[20];
    node* head[20];

public:
    adjmatlist() {
        for (int i = 0; i < 20; i++) {
            head[i] = NULL;
            for (int j = 0; j < 20; j++)
                m[i][j] = 0;
        }
    }

    void getgraph();
    void adjlist();
    void displaym();
    void displaya();
};

void adjmatlist::getgraph() {
    char ch;
    cout << "\nEnter number of cities (max 20): ";
    cin >> n;

    cout << "Enter names of cities:\n";
    for (int i = 0; i < n; i++) {
        cout << "City " << (i + 1) << ": ";
        cin >> v[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\nIs there a path from " << v[i] << " to " << v[j] << "? (y/n): ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                cout << "Enter time in minutes from " << v[i] << " to " << v[j] << ": ";
                cin >> m[i][j];
            } else {
                m[i][j] = 0;
            }
        }
    }

    adjlist();  // Call adjacency list builder after input
}

void adjmatlist::adjlist() {
    for (int i = 0; i < n; i++) {
        // Create head node
        node* p = new node;
        p->vertex = v[i];
        p->time = 0; // No time needed for the node itself
        p->next = NULL;
        head[i] = p;

        node* last = p;
        for (int j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                node* q = new node;
                q->vertex = v[j];
                q->time = m[i][j];
                q->next = NULL;

                last->next = q;
                last = q;
            }
        }
    }
}

void adjmatlist::displaym() {
    cout << "\n\nAdjacency Matrix:\n\t";
    for (int j = 0; j < n; j++) {
        cout << v[j] << "\t";
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << v[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << "\t";
        }
        cout << "\n";
    }
}

void adjmatlist::displaya() {
    cout << "\n\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        node* temp = head[i];
        while (temp != NULL) {
            if (temp->time > 0)
                cout << " --> ";
            cout << temp->vertex;
            temp = temp->next;
        }
        cout << "\n";
    }

    cout << "\nPaths and time required:\n";
    for (int i = 0; i < n; i++) {
        node* temp = head[i]->next;  // Skip the head itself
        while (temp != NULL) {
            cout << head[i]->vertex << " --> " << temp->vertex
                 << " [Time: " << temp->time << " min]\n";
            temp = temp->next;
        }
    }
}

int main() {
    int choice;
    adjmatlist a;

    while (true) {
        cout << "\n\nMenu:";
        cout << "\n1. Enter Graph";
        cout << "\n2. Display Adjacency Matrix";
        cout << "\n3. Display Adjacency List";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: a.getgraph(); break;
            case 2: a.displaym(); break;
            case 3: a.displaya(); break;
            case 4: exit(0);
            default: cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
