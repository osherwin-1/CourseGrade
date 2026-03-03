// CourseGrade.cpp : This program uses structs to store information about students' course grades.
// It outputs students' names, ID numbers, average scores, and letter grades.
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
// Structure holding student information
struct Student
{
	string name;
	int studentID;
	double* testScores;
	double averageScore;
	char letterGrade;
};
// Function to read student data from a file
// Takes student array, number of students, and number of tests as parameters.
// Precondition: The file "student_data.txt" must exist and be formatted correctly with the number of students, number of tests, and each student's name, ID, and test scores. Postcondition: The student array is populated with data from the file.
// Postcondition: The student array is populated with data from the file.
void readData(Student*& students, int& numStudents, int& numTests)
{
	
	ifstream inFile("student_data.txt");
	if (!(inFile))
	{
		cerr << "Error opening file!" << endl;
		exit(1);
	}
	inFile >> numStudents >> numTests;
	students = new Student[numStudents];
	for (int i = 0; i < numStudents; i++)
	{
		inFile >> students[i].name >> students[i].studentID;
		students[i].testScores = new double[numTests];
		for (int j = 0; j < numTests; j++)
		{
			inFile >> students[i].testScores[j];
		}
		students[i].averageScore = 0;
		students[i].letterGrade = 'F';
	}
	inFile.close();
}
// Function to calculate average scores for each student
// Takes student array, number of students, and number of tests as parameters. 
// Precondition: The student array must be populated with test scores. 
// Postcondition: Each student's average score is calculated and stored in the averageScore member of the Student struct.
void calculateAverages(Student* students, int numStudents, int numTests)
{
	for (int i = 0; i < numStudents; i++)
	{
		double total = 0;
		for (int j = 0; j < numTests; j++)
		{
			total += students[i].testScores[j];
		}
		students[i].averageScore = total / numTests;
	}
}
// Function to assign letter grades based on average scores
// Takes student array and number of students as parameters.
// Precondition: Each student's average score must be calculated and stored in the averageScore member of the Student struct.
// Postcondition: Each student's letter grade is assigned based on their average score and stored in the letterGrade member of the Student struct.
void giveLetter(Student* students, int numStudents)
{
	for (int i = 0; i < numStudents; i++)
	{
		if (students[i].averageScore >= 90)
			students[i].letterGrade = 'A';
		else if (students[i].averageScore >= 80)
			students[i].letterGrade = 'B';
		else if (students[i].averageScore >= 70)
			students[i].letterGrade = 'C';
		else if (students[i].averageScore >= 60)
			students[i].letterGrade = 'D';
		else
			students[i].letterGrade = 'F';
	}
}
// Function to print the course report card
// Takes student array, number of students, and number of tests as parameters.
// Precondition: Each student's name, ID, average score, and letter grade must be calculated and stored in the respective members of the Student struct.
// Postcondition: The course report card is printed to the console, displaying each student's name, ID, average score, and letter grade in a formatted manner.
void printReportCard(const Student* students, int numStudents, int numTests)
{
	cout << "Course Report Card" << endl;
	cout << "" << endl;
	cout << "Name\tID\tAverage\tGrade" << endl;
	cout << "-------------------------------" << endl;
	for (int i = 0; i < numStudents; i++)
	{
		cout << students[i].name << "\t" << students[i].studentID << "\t" 
			 << students[i].averageScore << "\t" << students[i].letterGrade << endl;
		cout << "-------------------------------" << endl;
	}
}

int main()
{
	int numStudents = 0;
	int numTests = 0;
	Student* students = nullptr;
	readData(students, numStudents, numTests);
	calculateAverages(students, numStudents, numTests);
	giveLetter(students, numStudents);
	printReportCard(students, numStudents, numTests);
	
	for (int i = 0; i < numStudents; i++) //Removes each element of the testScores array for each student to prevent memory leaks.
	{
		delete[] students[i].testScores;
	}
	delete[] students; // Removes the students array to prevent memory leaks.
	students = nullptr; // Sets the students pointer to nullptr after deleting to avoid pointer issues.
}
