#include <iostream>
#include <iomanip>
#include <string>
#include <map>
using namespace std;

// Global map for grade conversion (safe for all compilers)
map<string, double> gradeTable;

// Function to convert grade to points
double gradeToPoints(string grade) {
    if (gradeTable.find(grade) != gradeTable.end())
        return gradeTable[grade];
    return -1; // invalid grade
}

int main() {
    // Fill the grade table (no initializer list ? works everywhere)
    gradeTable["A+"] = 4.0;
    gradeTable["A"]  = 4.0;
    gradeTable["A-"] = 3.7;
    gradeTable["B+"] = 3.3;
    gradeTable["B"]  = 3.0;
    gradeTable["B-"] = 2.7;
    gradeTable["C+"] = 2.3;
    gradeTable["C"]  = 2.0;
    gradeTable["C-"] = 1.7;
    gradeTable["D+"] = 1.3;
    gradeTable["D"]  = 1.0;
    gradeTable["F"]  = 0.0;

    int n;
    cout << "Enter number of courses this semester: ";
    cin >> n;

    double totalCredits = 0, totalGradePoints = 0;

    string grade;
    double credit;

    cout << "\n--- Enter Course Details ---\n";

    for (int i = 1; i <= n; i++) {
        cout << "\nCourse " << i << ":\n";

        // Input grade
        cout << "Enter grade (A, B+, C-, etc.): ";
        cin >> grade;

        // Validate grade
        while (gradeToPoints(grade) < 0) {
            cout << "Invalid grade! Enter again: ";
            cin >> grade;
        }

        // Input credits
        cout << "Enter credit hours: ";
        cin >> credit;

        double gp = gradeToPoints(grade);
        totalCredits += credit;
        totalGradePoints += gp * credit;

        cout << "Recorded: Grade = " << grade
             << ", Credit = " << credit
             << ", Grade Points = " << gp << endl;
    }

    // Calculate Semester GPA
    double semesterGPA = totalGradePoints / totalCredits;

    // Ask for previous CGPA details
    char choice;
    double previousCGPA = 0, previousCredits = 0;

    cout << "\nDo you have previous CGPA? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        cout << "Enter previous CGPA: ";
        cin >> previousCGPA;
        cout << "Enter previous total credits: ";
        cin >> previousCredits;
    }

    // Calculate Overall CGPA
    double finalCGPA;
    if (previousCredits > 0) {
        finalCGPA = (previousCGPA * previousCredits +
                     semesterGPA * totalCredits) /
                    (previousCredits + totalCredits);
    } else {
        finalCGPA = semesterGPA;
    }

    // Display results
    cout << fixed << setprecision(2);
    cout << "\n--- Results ---\n";
    cout << "Total Credits This Semester: " << totalCredits << endl;
    cout << "Semester GPA: " << semesterGPA << endl;
    cout << "Final CGPA: " << finalCGPA << endl;

    return 0;
}

