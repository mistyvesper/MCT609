// Author: Christine Mahler
// MCT609 Assignment 4 - Question 2

// The factorial of a non-negative integer n, written as n!, is a mathematical calculation
// that is the product of all positive integers less than or equal to n.  
// The calculation of factorials is one of the example of the use of recursion.
// The calculation can be written as n!= n * (n - 1) * (n - 2) * … 1
// where 1! = 1, and 0! is defined to be 1 as well.

// In this exercise, you will be using factorials to calculate a mathematical series.
// Perform the following steps for this exercise:
// 1.	One of the tenets of modern Software Engineering is code reuse. 
// There are many instances of functions that implement the factorial schema on the Internet.
// Locate a recursive instance , code it and test it.
// 2.	Use the factorial function to calculate the series: e = 1 / 0!+ 1 / 1!+ 1 / 2!+ 1 / 3!+ … for 20 terms.
// 3.	Write the same series calculation using an iterative loop of your choice.
// 4.	Instrument your code to measure time for the recursive and iterative loop methods to calculate the first 20 terms of the series.
// 5.	Present your timing results.
// 6.	Based on your timing results, comment on the quote: ”Would any of you very experienced programmers, 
// if asked to code an iterative loop (like a mathematical series), think of using recursion or would that be a ‘mistake’
// that a rookie programmer would leap to?”


#include <stdio.h> // standard input/output header
#include <time.h> // time header for clock() function
#include <math.h> // math header for ceiling function
#include <limits.h> // limits header for CHAR_MAX constant
#include <stdlib.h> // standard library header for atof() function
#include <ctype.h> // ctype header for isdigit() function

double factorial(double num); // preprocess factorial function

int main(void) {
	
	char charIterations[1][CHAR_MAX]; // declare string array for indicating total # of passes to be performed
	float floatIterations[1] = { 1 }; // declare and initialize float array for indicating total # of passes to be performed
	double counter = 0;  // declare and initialize counter as double for recursion and iteration
	double recursiveSeries = 0; // declare and intialize recursiveSeries as double
	double iterativeSeries = 0; // declare and initialize iterativeSeries as double
	clock_t recursiveStart; // declare recursive start time
	clock_t recursiveEnd; // declare recursive end time
	clock_t iterativeStart; // declare iterative start time
	clock_t iterativeEnd; // declare iterative end time
	double recursiveTotal; // declare recursive total time to process variable as double
	double iterativeTotal; // declare iterative total time to process variable as double
	double i; // declare counter variable for use in for loop in iterative code
	double fact; // declare factorial variable as double for storing iterative factorial results 
	int status; // declare status variable for storing result of scanf function
	int c; // declare variable for stdin flushing
	int n; // declare counter for iterating through each input character
	int digCheck; // declare digit check flag for checking contents of input string

	// program intro
	
	printf("%s", "Compare and contrast Euler's number calculation using recursion versus iteration!\n"); 

	// prompt user for # of iterations and read input

	while (floatIterations[1] != 0) {
		printf("%s", "\nEnter total number of iterations to perform (between 1 and 2000, 0 to exit): \n");
		status = scanf("%s", &charIterations[0]); // read input in to string array
		if (atof(charIterations[0]) == 0) { // convert to float, set to 1 if conversion fails
			floatIterations[0] == 1;
		}
		else {
			floatIterations[0] = atof(charIterations[0]);
		}

		n = 0; // reset digit check flag
		digCheck = 0; // reset counter for iterating through each input character

	// check each character of input string to determine if invalid input entered 

		while (charIterations[0][n] != '\0') {  // while character in string is not equal to end of string
			if (isdigit(charIterations[0][n]) == 0) { // use isdigit function to check if value is integer
				digCheck = 1; // set digCheck flag = 1 if NOT equal to an integer
			}
			n++; // increment counter
		}
	
	// check for sentinel value and exit if found
		
		if (strcmp(charIterations[0], "0") == 0) {
			printf("Goodbye!\n");
			return 0;
		}

	// check for invalid values and prompt for input again

		if (status == 0 || floatIterations[0] <= 0 || floatIterations[0]  > 2000 || ceil(floatIterations[0]) != (int)floatIterations[0] || digCheck == 1) {
			while ((c = getchar()) != '\n' && c != EOF); // fflush unwanted characters
			printf("%s", "\nWarning - invalid value provided. Please try again.\n");
		}
		else {

	// initialize calculations

			printf("\nCalculating...\n\n");

	// recursive calculations

			recursiveStart = clock(); // set start time

			while (counter < floatIterations[0]) {
				recursiveSeries = recursiveSeries + 1 / factorial(counter); // calculate series
				counter++; // increment counter
			}

			recursiveEnd = clock(); // set end time
			recursiveTotal = (double)(recursiveEnd - recursiveStart); // calculate total time to process

	// iterative calculations
			
			counter = floatIterations[0]; // reset counter

			iterativeStart = clock(); // set start time

			while (counter >= 0) {

				if (counter == 0) {
					fact = 1; // reset fact
				}
				else {
					fact = counter; // reset fact
				}

				for (i = counter; i >= 0; --i) {

					if (i == 0 || i == 1) {
						fact = fact * 1; // calculate factorial
					}
					else {
						fact = fact * (i - 1); // calculate factorial
					}
				}
				iterativeSeries = iterativeSeries + 1 / fact; // calculate series
				--counter; // decrement counter
			}

			iterativeEnd = clock(); // set end time
			iterativeTotal = (double)(iterativeEnd - iterativeStart); // calculate total time to process

	// print results to screen
			
			printf("The value of Euler's number using recursion is: %2f\n", recursiveSeries);
			printf("The total time to calculate Euler's number using recursion is: %.0f seconds\n\n", recursiveTotal);
			printf("The value of Euler's number using iteration is: %2f\n", iterativeSeries);
			printf("The total time to calculate Euler's number using recursion is: %.0f seconds\n", iterativeTotal);

	// reset values

			counter = 0;
			recursiveSeries = 0;
			iterativeSeries = 0;

		}
	}
	
	system("pause"); // pause to allow user to view results
	return 0; // exit program

}

// define factorial recursive function

double factorial(double num) {
	if (num == 0 || num == 1) {
		return 1;
	}
	else {
		return (num * factorial(num - 1));
	}
}