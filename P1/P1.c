// P1 Assignment
// Author: Logan Reed
// Date:   8/25/2016
// Class:  CS270
// Email:  lvreed@cs.colostate.edu

// Include files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//static double input[4];
static double output[4];


void computeSphere(double radius, double *addressOfVolume)
{
    // Compute volume
    double result = (4.0 / 3.0) * (3.141593 * radius * radius * radius);

    // Dereference pointer to return result
    *addressOfVolume = result;
}
void computeCircle(double radius1, double *areaAddress)
{
	// Compute area
	double result1 = 3.141593 * radius1 * radius1;
	
	// Dereference pointer to return result1
	*areaAddress = result1;
}
void computeTriangle(double side, double *areaAddress)
{
	// Compute area
	double result1 =  0.433013 * side * side;
	
	// Dereference pointer to return result1
	*areaAddress = result1;
}
void computeSquare(double side, double *areaAddress)
{
	// Compute area
	double result1 = side * side;
	
	// Dereference pointer to return result1
	*areaAddress = result1;
}
void computePentagon(double side, double *areaAddress)
{
	// Compute area
	double result1 =   1.720477 * side * side;
	
	// Dereference pointer to return result1
	*areaAddress = result1;
}

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 5) {
        printf("usage: ./P1 <double> <double> <double> <double>\n");
        return EXIT_FAILURE;
    }

    // Parse arguments
    double measure1 = atof(argv[1]);
	double measure2 = atof(argv[2]);
	double measure3 = atof(argv[3]);
	double measure4 = atof(argv[4]);

    // Call function
    computeCircle(measure1, &output[0]);
	computeTriangle(measure2, &output[1]);
	computeSquare(measure3, &output[2]);
	computePentagon(measure4, &output[3]);
    
    // Print volume
    printf("CIRCLE, radius = %.5f, area = %.5f.\n", measure1, output[0]);
	printf("TRIANGLE, length = %.5f, area = %.5f.\n", measure2, output[1]);
	printf("SQUARE, length = %.5f, area = %.5f.\n", measure3, output[2]);
    printf("PENTAGON, length = %.5f, area = %.5f.\n", measure4, output[3]);



    // Return success
    return EXIT_SUCCESS;
}
