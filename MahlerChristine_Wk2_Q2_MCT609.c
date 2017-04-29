// Author: Christine Mahler
// MCT609 Assignment 2 - Question 1

// The process of finding the largest number (i.e. the maximum of a group of numbers) 
// is frequently used in computer applications. For example, a program that determines the winner of 
// a sales contest would input the number of units sold by each salesperson.
// The salesperson who sold the most units wins the contest.
// Write a pseudo code program and then a program that inputs a series of 10 numbers
// and determines and prints the largest of the numbers.

#include <stdio.h> // preprocess standard input/output header
#include <limits.h> // proprocess limits header to get INT_MAX constant
#include <math.h> // preprocess math header to get ceiling function

int main(void) 
{
	int counter = 1; // counter as integer type
	float number = 0; // number of units sold as float type
	int largest = 0; // maximum number of units sold as integer type
	int status = 0; // status as integer type for checking for non-integer values
	int c; // variable for getting unsigned character from stdin
	int intMax = INT_MAX; // maximum integer value as integer

	printf("Determine the most units sold!\n"); // program intro

	while (counter <= 10) // counter-controlled loop for 10 numbers
	{
		printf("\nEnter the total number of units sold: "); // prompt user for total number of units sold
		status = scanf("%f", &number); // read total number of units sold as float 

		if (number < -1 || number > intMax || (number < 0 & number != -1) || (status != 1) || ceilf(number) != (int)number) // test for negative values and invalid float values
		{
			while ((c = getchar()) != '\n' && c != EOF); // getchar() function converts stdin to int and loop flushes the unwanted new line that follows last character entered by user 
			printf("%s", "\nWarning: Invalid input.\n"); // print error
		}
		else
		{
			if (number > largest) { // check if number of units entered is greater than largest value
				largest = number; // set largest value to number of units
			}

			counter += 1; // increment counter by 1
		}
	} 

	printf("\nThe maximum number of units sold was: %d\n\n", largest); // display maximum number of units sold
	system("pause"); // pause at end of program so that user can read the result
	return 0; // exit program
}