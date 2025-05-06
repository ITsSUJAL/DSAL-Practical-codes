#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct stud {
    int roll;
    char name[10];
    char div;
    char add[10];
};

class student {
    stud rec;
public:
    void create();
    void display();
    int search();
    void Delete();
};

void student::create() {
    char ans;
    ofstream fout("stud.dat", ios::out | ios::binary);
    do {
        cout << "\n\tEnter Roll No of Student : ";
        cin >> rec.roll;
        cout << "\n\tEnter Name of Student : ";
        cin >> rec.name;
        cout << "\n\tEnter Division of Student : ";
        cin >> rec.div;
        cout << "\n\tEnter Address of Student : ";
        cin >> rec.add;

        fout.write((char *)&rec, sizeof(rec));
        cout << "\n\tDo You Want to Add More Records (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
    fout.close();
}

void student::display() {
    ifstream fin("stud.dat", ios::in | ios::binary);
    cout << "\n\tThe Contents of File are:\n";
    cout << "\n\tRoll\tName\tDiv\tAddress";
    while (fin.read((char *)&rec, sizeof(rec))) {
        if (rec.roll != -1) {
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
        }
    }
    fin.close();
}

int student::search() {
    int r, i = 0;
    ifstream fin("stud.dat", ios::in | ios::binary);
    cout << "\n\tEnter Roll No to Search: ";
    cin >> r;

    while (fin.read((char *)&rec, sizeof(rec))) {
        if (rec.roll == r) {
            cout << "\n\tRecord Found...\n";
            cout << "\n\tRoll\tName\tDiv\tAddress";
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
            fin.close();
            return i;
        }
        i++;
    }

    fin.close();
    return -1; // Not found
}

void student::Delete() {
    int pos = search();
    if (pos == -1) {
        cout << "\n\tRecord Not Found.\n";
        return;
    }

    fstream f("stud.dat", ios::in | ios::out | ios::binary);
    int offset = pos * sizeof(stud);
    f.seekp(offset, ios::beg);

    // Soft delete: mark record as deleted
    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    f.write((char *)&rec, sizeof(rec));
    f.close();
    cout << "\n\tRecord Deleted Successfully.";
}

int main() {
    student obj;
    int ch;
    char ans;
    do {
        cout << "\n\t Student Information System";
        cout << "\n\t1. Create\n\t2. Display\n\t3. Delete\n\t4. Search\n\t5. Exit";
        cout << "\n\t..... Enter Your Choice: ";
        cin >> ch;
        switch (ch) {
            case 1:
                obj.create();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                obj.Delete();
                break;
            case 4:
                if (obj.search() == -1)
                    cout << "\n\tRecord Not Found...\n";
                break;
            case 5:
                cout << "\n\tExiting...\n";
                return 0;
            default:
                cout << "\n\tInvalid Choice!";
        }
        cout << "\n\t..... Do You Want to Continue in Main Menu (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
