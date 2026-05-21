#include <iostream>     // For input and output
#include <fstream>      // For file handling
#include <string>       // For string operations
#include <cstdio>       // For remove() and rename()

using namespace std;

// ======================================================
// Function: initializeDatabase()
// Purpose : Create attendance.csv file if it does not exist
//           and add column headings.
// ======================================================

void initializeDatabase() {

    // Open file in read mode
    ifstream file("attendance.csv");

    // If file does not exist
    if (!file) {

        // Create new file
        ofstream newFile("attendance.csv");

        // Add headings
        newFile << "ID,Name,Department,Attendance\n";

        // Close file
        newFile.close();

        cout << "Database created successfully.\n";
    }

    else {

        cout << "Database already exists.\n";
    }

    // Close checking file
    file.close();
}

// ======================================================
// Function: isUnique()
// Purpose : Check whether Student ID already exists.
// Return  : true  -> Unique ID
//           false -> Duplicate ID
// ======================================================

bool isUnique(string id) {

    // Open file
    ifstream file("attendance.csv");

    string line;

    // Read file line by line
    while (getline(file, line)) {

        // Skip header row
        if (line == "ID,Name,Department,Attendance") {

            continue;
        }

        // Extract ID from CSV line
        string storedID = line.substr(0, line.find(','));

        // Compare IDs
        if (storedID == id) {

            file.close();

            return false;
        }
    }

    // Close file
    file.close();

    return true;
}

// ======================================================
// Function: appendRecord()
// Purpose : Add new student record into CSV file.
// ======================================================

void appendRecord(string data) {

    // Open file in append mode
    ofstream file("attendance.csv", ios::app);

    // Write record
    file << data << endl;

    // Close file
    file.close();

    cout << "Record added successfully.\n";
}

// ======================================================
// Function: searchByID()
// Purpose : Search student record using ID.
// ======================================================

void searchByID(string id) {

    // Open file
    ifstream file("attendance.csv");

    string line;

    bool found = false;

    // Read line by line
    while (getline(file, line)) {

        // Skip header
        if (line == "ID,Name,Department,Attendance") {

            continue;
        }

        // Extract ID
        string storedID = line.substr(0, line.find(','));

        // Compare IDs
        if (storedID == id) {

            cout << "\n===== Student Record Found =====\n";

            cout << line << endl;

            found = true;

            break;
        }
    }

    // If record not found
    if (!found) {

        cout << "Student record not found.\n";
    }

    // Close file
    file.close();
}

// ======================================================
// Function: updateRecord()
// Purpose : Update student record.
// Method  : Temporary file method.
// ======================================================

void updateRecord(string id, string newData) {

    // Open original file
    ifstream file("attendance.csv");

    // Create temporary file
    ofstream temp("temp.csv");

    string line;

    bool found = false;

    // Read original file
    while (getline(file, line)) {

        // Keep header unchanged
        if (line == "ID,Name,Department,Attendance") {

            temp << line << endl;

            continue;
        }

        // Extract ID
        string storedID = line.substr(0, line.find(','));

        // If matching ID found
        if (storedID == id) {

            // Write updated data
            temp << newData << endl;

            found = true;
        }

        else {

            // Copy old data
            temp << line << endl;
        }
    }

    // Close files
    file.close();
    temp.close();

    // Delete old file
    remove("attendance.csv");

    // Rename temp file
    rename("temp.csv", "attendance.csv");

    // Display result
    if (found) {

        cout << "Record updated successfully.\n";
    }

    else {

        cout << "Record not found.\n";
    }
}

// ======================================================
// Function: deleteRecord()
// Purpose : Delete student record.
// ======================================================

void deleteRecord(string id) {

    // Open original file
    ifstream file("attendance.csv");

    // Create temp file
    ofstream temp("temp.csv");

    string line;

    bool found = false;

    // Read original file
    while (getline(file, line)) {

        // Keep header row
        if (line == "ID,Name,Department,Attendance") {

            temp << line << endl;

            continue;
        }

        // Extract ID
        string storedID = line.substr(0, line.find(','));

        // Skip matching record
        if (storedID == id) {

            found = true;
        }

        else {

            // Copy remaining records
            temp << line << endl;
        }
    }

    // Close files
    file.close();
    temp.close();

    // Delete old file
    remove("attendance.csv");

    // Rename temp file
    rename("temp.csv", "attendance.csv");

    // Display result
    if (found) {

        cout << "Record deleted successfully.\n";
    }

    else {

        cout << "Record not found.\n";
    }
}

// ======================================================
// Function: displayAllRecords()
// Purpose : Display all student records.
// ======================================================

void displayAllRecords() {

    // Open file
    ifstream file("attendance.csv");

    string line;

    cout << "\n===== All Student Records =====\n\n";

    // Display all lines
    while (getline(file, line)) {

        cout << line << endl;
    }

    // Close file
    file.close();
}

// ======================================================
// Main Function
// ======================================================

int main() {

    // Initialize database
    initializeDatabase();

    int choice;

    // Repeat menu until Exit selected
    do {

        cout << "\n===== Student Attendance Management System =====\n";

        // Menu options
        cout << "1. Add Student Record\n";
        cout << "2. Search Student Record\n";
        cout << "3. Update Student Record\n";
        cout << "4. Delete Student Record\n";
        cout << "5. Display All Records\n";
        cout << "6. Exit\n";

        // Input choice
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer
        cin.ignore();

        // ==================================================
        // Option 1 : Add Student
        // ==================================================

        if (choice == 1) {

            string id;
            string name;
            string department;

            int attendance;

            // Input ID
            cout << "Enter Student ID: ";
            getline(cin, id);

            // Check duplicate ID
            if (!isUnique(id)) {

                cout << "Duplicate ID not allowed.\n";

                continue;
            }

            // Input Name
            cout << "Enter Student Name: ";
            getline(cin, name);

            // Input Department
            cout << "Enter Department: ";
            getline(cin, department);

            // Input Attendance
            cout << "Enter Attendance Percentage: ";
            cin >> attendance;

            // Validate attendance
            if (attendance < 0 || attendance > 100) {

                cout << "Invalid Attendance Percentage.\n";

                cin.ignore();

                continue;
            }

            // Clear buffer
            cin.ignore();

            // Create CSV record
            string data = id + "," + name + "," +
                          department + "," + to_string(attendance);

            // Save record
            appendRecord(data);
        }

        // ==================================================
        // Option 2 : Search Student
        // ==================================================

        else if (choice == 2) {

            string id;

            // Input ID
            cout << "Enter Student ID to search: ";
            getline(cin, id);

            // Search record
            searchByID(id);
        }

        // ==================================================
        // Option 3 : Update Student
        // ==================================================

        else if (choice == 3) {

            string id;
            string name;
            string department;

            int attendance;

            // Input ID
            cout << "Enter Student ID to update: ";
            getline(cin, id);

            // Input new name
            cout << "Enter New Name: ";
            getline(cin, name);

            // Input new department
            cout << "Enter New Department: ";
            getline(cin, department);

            // Input new attendance
            cout << "Enter New Attendance Percentage: ";
            cin >> attendance;

            // Validate attendance
            if (attendance < 0 || attendance > 100) {

                cout << "Invalid Attendance Percentage.\n";

                cin.ignore();

                continue;
            }

            // Clear buffer
            cin.ignore();

            // Create updated record
            string newData = id + "," + name + "," +
                             department + "," + to_string(attendance);

            // Update record
            updateRecord(id, newData);
        }

        // ==================================================
        // Option 4 : Delete Student
        // ==================================================

        else if (choice == 4) {

            string id;

            // Input ID
            cout << "Enter Student ID to delete: ";
            getline(cin, id);

            // Delete record
            deleteRecord(id);
        }

        // ==================================================
        // Option 5 : Display All Records
        // ==================================================

        else if (choice == 5) {

            // Display all records
            displayAllRecords();
        }

        // ==================================================
        // Option 6 : Exit Program
        // ==================================================

        else if (choice == 6) {

            cout << "Exiting Program...\n";
        }

        // ==================================================
        // Invalid Choice
        // ==================================================

        else {

            cout << "Invalid Choice.\n";
        }

    } while (choice != 6);

    return 0;
}