// CourseGrade.cpp : This program uses structs to store information about students' course grades.
// It outputs students' names, ID numbers, average scores, and letter grades.
using namespace std;
#include <iostream>
#include <fstream>

struct Student
{
	string name;
	int studentID;
	double* testScores;
	double averageScore;
	char letterGrade;
};

void readData(Student*& students, int numStudents, int numTests)
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
		else if (students[i].averageScore >= 64)
			students[i].letterGrade = 'D';
		else
			students[i].letterGrade = 'F';
	}
}

void printReportCard(const Student* students, int numStudents, int numTests)
{
	cout << "Name\tID\tAverage\tGrade" << endl;
	for (int i = 0; i < numStudents; i++)
	{
		cout << students[i].name << "\t" << students[i].studentID << "\t" 
			 << students[i].averageScore << "\t" << students[i].letterGrade << endl;
		cout << "------------------------------------------" << endl;
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
	
	for (int i = 0; i < numStudents; i++) 
	{
		delete[] students[i].testScores;
	}
	delete[] students;
	students = nullptr;
}
