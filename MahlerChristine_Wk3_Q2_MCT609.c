// Author: Christine Mahler
// MCT609 Assignment 3 - Question 2

// One interesting application of computers is drawing graphs and bar charts (sometimes called histograms).
// Write a program that first reads and stores five numbers (each between 1 and 30). 
// Then, for each number read, your program should print a line containing that number of adjacent asterisks 
// (e.g. for the number seven, it should print *******), so that it displays five rows of asterisks.

#include <stdio.h> // standard input/output header
#include <math.h> // math header for ceiling function
#include <ctype.h> // ctype header for isdigit function
#include <limits.h> // limits header for CHAR_MAX

int main(void) {
	
	int counter = 1; // declare and initialize counter variable for 5 numbers
	char strNumbers[5][CHAR_MAX]; // declare string array with 6 positions with a max of 50 characters per position for storing input
	float floatNumbers[5]; // declare float array with 6 positions for storing converted input
	int n = 0; // declare and initialize counter for iterating through strNumber characters
	int digCheck = 0; // declare and initialize digit check variable
	int i; // declare counter for repeating asterisks
	int astCount; // declare variable for asterisk count
	int c; // declare variable for stdin flushing

	printf("%s", "Create a histogram!\n"); // program intro

	// prompt user for and read 5 numbers (storing in string array)

	while (counter <= 5) {
		printf("%s", "\nInput a number between 1 and 30: "); // prompt user for a number
		scanf(" %s", &strNumbers[counter - 1]); // read input and store in string array
		floatNumbers[counter - 1] = atof(&strNumbers[counter - 1]); // convert input to float and store in float array

		// check if each character in string input

		while (strNumbers[counter - 1][n] != '\0') {  // while character in string is not equal to end of string
			if (isdigit(strNumbers[counter - 1][n]) == 0) { // use isdigit function to check if value is integer
				digCheck= 1; // set digCheck flag = 1 if NOT equal to an integer
			} 
			n++;
		}

		// check for invalid input

		if (digCheck == 1 || floatNumbers[counter - 1] < 1 || floatNumbers[counter - 1] > 30 || ceilf(floatNumbers[counter-1]) != (int)floatNumbers[counter-1]) {
			while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters
			printf("%s", "\nWarning - invalid value provided. Please try again.\n"); // print error message
			digCheck = 0; // reset digit check
			n = 0; // reset character count
		}
		else {
			++counter; // increment counter
			n = 0; // reset character count
		}
	}
	
	printf("%s", "\n"); // print line break for formatting

	// for each number, repeat asterisks x number of times equal to the number entered

	for (counter = 1; counter <= 5; counter++) {
		astCount = floatNumbers[counter - 1]; // set the asterisk count equal to the number
		for (i = 1; i <= astCount; i++) { // print the asterisk astCount times
			printf("%s", "*");
		}
		printf("%s", "\n");
	}
	
	printf("%s", "\n"); // print line break for formatting

	system("pause"); // pause results for user to read
	return 0; // exit program
}