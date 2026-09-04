#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

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
        cout << "\nID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks << endl;
    }
};

// Add Student
void addStudent() {
    Student s;

    s.input();

    ofstream file("students.txt", ios::app);

    if (!file) {
        cout << "\nError opening file!\n";
        return;
    }

    file << s.id << "|" << s.name << "|" << s.marks << endl;

    file.close();

    cout << "\nStudent added successfully!\n";
}

// Display All Students
void displayStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n==============================";
    cout << "\n      STUDENT RECORDS";
    cout << "\n==============================\n";

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos) {
            continue;
        }

        int id = stoi(line.substr(0, first));
        string name = line.substr(first + 1, second - first - 1);
        float marks = stof(line.substr(second + 1));

        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;

        cout << "------------------------------";

        found = true;
    }

    file.close();

    if (!found) {
        cout << "\nNo student records found.\n";
    }
}

// Search Student
void searchStudent() {
    int searchId;

    cout << "Enter Student ID to search: ";
    cin >> searchId;

    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos) {
            continue;
        }

        int id = stoi(line.substr(0, first));

        if (id == searchId) {
            string name = line.substr(first + 1, second - first - 1);
            string marks = line.substr(second + 1);

            cout << "\nStudent Found!\n";
            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Marks: " << marks << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "\nStudent not found.\n";
    }
}

// Update Student
void updateStudent() {
    int searchId;

    cout << "Enter Student ID to update: ";
    cin >> searchId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos) {
            continue;
        }

        int id = stoi(line.substr(0, first));

        if (id == searchId) {
            Student s;

            s.id = id;

            cin.ignore();

            cout << "Enter New Student Name: ";
            getline(cin, s.name);

            cout << "Enter New Marks: ";
            cin >> s.marks;

            temp << s.id << "|" << s.name << "|" << s.marks << endl;

            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nStudent updated successfully!\n";
    }
    else {
        cout << "\nStudent not found.\n";
    }
}

// Delete Student
void deleteStudent() {
    int deleteId;

    cout << "Enter Student ID to delete: ";
    cin >> deleteId;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);

        if (first == string::npos || second == string::npos) {
            continue;
        }

        int id = stoi(line.substr(0, first));

        if (id == deleteId) {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nStudent deleted successfully!\n";
    }
    else {
        cout << "\nStudent not found.\n";
    }
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n\n==============================";
        cout << "\n   STUDENT RECORD MANAGEMENT";
        cout << "\n==============================";

        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

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
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
