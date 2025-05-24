#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include<fstream>
using namespace std;

class Farmer {
    float rent_per_sack;
    float total_rent;
     
    int qty, id;
    char name[100], fname[100], addr[200];
    string contact;

public:
static int cnt;
    void input() {
        cout << "Enter the name: ";
        cin.ignore();
        cin.getline(name, 100);

        cout << "Enter the father's name: ";
        cin.getline(fname, 100);

        cout << "Enter the farmer's address: ";
        cin.getline(addr, 200);

        cout << "Enter the quantity: ";
        cin >> qty;

        bool valid = false;
        while (!valid) {
            cout << "Enter the contact number: ";
            cin >> contact;
            if (contact.length() == 10 && all_of(contact.begin(), contact.end(), ::isdigit)) {
                valid = true;
            } else {
                cout << "Invalid contact number. Please enter exactly 10 digits.\n";
            }
        }

        id = ++cnt;
        cout << "Enter rent per sack of potato: ";
        cin >> rent_per_sack;
        total_rent = rent_per_sack * qty;

    }

    void display() {
        cout << left
             << setw(5) << id
             << setw(20) << name
             << setw(20) << fname
             << setw(50) << addr
             << setw(10) << qty
             << setw(15) << contact 
              << setw(15) << fixed << setprecision(2) << total_rent<<endl;
    }

    static void printHeader() {
        cout << left
             << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(20) << "Father's Name"
             << setw(50) << "Address"
             << setw(10) << "Qty"
             << setw(15) << "Contact" 
              << setw(15) << "Total Rent"<<endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    }

    string getName() {
        return string(name);
    }

    int getId() {
        return id;
    }
    void saveToFile() {
    ofstream out("farmers.txt", ios::app);  // append mode
    if (out.is_open()) {
        out << id << "|"
            << name << "|"
            << fname << "|"
            << addr << "|"
            << qty << "|"
            << contact << "|"
            << fixed << setprecision(2) << total_rent << "\n";
        out.close();
    } else {
        cout << "Error opening file!" << endl;
    }
}

static void displayFromFile() {
    ifstream in("farmers.txt");
    if (!in) {
        cout << "File not found.\n";
        return;
    }
    string line;
    Farmer::printHeader();
    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, fname, addr, qty, contact, total_rent;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, fname, '|');
        getline(ss, addr, '|');
        getline(ss, qty, '|');
        getline(ss, contact, '|');
        getline(ss, total_rent, '|');

        cout << left
             << setw(5) << id
             << setw(20) << name
             << setw(20) << fname
             << setw(50) << addr
             << setw(10) << qty
             << setw(15) << contact
             << setw(15) << total_rent
             << endl;
    }
    in.close();
}
static void searchByNameFromFile(const string& searchName) {
    ifstream in("farmers.txt");
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    string line;
    bool found = false;
    Farmer::printHeader();

    while (getline(in, line)) {
        stringstream ss(line);
        string id, name, fname, addr, qty, contact, total_rent;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, fname, '|');
        getline(ss, addr, '|');
        getline(ss, qty, '|');
        getline(ss, contact, '|');
        getline(ss, total_rent, '|');

        if (name == searchName) {
            cout << left
                 << setw(5) << id
                 << setw(20) << name
                 << setw(20) << fname
                 << setw(50) << addr
                 << setw(10) << qty
                 << setw(15) << contact
                 << setw(15) << total_rent
                 << endl;
            found = true;
        }
    }

    if (!found) cout << "Record not found.\n";
    in.close();
}

static void searchByIdFromFile(int searchId) {
    ifstream in("farmers.txt");
    if (!in) {
        cout << "File not found.\n";
        return;
    }

    string line;
    bool found = false;
    Farmer::printHeader();

    while (getline(in, line)) {
        stringstream ss(line);
        string idStr, name, fname, addr, qty, contact, total_rent;
        getline(ss, idStr, '|');
        getline(ss, name, '|');
        getline(ss, fname, '|');
        getline(ss, addr, '|');
        getline(ss, qty, '|');
        getline(ss, contact, '|');
        getline(ss, total_rent, '|');

        if (stoi(idStr) == searchId) {
            cout << left
                 << setw(5) << idStr
                 << setw(20) << name
                 << setw(20) << fname
                 << setw(50) << addr
                 << setw(10) << qty
                 << setw(15) << contact
                 << setw(15) << total_rent
                 << endl;
            found = true;
        }
    }

    if (!found) cout << "Record not found.\n";
    in.close();
}

static int getLastIdFromFile() {
    ifstream in("farmers.txt");
    if (!in) return 0; // No file = no records

    string line, lastLine;
    while (getline(in, line)) {
        if (!line.empty()) lastLine = line;
    }
    in.close();

    if (lastLine.empty()) return 0;

    stringstream ss(lastLine);
    string idStr;
    getline(ss, idStr, '|');

    try {
        return stoi(idStr);
    } catch (...) {
        return 0; // Fallback in case of bad formatting
    }
}

};

int Farmer::cnt = 0;

int main() {
     Farmer::cnt = Farmer::getLastIdFromFile();
    Farmer f[100];
    int ch, n = 0;

    do {
        cout << "\nEnter your choice\n";
        cout << "1 - Enter a record\n";
        cout << "2 - Display all records\n";
        cout << "3 - Search record by name\n";
        cout << "4 - Search record by ID\n";
        cout << "5 - Exit\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                f[n].input();
                f[n].saveToFile();
                n++;
                break;

            case 2:
              Farmer::displayFromFile();

                break;

            case 3: {
    string searchName;
    cout << "Enter the name to be searched: ";
    cin.ignore();
    getline(cin, searchName);
    Farmer::searchByNameFromFile(searchName);
    break;
}

case 4: {
    int searchId;
    cout << "Enter the ID to be searched: ";
    cin >> searchId;
    Farmer::searchByIdFromFile(searchId);
    break;
}

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (true);

    return 0;
}
