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

void readData(Student*& students)
{
	int numStudents;
	int numTests;
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

int main()
{
	Student* students = nullptr;
	readData(students);
}
