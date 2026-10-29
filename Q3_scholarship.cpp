/*
 * Name       : M.Ahmad Hassan
 * Reg No     : L1S26BSCS0026
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char path[100];

    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);

    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n = 0;
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 1;
    }

    ofstream outFile("scholarship.txt");

    char name[30], topName[30];
    double cgpa, total = 0, highest = -1;
    int count = 0, eligible = 0;

    while (count < n) {
        if (!inFile.getline(name, 30, ',')) {
            break;
        }

        if (!(inFile >> cgpa)) {
            break;
        }

        inFile.ignore(100, '\n');

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        total = total + cgpa;
        count++;

        if (cgpa >= 3.50) {
            outFile << name << "," << cgpa << endl;
            eligible++;
        }

        if (cgpa > highest) {
            highest = cgpa;
            strcpy_s(topName, name);
        }
    }

    inFile.close();
    outFile.close();

    if (count < n) {
        cout << "Warning: only " << count << " of "
            << n << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << total / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << highest << ")" << endl;

    return 0;
}