/*
 * Name       : M.Ahmad Hassan
 * Reg No     : L1S26BSCS0026
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");

    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;

    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n');

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    ofstream outFile("receipts.txt");
    outFile << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], longestPlate[15], type, colon;
    int inHour, inMinute, outHour, outMinute;
    int count = 0, cars = 0, bikes = 0;
    int total = 0, longest = -1;

    while (count < 30 &&
        inFile >> plate >> type
        >> inHour >> colon >> inMinute
        >> outHour >> colon >> outMinute) {

        int inTime = inHour * 60 + inMinute;
        int outTime = outHour * 60 + outMinute;
        int minutes = outTime - inTime;

        int hoursCharged = (minutes + 59) / 60;

        if (hoursCharged == 0) {
            hoursCharged = 1;
        }

        int fee;

        cout << plate << " ";

        if (type == 'C') {
            fee = hoursCharged * 100;
            cars++;
            cout << "Car ";
        }
        else {
            fee = hoursCharged * 40;
            bikes++;
            cout << "Bike ";
        }

        cout << minutes / 60 << " h "
            << minutes % 60 << " min Fee: " << fee << endl;

        outFile << plate << " " << fee << endl;

        count++;
        total = total + fee;

        if (minutes > longest) {
            longest = minutes;
            strcpy_s(longestPlate, plate);
        }
    }

    inFile.close();
    outFile.close();

    if (count == 0) {
        cout << "No vehicles found!" << endl;
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << longestPlate << " ("
        << longest / 60 << " h "
        << longest % 60 << " min)" << endl;

    return 0;
}