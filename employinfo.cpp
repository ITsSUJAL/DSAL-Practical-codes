#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class EMP_CLASS {
    typedef struct EMPLOYEE {
        int emp_id;
        char name[10];
        int salary;
    } Rec;

    typedef struct INDEX {
        int emp_id;
        int position;
    } Ind_Rec;

    Rec Records;
    Ind_Rec Ind_Records;

public:
    EMP_CLASS();
    void Create();
    void Display();
    void Update();
    void Delete();
    void Append();
    void Search();
};

EMP_CLASS::EMP_CLASS() {
    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = 0;
    Ind_Records.emp_id = -1;
    Ind_Records.position = -1;
}

void EMP_CLASS::Create() {
    int i = 0;
    char ch = 'y';
    ofstream seqfile("EMP.DAT", ios::out | ios::binary);
    ofstream indexfile("IND.DAT", ios::out | ios::binary);

    do {
        cout << "\nEnter Emp_ID: ";
        cin >> Records.emp_id;
        cout << "Enter Name: ";
        cin >> Records.name;
        cout << "Enter Salary: ";
        cin >> Records.salary;

        seqfile.write((char*)&Records, sizeof(Records));
        Ind_Records.emp_id = Records.emp_id;
        Ind_Records.position = i;
        indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));
        i++;

        cout << "Do you want to add more records? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Display() {
    fstream seqfile("EMP.DAT", ios::in | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        int pos = Ind_Records.position * sizeof(Records);
        seqfile.seekg(pos, ios::beg);
        seqfile.read((char*)&Records, sizeof(Records));

        if (Records.emp_id != -1) {
            cout << "\nName: " << Records.name;
            cout << "\nEmp_ID: " << Records.emp_id;
            cout << "\nSalary: " << Records.salary << "\n";
        }
    }

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Update() {
    int pos = -1, id;
    char New_name[10];
    int New_salary;

    cout << "\nEnter the Emp_ID for updating: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1) return;

    cout << "\nEnter new Name: ";
    cin >> New_name;
    cout << "Enter new Salary: ";
    cin >> New_salary;

    int offset = pos * sizeof(Records);
    seqfile.seekp(offset, ios::beg);
    strcpy(Records.name, New_name);
    Records.emp_id = id;
    Records.salary = New_salary;
    seqfile.write((char*)&Records, sizeof(Records));

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Delete() {
    int id, pos = -1;

    cout << "\nEnter the Emp_ID to delete: ";
    cin >> id;

    fstream seqfile("EMP.DAT", ios::in | ios::out | ios::binary);
    fstream indexfile("IND.DAT", ios::in | ios::out | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    if (pos == -1) return;

    int offset = pos * sizeof(Records);
    seqfile.seekp(offset, ios::beg);
    strcpy(Records.name, "");
    Records.emp_id = -1;
    Records.salary = -1;
    seqfile.write((char*)&Records, sizeof(Records));

    offset = pos * sizeof(Ind_Records);
    indexfile.seekp(offset, ios::beg);
    Ind_Records.emp_id = -1;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Append() {
    fstream indexfile("IND.DAT", ios::in | ios::binary);
    int pos;

    indexfile.seekg(0, ios::end);
    pos = indexfile.tellg() / sizeof(Ind_Records);
    indexfile.close();

    indexfile.open("IND.DAT", ios::app | ios::binary);
    fstream seqfile("EMP.DAT", ios::app | ios::binary);

    cout << "\nEnter Name: ";
    cin >> Records.name;
    cout << "Enter Emp_ID: ";
    cin >> Records.emp_id;
    cout << "Enter Salary: ";
    cin >> Records.salary;

    seqfile.write((char*)&Records, sizeof(Records));
    Ind_Records.emp_id = Records.emp_id;
    Ind_Records.position = pos;
    indexfile.write((char*)&Ind_Records, sizeof(Ind_Records));

    seqfile.close();
    indexfile.close();
}

void EMP_CLASS::Search() {
    int id, pos = -1;

    cout << "\nEnter Emp_ID to search: ";
    cin >> id;

    fstream indexfile("IND.DAT", ios::in | ios::binary);

    while (indexfile.read((char*)&Ind_Records, sizeof(Ind_Records))) {
        if (id == Ind_Records.emp_id) {
            pos = Ind_Records.position;
            break;
        }
    }

    indexfile.close();
    if (pos == -1) return;

    int offset = pos * sizeof(Records);
    fstream seqfile("EMP.DAT", ios::in | ios::binary);
    seqfile.seekg(offset, ios::beg);
    seqfile.read((char*)&Records, sizeof(Records));

    if (Records.emp_id != -1) {
        cout << "\nName: " << Records.name;
        cout << "\nEmp_ID: " << Records.emp_id;
        cout << "\nSalary: " << Records.salary << "\n";
    }

    seqfile.close();
}

int main() {
    EMP_CLASS List;
    int choice;

    do {
        cout << "\nMain Menu\n";
        cout << "1. Create\n";
        cout << "2. Display\n";
        cout << "3. Update\n";
        cout << "4. Delete\n";
        cout << "5. Append\n";
        cout << "6. Search\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: List.Create(); break;
            case 2: List.Display(); break;
            case 3: List.Update(); break;
            case 4: List.Delete(); break;
            case 5: List.Append(); break;
            case 6: List.Search(); break;
            case 7: exit(0);
        }
    } while (choice != 7);

    return 0;
}
