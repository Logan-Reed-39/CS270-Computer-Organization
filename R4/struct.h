// File:        struct.h
// Description: ... fill this in
// Author:      ... fill this in
// Date:        ... fill this in
// Email:       ... fill this in

// Structure definition
typedef struct
{
    char firstName[80];
    // TODO: Add required fields
    char lastName[80];
    int avghomeworkscore;
    int avglabscore;
    int midtermscore;
    int finalscore;
	float totalPoints;
	char letterGrade;
} Student;

// Function Prototypes
void inputScores(Student *student);
void outputScores(Student student);
void calculateScores(Student *student);
// TODO: Add required functions
