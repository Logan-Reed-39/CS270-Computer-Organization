// File:        struct.c
// Description: ... fill this in
// Author:      ... fill this in
// Date:        ... fill this in
// Email:       ... fill this in

// Include files
#include "struct.h"
// TODO: add include for printf/scanf
#include <stdio.h>

// Input scores
void inputScores(Student *student)
{
	printf("Enter the first name: ");
	scanf("%s", student -> firstName);
	printf("Enter the last name: ");
	scanf("%s", student -> lastName);
	printf("Enter the average homework score: ");
	scanf("%d", &student -> avghomeworkscore);
	printf("Enter the average lab score: ");
	scanf("%d", &student -> avglabscore);
	printf("Enter the midterm score: ");
	scanf("%d", &student -> midtermscore);
	printf("Enter the final exam score: ");
	scanf("%d", &student -> finalscore);
}
	


// Output scores
void outputScores(Student student)
{
	printf("First name: %s", student.firstName);
	printf("\n");
	printf("Last name: %s", student.lastName);
	printf("\n");
	printf("Average homework score: %d", student.avghomeworkscore);
	printf("\n");
	printf("Average lab score: %d", student.avglabscore);
	printf("\n");
	printf("Midterm score: %d", student.midtermscore);
	printf("\n");
	printf("Final exam score: %d", student.finalscore);
	printf("\n");
	printf("Total points: %.2f", student.totalPoints);
	printf("\n");
	printf("Letter grade: %c", student.letterGrade);
	printf("\n");
}

// Calculate scores
void calculateScores(Student *student)
{
	(*student).totalPoints = ((student -> avghomeworkscore * .30) +  (student -> avglabscore * 0.20) + (student -> midtermscore * 0.20) + (student -> finalscore * 0.30));
	if(90.0 < student -> totalPoints)
	{
		(*student).letterGrade = 'A';
	}
	if(80.0 < student -> totalPoints && student -> totalPoints < 90)
	{
		(*student).letterGrade = 'B';
	}
	if(70.0 < student -> totalPoints && student -> totalPoints < 80)
	{
		(*student).letterGrade = 'C';
	}
	if(60.0 < student -> totalPoints && student -> totalPoints < 70)
	{
		(*student).letterGrade = 'D';
	}
	if(student -> totalPoints < 60.0)
	{
		(*student).letterGrade = 'F';
	}

}


