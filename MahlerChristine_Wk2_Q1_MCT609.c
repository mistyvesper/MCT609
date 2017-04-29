// Author: Christine Mahler
// MCT609 Assignment 2 - Question 1

// One large chemical company pays its salespeople on a commission basis.
// The salespeople receive $200 per week plus 9% of their gross sales for that week.
// For example, a salesperson who sells $5000 worth of chemicals in a week receives $200 plus 9% of $5000, or a total of $650.
// Develop a program that will input each salesperson’s gross sales for last week
// and will calculate and display that salesperson's earnings.
// Process one salesperson's figures at a time.

#include <stdio.h> // preprocess standard input/output header
#include <float.h> // proprocess float header to get FLT_MAX constant

int main(void) // main function returns integer value, does not receive a value
{
	float gross = 0; // gross sales as float type
	float total = 0; // total salary as float type
	int status; // status as integer type for checking for non-float values
	int c; // variable for getting unsigned character from stdin
	const float percentage = 0.09; // percentage commission as float type
	const float flat = 200; // flat weekly earnings as float type
	const float maxFloat = FLT_MAX; // max float value as float type

	printf("Calculate your total weekly earnings!\n\n"); // program intro

	while (gross != -1) {
		printf("Enter sales in dollars (-1 to end): $"); // prompt user for total gross sales
		status = scanf("%f", &gross); // read gross sales and assign to status variable
		if (gross < -1 || gross > maxFloat || (gross < 0 & gross != -1 || status != 1)) // test for negative values and invalid float values
		{
			while ((c = getchar()) != '\n' && c != EOF); // getchar() function converts stdin to int and loop flushes the unwanted new line that follows last character entered by user 
			printf("%s", "\nWarning: Invalid input.\n\n"); // print error
		}
		else
		{
			total = flat + gross * percentage; // calculate total weekly salary
			printf("\nSalary is: $%.2f\n\n", total); // display total weekly salary with precision of 2 decimal points
		}
	}
	
	printf("Goodbye!");
	return 0; // exit program
}
