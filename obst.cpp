#include <iostream>
using namespace std;

class obst {
    int a[10], r[10][10], n;
    float p[10], q[10], w[10][10], c[10][10];
public:
    void accept();
    void cons_obst();
    int find_min(int, int);
    void tree(int i, int j);
};

void obst::accept() {
    int i;
    cout << "\nHow many elements are there in the tree? : ";
    cin >> n;
    cout << "\nEnter " << n << " elements :";
    for (i = 1; i <= n; i++) cin >> a[i];
    
    cout << "\nEnter " << n << " successful probabilities : ";
    for (i = 1; i <= n; i++) cin >> p[i];
    
    cout << "\nEnter " << n + 1 << " failure probabilities : ";
    for (i = 0; i <= n; i++) cin >> q[i];
}

void obst::cons_obst() {
    int i, m, j, k;
    
    // Initialize weight and cost matrices when j-i=0 and j-i=1
    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        r[i][i] = c[i][i] = 0;
    }

    for (i = 1; i < n; i++) {
        w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        r[i][i + 1] = i + 1;
        c[i][i + 1] = w[i][i + 1];
    }
    
    w[n][n] = q[n];
    r[n][n] = c[n][n] = 0;

    // Calculate weight and cost matrices for different sizes of subtrees
    for (m = 2; m <= n; m++) {
        for (i = 0; i <= n - m; i++) {
            j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            k = find_min(i, j); // Find the minimum value in the range r[i..j-1] to r[i+1..j]
            c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
            r[i][j] = k;
        }
    }

    cout << "Root node is " << a[r[0][n]] << endl;
    cout << "\nLeft child of " << a[r[0][n]] << " is ";
    tree(0, r[0][n] - 1);
    cout << "\nRight child of " << a[r[0][n]] << " is ";
    tree(r[0][n], n);
}

int obst::find_min(int i, int j) {
    int min = 999, k, z;
    
    for (k = r[i][j - 1]; k <= r[i + 1][j]; k++) {
        cout << "\n i = " << i << " j = " << j << " k = " << k;
        if (min > c[i][k - 1] + c[k][j]) {
            min = c[i][k - 1] + c[k][j];
            z = k;
        }
    }
    return z;
}

void obst::tree(int i, int j) {
    if (r[i][j] == 0) {
        cout << " NULL\n";
        return;
    }
    cout << " :: " << a[r[i][j]];
    cout << "\nLeft child of " << a[r[i][j]] << " is ";
    tree(i, r[i][j] - 1);
    cout << "\nRight child of " << a[r[i][j]] << " is ";
    tree(r[i][j], j);
}

int main() {
    obst o;
    o.accept();
    o.cons_obst();
}
