#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

float calculateAverageMarks(int marks[]);

char calculateGrade(float average);

void updateMarks(int rollNumbers[], int studentCount, int marks[][3], float averages[], char grades[]);

void searchByRollNumber(int rollNumbers[], int studentCount, string names[],

                        int marks[][3], float averages[], char grades[]);

bool checkIfRollNumberExists(int rollNumber, int rollNumbers[], int currentStudentCount);

void addStudent(string names[], int marks[][3], int rollNumbers[], float averages[], char grades[], int MAX_STUDENTS, int &studentCount);

void displayAllStudents(string names[], int marks[][3], int rollNumbers[],

float averages[], char grades[], int studentCount);

void deleteByRollNumber(int rollNumbers[], int &studentCount, string names[], int marks[][3], float averages[], char grades[], bool attendance[][30]);

void sort(int rollNumbers[], string names[], int marks[][3], float averages[], char grades[], int studentCount);

void displayTop3Students(int rollNumbers[], string names[], int marks[][3], float averages[], char grades[], int studentCount);

void markStudentAttendence(int maxDays, int studentCount, bool attendance[][30]);

void gradeSummary(char grades[], int studentCount);

void attendanceSummary(int rollNumbers[], int studentCount, bool attendance[][30]);

void exportToTextFile(int rollNumbers[], char grades[], int studentCount, bool attendance[][30]);

int main()
{

    const int MAX_STUDENTS = 50;
    const int MAX_DAYS = 30;
    int rollNumbers[MAX_STUDENTS];
    string names[MAX_STUDENTS];
    int marks[MAX_STUDENTS][3];
    float averages[MAX_STUDENTS];
    char grades[MAX_STUDENTS];
    bool attendance[MAX_STUDENTS][MAX_DAYS];

    int studentCount = 0;
    int choice;
    int password = 1234;
    int userEnteredPassword;
    bool isLoggedIn = false;

    for (int i = 0; i < MAX_STUDENTS; i++)
    for (int j = 0; j < MAX_DAYS; j++)
        attendance[i][j] = false;
        
    cout << "\033[33mInitializing Super Serious Student Management System...\033[0m\n";
    cout << "\033[32mLoading: [##########] 100%\n\033";
    cout << "\033[36mSystem Ready. Please behave professionally :)\033[0m\n";

    do
    {
        if (!isLoggedIn)
        {
            cout << "Enter Your Password: ";
            cin >> userEnteredPassword;

            if (userEnteredPassword == password)
            {
                isLoggedIn = true;
            }
            else
            {
                cout << "Wrong Password, try again!" << endl;
                continue;
            }
        }
        else
        {

            cout << "\033[36m1. Add Student\033[0m\n";
            cout << "\033[36m2. Display All Students\033[0m\n";
            cout << "\033[36m3. Search by Roll Number\033[0m\n";
            cout << "\033[36m4. Update Student Marks\033[0m\n";
            cout << "\033[36m5. Delete By Roll Number\033[0m\n";
            cout << "\033[36m6. Display Top 3 Students\033[0m\n";
            cout << "\033[36m7. Attendance\033[0m\n";
            cout << "\033[36m8. Grade Summary ( We won't judge )\033[0m\n";
            cout << "\033[36m9. Attendance Summary ( Who Bunked The Most? )\033[0m\n";
            cout << "\033[33m10. Export to Text File\033[0m\n";
            cout << "\033[31m11. Exit\033[0m\n";               
            cout << "\033[36mEnter your choice: \033[0m";
            cin >> choice;

            switch (choice)
            {

            case 1:
                addStudent(names, marks, rollNumbers, averages, grades, MAX_STUDENTS, studentCount);
                break;
            case 2:
                displayAllStudents(names, marks, rollNumbers, averages, grades, studentCount);
                break;
            case 3:
                searchByRollNumber(rollNumbers, studentCount, names, marks, averages, grades);
                break;
            case 4:
                updateMarks(rollNumbers, studentCount, marks, averages, grades);
                break;
            case 5:
                deleteByRollNumber(rollNumbers, studentCount, names, marks, averages, grades,attendance);
                break;
            case 6:
                displayTop3Students(rollNumbers, names, marks, averages, grades, studentCount);
                break;
            case 7:
                markStudentAttendence(MAX_DAYS, studentCount, attendance);
                break;
            case 8:
                gradeSummary(grades, studentCount);
                break;
            case 9:
                attendanceSummary(rollNumbers, studentCount, attendance);
                break;
            case 10:
                exportToTextFile(rollNumbers, grades, studentCount, attendance);
                break;
            case 11:
                cout << "Exiting..." << endl;
                return 0;
                break;
            default:
                cout << "Invalid choice! " << endl;
            }
        }
    } while (true);

    return 0;
}

bool checkIfRollNumberExists(int rollNumber, int rollNumbers[], int currentStudentCount)
{
    for (int i = 0; i < currentStudentCount; i++)
    {
        if (rollNumbers[i] == rollNumber)
            return true;
    }
    return false;
}

float calculateAverageMarks(int marks[])
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
        sum += marks[i];
    float avg = static_cast<float>(sum) / 3.0f;
    return avg;
}

char calculateGrade(float average)
{
    if (average >= 85)
        return 'A';
    else if (average >= 70)
        return 'B';
    else if (average >= 50)
        return 'C';
    else
        return 'F';
}

void addStudent(string names[], int marks[][3], int rollNumbers[], float averages[], char grades[], int MAX_STUDENTS, int &studentCount)
{

    if (studentCount >= MAX_STUDENTS)
    {
        cout << "Maximum students reached " << endl;
        return;
    }

    cout << "\nEnter Student Name: ";
    cin.ignore();
    getline(cin, names[studentCount]);

    cout << "Enter Roll Number: ";
    cin >> rollNumbers[studentCount];

    if (checkIfRollNumberExists(rollNumbers[studentCount], rollNumbers, studentCount))
    {
        cout << "Roll number already exists!" << endl;
        return;
    }

    for (int i = 0; i < 3; i++)
    {
        int m;
        cout << "Enter marks for subject " << i + 1 << ": ";
        cin >> m;
        if (m < 0 || m > 100)
        {
            cout << "Marks must be between 0 and 100 " << endl;
            return;
        }

        marks[studentCount][i] = m;
    }

    averages[studentCount] = calculateAverageMarks(marks[studentCount]);
    grades[studentCount] = calculateGrade(averages[studentCount]);
    studentCount++;
    cout<<endl;
    cout << "\033[32mStudent added successfully!\033[0m\n";
    cout<<endl;
}

void displayAllStudents(string names[], int marks[][3],
                        int rollNumbers[], float averages[],
                        char grades[], int studentCount)
{

    if (studentCount == 0)
    {
        cout << "No students to display" << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        cout << "----------------------------------" << endl;
        cout << "Student " << i + 1 << endl;

        cout << "Name: " << names[i] << endl;
        cout << "Roll Number: " << rollNumbers[i] << endl;

        cout << "Marks: "
             << marks[i][0] << ", "
             << marks[i][1] << ", "
             << marks[i][2] << endl;

        cout << "Average: " << averages[i] << endl;
        cout << "Grade: " << grades[i] << endl;
        cout << "----------------------------------" << endl;
    }
}

void searchByRollNumber(int rollNumbers[], int studentCount,
                        string names[], int marks[][3],
                        float averages[], char grades[])
{

    if (studentCount == 0)
    {
        cout << "No students available " << endl;
        return;
    }

    int rollNumber;
    cout << "Enter roll number to search: ";
    cin >> rollNumber;

    for (int i = 0; i < studentCount; i++)
    {

        if (rollNumbers[i] == rollNumber)
        {
            cout << "Name: " << names[i] << endl;
            cout << "Roll Number: " << rollNumbers[i] << endl;
            cout << "Marks: "
                 << marks[i][0] << ", "
                 << marks[i][1] << ", "
                 << marks[i][2] << endl;
            cout << "Average: " << averages[i] << endl;
            cout << "Grade: " << grades[i] << endl;
            return;
        }
    }
    cout << "Roll number not found" << endl;
}

void updateMarks(int rollNumbers[], int studentCount, int marks[][3], float averages[], char grades[])
{
    if (studentCount == 0)
    {
        cout << "No students available" << endl;
        return;
    }
    int rollNumber;
    cout << "Enter roll number to update marks: ";
    cin >> rollNumber;
    for (int i = 0; i < studentCount; i++)
    {
        if (rollNumbers[i] == rollNumber)
        {
            for (int j = 0; j < 3; j++)
            {
                int mark;
                cout << "Enter new marks for subject "
                     << j + 1 << ": ";
                cin >> mark;
                if (mark < 0 || mark > 100)
                {
                    cout << "Invalid marks" << endl;
                    return;
                }
                marks[i][j] = mark;
            }
            averages[i] =
                calculateAverageMarks(marks[i]);
            grades[i] =
                calculateGrade(averages[i]);
            cout << "Marks updated successfully!\n";
            return;
        }
    }

    cout << "Roll number not found" << endl;
}

void deleteByRollNumber(int rollNumbers[], int &studentCount, string names[], int marks[][3], float averages[], char grades[], bool attendance[][30])
{
    int rollNumber;
    cout << "Enter Roll Number of student you want to delete: ";
    cin >> rollNumber;

    int index = -1;
    for (int i = 0; i < studentCount; i++)
        if (rollNumbers[i] == rollNumber)
            index = i;

    if (index == -1)
    {
        cout << "Roll Number doesn't exist!" << endl;
        return;
    }

    for (int i = index; i < studentCount - 1; i++)
    {
        rollNumbers[i] = rollNumbers[i + 1];
        names[i] = names[i + 1];
        averages[i] = averages[i + 1];
        grades[i] = grades[i + 1];

        for (int j = 0; j < 3; j++)
            marks[i][j] = marks[i + 1][j];

        for (int d = 0; d < 30; d++)
            attendance[i][d] = attendance[i + 1][d];
    }

    studentCount--;

    cout << "Deleted Successfully!\n";
}


void sort(int rollNumbers[], string names[], int marks[][3], float averages[], char grades[], int studentCount)
{
    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = i + 1; j < studentCount; j++)
        {
            if (averages[j] > averages[i])
            {
                swap(rollNumbers[i], rollNumbers[j]);
                swap(names[i], names[j]);
                for (int k = 0; k < 3; k++)
                    swap(marks[i][k], marks[j][k]);
                swap(averages[i], averages[j]);
                swap(grades[i], grades[j]);
            }
        }
    }
}

void displayTop3Students(int rollNumbers[], string names[], int marks[][3], float averages[], char grades[], int studentCount)
{
    if (studentCount < 3)
    {
        cout << "Not Enough Records!";
        return;
    }
    sort(rollNumbers, names, marks, averages, grades, studentCount);
    for (int i = 0; i < 3; i++)
    {
        cout << "Roll Number: " << rollNumbers[i] << endl;
        cout << "Name: " << names[i] << endl;
        cout << "Marks: " << marks[i][0] << "," << marks[i][1] << "," << marks[i][2] << endl;
        cout << "Average: " << averages[i] << endl;
        cout << "Grade: " << grades[i] << endl;
    }
}

void markStudentAttendence(int maxDays, int studentCount, bool attendance[][30])
{
    int day;
    cout << "Enter day number (1-30): ";
    cin >> day;
    if (day < 1 || day > maxDays)
    {
        cout << "Invalid day number!" << endl;
        return;
    }
    day--;
    for (int i = 0; i < studentCount; i++)
    {
        char present;
        cout << "Roll No student " << i + 1 << " -> Present (P) or Absent (A): ";
        cin >> present;

        if (present == 'P' || present == 'p')
            attendance[i][day] = true;
        else
            attendance[i][day] = false;
    }

    cout << "Attendance marked successfully!" << endl;
}

void attendanceSummary(int rollNumbers[], int studentCount, bool attendance[][30])
{
    for (int i = 0; i < studentCount; i++)
    {
        int present = 0, absent = 0;

        for (int j = 0; j < 30; j++)
        {
            if (attendance[i][j])
                present++;
            else
                absent++;
        }

        double percentage = (present * 100.0) / (present + absent);

        cout << "Roll Number: " << rollNumbers[i]
             << " Attendance %: " << percentage << endl;

        if (percentage < 75)
            cout << "** LOW ATTENDANCE **" << endl;
    }
}

void gradeSummary(char grades[], int studentCount)
{
    int numberOfStudentsWithA = 0, numberOfStudentsWithB = 0, numberOfStudentsWithC = 0, numberOfStudentsWithF = 0;
    for (int i = 0; i < studentCount; i++)
    {
        if (grades[i] == 'A')
            numberOfStudentsWithA++;
        else if (grades[i] == 'B')
            numberOfStudentsWithB++;
        else if (grades[i] == 'C')
            numberOfStudentsWithC++;
        else if (grades[i] == 'F')
            numberOfStudentsWithF++;
    }
    cout << "Number of Students with A: " << numberOfStudentsWithA << endl;
    cout << "Number of Students with B: " << numberOfStudentsWithB << endl;
    cout << "Number of Students with C: " << numberOfStudentsWithC << endl;
    cout << "Number of Students with F: " << numberOfStudentsWithF << endl;
}

void exportToTextFile(int rollNumbers[], char grades[], int studentCount, bool attendance[][30])
{
    ofstream file("studentRecords.txt");
    if (!file.is_open())
    {
        cout << "Error opening file!" << endl;
        return;
    }
    file << "ATTENDANCE SUMMARY\n";
    for (int i = 0; i < studentCount; i++)
    {
        int present = 0, absent = 0;
        for (int j = 0; j < 30; j++)
        {
            if (attendance[i][j])
                present++;
            else
                absent++;
        }
        double percentage = (present * 100.0) / (present + absent);
        file << "Roll Number: " << rollNumbers[i] << " Attendance %: " << percentage;
        if (percentage < 75)
            file << " ** LOW ATTENDANCE **";
        file << endl;
    }
    int A = 0, B = 0, C = 0, F = 0;

    for (int i = 0; i < studentCount; i++)
    {
        if (grades[i] == 'A')
            A++;
        else if (grades[i] == 'B')
            B++;
        else if (grades[i] == 'C')
            C++;
        else if (grades[i] == 'F')
            F++;
    }

    file << "\nGRADE SUMMARY\n";
    file << "A: " << A << endl;
    file << "B: " << B << endl;
    file << "C: " << C << endl;
    file << "F: " << F << endl;

    file.close();
    cout << "Records exported to studentRecords.txt" << endl;
}
