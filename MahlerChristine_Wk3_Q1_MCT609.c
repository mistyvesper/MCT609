// Author: Christine Mahler
// MCT609 Assignment 3 - Question 1

// Write for statements that print the following sequences of values:
// a.	1, 2, 3, 4, 5, 6, 7
// b.	3, 8, 13, 18, 23
// c.	20, 14, 8, 2, -4, -10
// d.	19, 27, 35, 43, 51

#include <stdio.h>  // standard input/output header
#include <string.h> // string header to get strlen function
#include <limits.h> // limits header to get char limit

int main(void)
{
	char strSequence[CHAR_MAX] = "a"; // declare and initialize string sequence variable as string with max characters
	int aCounter = 1; // declare and initialize counter for "a" sequence of numbers as int type
	int bCounter = 3; // declare and initialize counter for "b" sequence of numbers as int type
	int cCounter = 20; // declare and initialize counter for "c" sequence of numbers as int type
	int dCounter = 19; // declare and initialize counter for "d" sequence of numbers as int type
	int status; // declare status variable for returning result of scanf function

	printf("%s", "Generate a Sequence!\n"); // program intro

	while (strcmp(strSequence, "0") != 0) {

		printf("%s", "\nEnter a sequence (a, b, c, d, or 0 to exit): "); // prompt user for sequence
		status = scanf("%s", &strSequence); // read input

		if (strlen(strSequence) == 1) { // check string length and perform switch statement if true
			
			switch (strSequence[0]) {
			
			// case 0 for exiting the program

			case '0':
				printf("\nGoodbye!"); // goodbye message
				break;
			
			// case a for generating 1, 2, 3, 4, 5, 6, 7 sequence

			case 'A':
			case 'a':
				printf("\n"); // print break for formatting
				for (aCounter; aCounter <= 7; aCounter++) { // for loop to generate sequence
					printf("%d ", aCounter); // print values to console
				}
				printf("\n"); // print break for formatting
				aCounter = 1; // reset counter
				break;
			
			// case b for generating 3, 8, 13, 18, 23 sequence

			case 'B':
			case 'b':
				printf("\n"); // print break for formatting
				for (bCounter; bCounter <= 23; bCounter += 5) { // for loop to generate sequence
					printf("%d ", bCounter); // print values to console
				}
				printf("\n"); // print break for formatting
				bCounter = 3; // reset counter
				break;

			// case c for generating 20, 14, 8, 2, -4, -10 sequence
			
			case 'c':
			case 'C':
				printf("\n"); // print break for formatting
				for (cCounter; cCounter >= -10; cCounter -= 6) { // for loop to generate sequence
					printf("%d ", cCounter); // print values to console
				}
				printf("\n"); // print break for formatting
				cCounter = 20; // reset counter
				break;

			// case d for generating 19, 27, 35, 43, 51 sequence
			
			case 'D':
			case 'd':
				printf("\n"); // print break for formatting
				for (dCounter; dCounter <= 51; dCounter += 8) { // for loop to generate sequence
					printf("%d ", dCounter); // print values to console
				}
				printf("\n"); // print break for formatting
				dCounter = 19; // reset counter
				break;
			
			default:
				printf("%s","\nWarning - invalid value provided. Please try again.\n"); // display warning for invalid values entered
			}
		}
		else {
			printf("%s", "\nWarning - invalid value provided. Please try again.\n"); // display warning for invalid values entered
		}
	}
	
	return 0; // exit program
}