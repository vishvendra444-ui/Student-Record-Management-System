#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    float marks;

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;

        cin.ignore();
        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);
    file << s.id << "|" << s.name << "|" << s.marks << endl;
    file.close();

    cout << "\nStudent added successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    Student s;
    string line;

    cout << "\n----- Student Records -----\n";

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos)
            continue;

        s.id = stoi(line.substr(0, first));
        s.name = line.substr(first + 1, second - first - 1);
        s.marks = stof(line.substr(second + 1));

        s.display();
    }

    file.close();
}

void searchStudent() {
    int searchId;
    cout << "Enter Student ID to search: ";
    cin >> searchId;

    ifstream file("students.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos)
            continue;

        int id = stoi(line.substr(0, first));

        if (id == searchId) {
            cout << "\nStudent Found!\n";
            cout << "ID: " << id << endl;
            cout << "Name: " << line.substr(first + 1, second - first - 1) << endl;
            cout << "Marks: " << line.substr(second + 1) << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n==============================";
        cout << "\n   STUDENT RECORD MANAGEMENT";
        cout << "\n==============================";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
