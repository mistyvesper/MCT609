// Author: Christine Mahler
// MCT609 Assignment 4 - Question 1

// Define a function called hypotenuse that calculates the length of 
// the hypotenuse of a right triangle when the other two sides are given.
// Use this function in a program to determine the length of the hypotenuse for each of the following triangles.
// The function should take two arguments of type double and return the hypotenuse as a double.
// Test your program with the side values specified below:

// | Triangle | Side 1 | Side 2 |
// | 1        | 3.0    | 4.0    |
// | 2        | 5.0    | 12.0   |
// | 3        | 8.0    | 15     |

#include <stdio.h> // standard input/output header
#include <math.h> // math header for pow() and sqrt() functions
#include <stdlib.h> // standard library header for atof() function

double hypotenuse(double side1, double side2); // preprocess hypotenuse function

int main(void)
{
	char side1char[3][CHAR_MAX]; // declare string array for storing side 1 of 3 triangles input by the user
	char side2char[3][CHAR_MAX]; // declare string array for storing side 2 of 3 triangles input by the user
	double side1doub[3]; // declare doubles array for storing side 1 of 3 triangles input by the user
	double side2doub[3]; // declare doubles array for storing side 2 of 3 triangles input by the user
	int i = 1; // declare and intialize counter variable for iterating through user prompts
	int status1 = 0; // declare and initialze status variable for storing result of scanf function with side 1 input values
	int status2 = 0; // declare and initialize status variable for storing result of scanf function with side 2 input values
	int c; // declare variable for stdin flushing
	int n = 0; // declare counter for iterating through each input character
	int digCheck; // declare digit check flag for checking contents of input string

	// program intro
	
	printf("Calculate the hypotenuse for 3 triangles!\n");

	// prompt user for triangle sides for a total of 3 triangles and read input
	
	while (i <= 3) {

	// prompt for side 1
		
		printf("\nEnter side 1 for triangle %d: \n", i);
		status1 = scanf("%s", &side1char[i - 1]); // read input in to string array
		side1doub[i - 1] = atof(side1char[i - 1]); // convert input to double

		digCheck = 0; // reset digit check flag
		n = 0; // reset counter for iterating through each input character
		
	// check each character of input string to determine if invalid input entered 
		
		while (side1char[i - 1][n] != '\0') {  // while character in string is not equal to end of string
			if (isdigit(side1char[i - 1][n]) == 0) { // use isdigit function to check if value is integer
				digCheck = 1; // set digCheck flag = 1 if NOT equal to an integer
			}
			n++; // increment counter
		}
		
	// check for invalid input and prompt again if invalid input provided
		
		if (status1 == 0 || side1doub[i - 1] <= 0 || digCheck == 1) {
			while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters
			status1 = 0; // reset status
			printf("\nWarning - invalid value provided. Please try again.\n");
		}
		else {

	// prompt for side 2

			while (status2 == 0 || side2doub[i - 1] <= 0) {
				printf("\nEnter side 2 for triangle %d: \n", i);
				status2 = scanf("%s", &side2char[i - 1]); // read input in to string array
				side2doub[i - 1] = atof(side2char[i - 1]); // convert input to double

				digCheck = 0; // reset digit check flag
				n = 0; // reset counter for iterating through each input character

	// check each character of input string to determine if invalid input entered 

				while (side2char[i - 1][n] != '\0') {  // while character in string is not equal to end of string
					if (isdigit(side2char[i - 1][n]) == 0) { // use isdigit function to check if value is integer
						digCheck = 1; // set digCheck flag = 1 if NOT equal to an integer
					}
					n++;
				}

	// check for invalid input and prompt again if invalid input provided

				if (status2 == 0 || side2doub[i - 1] <= 0 || digCheck == 1) {
					while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters
					status2 = 0; // reset status
					printf("\nWarning - invalid value provided. Please try again.\n");
				}
			}
			i++; // increment counter
			status2 = 0; // reset status
		}
	}

	// display results

	printf("\nThe results are in!\n\n");
	printf("Triangle\tSide 1\tSide 2\tHypotenuse\n");

	for (i = 1; i <= 3; ++i) // calculate and display hypotenuse alongside information used to perform calculations
	{
		printf("%d\t\t%.1f\t%.1f\t%.1f\n", i, side1doub[i - 1], side2doub[i - 1], hypotenuse(side1doub[i - 1], side2doub[i - 1]));
	}
	
	printf("\n"); // print break for formatting

	system("pause"); // pause to allow user to view results
	return 0; // exit program
}

// define hypotenuse function

double hypotenuse(double side1, double side2)
{
	return sqrt(pow(side1, 2) + pow(side2, 2));
}
