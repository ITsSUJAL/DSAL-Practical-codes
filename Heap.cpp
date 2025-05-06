#include <iostream>
using namespace std;

void min_heapify(int *a, int i, int n) {
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n) {
        if (j < n && a[j + 1] < a[j])
            j = j + 1;
        if (temp <= a[j])
            break;
        else {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
}

void max_heapify(int *a, int i, int n) {
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n) {
        if (j < n && a[j + 1] > a[j])
            j = j + 1;
        if (temp >= a[j])
            break;
        else {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
}

void build_minheap(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        min_heapify(a, i, n);
    }
}

void build_maxheap(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        max_heapify(a, i, n);
    }
}

int main() {
    int n, i, ch;
    cout << "\nEnter number of students: ";
    cin >> n;

    int a[21]; // 1-based indexing, allow up to 20 students safely
    for (i = 1; i <= n; i++) {
        cout << "Enter mark of student " << i << " : ";
        cin >> a[i];
    }

    do {
        cout << "\n1. MIN Heap\n2. MAX Heap\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                build_minheap(a, n);
                cout << "Min Heap:\n";
                for (i = 1; i <= n; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;
            case 2:
                build_maxheap(a, n);
                cout << "Max Heap:\n";
                for (i = 1; i <= n; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (ch != 3);

    return 0;
}
