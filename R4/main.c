// File:        main.c
// Description: ... fill this in
// Author:      ... fill this in
// Date:        ... fill this in
// Email:       ... fill this in

// Include files
#include "struct.h"
// TODO: add include for printf/scanf
#include <stdio.h>
// TODO: add include for malloc/free
#include <stdlib.h>

// Function:     main
// Description:  entry point  
Student *studstruct;
int p;

int main()
{

	printf("Enter the number of students: ");
	scanf("%d", &p);
	studstruct = malloc(sizeof(Student) * p);
	for(int i = 0; i < p; i++)
	{
		inputScores(&studstruct[i]);
		calculateScores(&studstruct[i]);
		outputScores(studstruct[i]);
	}
	free(studstruct); 
	return 0;
}
