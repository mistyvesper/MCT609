// Author: Christine Mahler
// MCT Assignment 6 - Question 1

// Write a program, called "sort_file", which takes a text file as input and produces an output file which 
// has all the original lines in alphabetical order. The program should do the following:
// Prompt the user for the names of the input and output files. You can prepare an input file with appropriate unsorted data.
// A simple file with one word per line will suffice.
// Declare and define three functions to perform the following tasks :
//  	Read the data from the input file into an array.
//		Sort the array using the bubble sort algorithm.
//		Write the sorted data array to the output file.

#include <stdio.h> // standard input/output header
#include <string.h> // string header for strcmp and strcpy functions
#include <ctype.h> // ctype header for getchar function

#define FILENAME_SIZE 50 // define filename size constant 
#define MAX_LINES 50 // define max lines per file
#define MAX_STRING 50 // define max string size per line

void lines(const char * file, int * fileLines); // preprocess lines function for input file error handling
void read(const char * file, char array[MAX_LINES][MAX_STRING], int * fileLines); // preprocess read function for reading input file
void bubbleSort(char array[MAX_LINES][MAX_STRING], int fileLines); // preprocess bubble sort function for sorting input file values
void write(const char * file, char array[MAX_LINES][MAX_STRING], size_t size); // preprocess write function for writing sorted array to new file

int main(void) {
	const char * filesPtr[2] = { NULL }; // declare and initiliaze array of pointers to filename strings
	char inputFile[FILENAME_SIZE] = { NULL }; // declare and initialize inputFile array of size SIZE
	char outputFile[FILENAME_SIZE] = { NULL }; // declare and initialize outputFile array of size SIZE
	char fileArray[MAX_LINES][MAX_STRING] = { NULL }; // declare and initialize 2D fileArray for storing values returned by read function
	int fileLines = 0; // declare and initialize fileLines counter for input file error handling, bubbleSort and write functions
	int c; // declare variable for flushing unwanted characters

	FILE *filePtr; // declare pointer to file
	
	filesPtr[0] = inputFile; // set first element of filename pointers array to input file
	filesPtr[1] = outputFile; // set second element of filename pointers array to output file

	// program introduction
	
	printf("%s", "________________________________READ, SORT, AND WRITE FILES________________________________\n");
	printf("%s", "                                      Enter 0 to Quit                                      \n\n");

	// do while loop first prompts user for input file name and then returns errors (or exits) until valid input provided

	do {
		printf("%s%d%s%d%s", "Enter input file (no more than ", FILENAME_SIZE, " characters or ", MAX_LINES, " records per file allowed): "); // prompt user for input file name
		scanf("%50s", inputFile); // read input string in to inputFile variable with 50 character limitation
		while ((c = getchar()) != '\n' && c != EOF); // fflush unwanted characters

		if (strcmp(inputFile, "0") == 0) { // check if sentinel value passed
			printf("%s", "\nGoodbye!\n\n");
			system("pause");
			exit();
		}
		if (inputFile[49] != '\0') { // check filename size
			printf("%s", "\nERROR - Filename too large. Try again.\n\n");
			memset(inputFile, 0, sizeof(inputFile)); // clear array values
		}
		else {
			if (fopen(inputFile, "r") == NULL) { // check if file exists
				printf("%s", "\nERROR - Input file not found. Try again.\n\n");
			}
			else {
				fileLines = 0; // reset fileLines variable for multiple iterations
				lines(filesPtr[0], &fileLines); // call lines function to determine total number of records in file
				if (fileLines < 2) { // check if no records
					printf("%s", "\nERROR - File must have at least 2 records. Try again.\n\n");
				}
				if (fileLines > MAX_LINES) { // check if records 
					printf("%s", "\nERROR - File has too many records. Try again.\n\n");
				}
			}
		}
	} while (fopen(inputFile, "r") == NULL || fileLines < 2 || fileLines > MAX_LINES || inputFile[49] != '\0'); // check for invalid conditions 

	// do while loop prompts user for output file name and then returns an error (or exits) until valid input provided

	do {
		printf("%s%d%s", "\nEnter output file (no more than ", MAX_STRING, " characters allowed, must be different than input file): "); // prompt user for output file name
		scanf("%49s", outputFile); // read output string in to inputFile variable with 50 character limitation
		while ((c = getchar()) != '\n' && c != EOF); // fflush unwanted characters

		if (outputFile[48] != '\0') { // check filename size
			printf("%s", "\nERROR - Filename too large. Try again.\n");
			memset(outputFile, '\0', sizeof(outputFile)); // clear array values
		}
		else {
			if (strcmp(outputFile, "0") == 0) { // check if sentinel value passed
				printf("%s", "\nGoodbye!\n\n");
				system("pause");
				exit();
			}
			if (strcmp(inputFile, outputFile) == 0) { // check if input file name match
				printf("%s", "\nERROR - Same as input file. Enter a different destination.\n");
			}
		}
	} while (strcmp(inputFile, outputFile) == 0 || outputFile[48] != '\0' || outputFile[0] == '\0'); // check for invalid conditions 

	fileLines = 0; // reset fileLines variable for read function
	
	read(filesPtr[0], fileArray, &fileLines); // call read function with input file name (in pointers array), 2D array for storing values, and address of fileLines variable for call-by-reference
	bubbleSort(fileArray, fileLines); // call bubbleSort function with unsorted 2D array and total number of records in file
	write(filesPtr[1], fileArray, fileLines); // call write function with output file name (in pointers array), sorted 2D array, and total number of records in file

	// program closing message

	printf("%s", "\n_____________________________________Actions Complete!_____________________________________\n\n");

	system("pause"); // pause for user to see status
	return 0; // exit program
}

// lines function takes pointer to file name and pointer to fileLines arguments, returns nothing (void) to main function
// function is used to determine total number of records in file for use in error handling with MAX_LINES file limit

void lines(const char * file, int * fileLines) {
	
	char temp[MAX_STRING] = { NULL }; // declare and initialize temporary value for storing lines read
	FILE *filePtr; // declare pointer to file

	filePtr = fopen(file, "r"); // open file

	// while the end of file has not been reached, read in each line and store in temp value (not to be used elsewhere), 
	// increment dereferenced fileLines value by 1 to get total number of fileLines
	
	while (!feof(filePtr)) {
		fscanf(filePtr, "%50s", &temp);
		if (temp[49] != '\0') { // check record size
			printf("%s%d%s", "\nERROR - Encountered record more than ", MAX_STRING, " characters long. Exiting Program.\n\n");
			memset(temp, '\0', sizeof(temp)); // clear array values
			system("pause");
			exit();
		}
		(*fileLines)++;
	}

	fclose(filePtr); // close file
	return; // pop function (and variables) off call stack and return control to main function
}

// read function takes pointer to file name, array of strings, and pointer to fileLines arguments, returns nothing (void) to main function
// function is used to read file records in to array of strings for sorting purposes

void read(const char * file, char array[MAX_LINES][MAX_STRING], int * fileLines) {
	
	size_t i = 0; // declare and initialize counter for iterating through array of strings
	FILE *filePtr; // declare pointer to file

	filePtr = fopen(file, "r"); // open file

	// while the end of file has not been reached, read in each line and store in array of strings (limited to 50 characters), 
	// increment dereferenced fileLines value by 1 to get total number of fileLines
	
	while (!feof(filePtr)) {
		fscanf(filePtr, "%50s", array[i]);
		i++;
		(*fileLines)++;
	}

	fclose(filePtr); // close file
	return; // pop function (and variables) off call stack and return control to main function
}

// bubbleSort function takes array of strings and fileLines arguments, returns nothing (void) to main function
// function is used to sort file records with lowercase taking precedence over uppercase characters

void bubbleSort(char array[MAX_LINES][MAX_STRING], int fileLines) {

	size_t i; // declare counter for iterating through various arrays, e.g. passes
	size_t j = 0; // declare second counter for secondary iterations through arrays, e.g. comparisons
	char arrayHold[MAX_STRING]; // declare variable for holding unaltered string for swapping purposes
	char casesHold[MAX_STRING]; // declare variable for holding all lowercases string for swapping purposes
	int mixedCaseHold; // declare int variable for holding total # of uppercases in string for swapping purposes
	char cases[MAX_LINES][MAX_STRING]; // declare 2D array of altered strings (all lowercase)
	int mixedCase[MAX_LINES] = { 0 }; // declare int array for storing total # of uppercases in strings

	// make a copy of original array argument and convert all words to lowercase
	
	for (i = 0; i <= fileLines; i++) {

		strcpy(cases[i], array[i]); // copy i element of array argument to i element of cases array

		while (cases[i][j] != 0) {
			if (isupper(cases[i][j]) > 0) {
				mixedCase[i]++; // increment mixedCase value each time uppercase is found
				cases[i][j] = tolower(cases[i][j]); // convert uppercase character to lowercase
			}
			j++; 
		}
		j = 0; // reset counter for multiple passes
	}

	// iterate through cases array and swap values as needed

	for (i = 0; i <= fileLines; i++) {
		
		for (j = i + 1; j <= fileLines - 1; j++) {

			// swap array elements if case elements equal and if first case element is greater than second case element (using strcmp function)
			// this is to specifically handle sorting of elements like "one" "ONE" and "oNe" where "oNe" would follow "one" and "ONE" would follow "oNe"

			if (strcmp(cases[i], cases[j]) == 0 && mixedCase[i] > mixedCase[j]) {
				
				// array swaps for original values
				
				strcpy(arrayHold, array[i]);
				strcpy(array[i], array[j]);
				strcpy(array[j], arrayHold);

				// case swaps for lowercases copy (all elements within each array need to stay in same position with relation to original array)

				strcpy(casesHold, cases[i]);
				strcpy(cases[i], cases[j]);
				strcpy(cases[j], casesHold);

				// mixedCase swaps for mixed cases total (again, all elements within each array need to stay in same position with relation to original array)

				mixedCaseHold = mixedCase[i];
				mixedCase[i] = mixedCase[j];
				mixedCase[j] = mixedCaseHold;
			}

			// swap array elements if first case element is greater than second case element (using strcmp function)

			if (strcmp(cases[i], cases[j]) > 0) {

				// array swaps for original values

				strcpy(arrayHold, array[i]);
				strcpy(array[i], array[j]);
				strcpy(array[j], arrayHold);

				// case swaps for lowercases copy (all elements within each array need to stay in same position with relation to original array)
				
				strcpy(casesHold, cases[i]);
				strcpy(cases[i], cases[j]);
				strcpy(cases[j], casesHold);

				// mixedCase swaps for mixed cases total (again, all elements within each array need to stay in same position with relation to original array)

				mixedCaseHold = mixedCase[i];
				mixedCase[i] = mixedCase[j];
				mixedCase[j] = mixedCaseHold;
			}
		}
	}

	return; // pop function (and variables) off call stack and return control to main function
}

// write function takes pointer to file name, sorted array of strings, and fileLines arguments, returns nothing (void) to main function
// function is used to write sorted array to output file as indicated

void write(const char * file, char array[MAX_LINES][MAX_STRING], size_t size) {

	size_t i = 0; // declare and initialize counter for iterating through array elements
	char temp[MAX_STRING]; // declare temporary string for writing values to file
	FILE *filePtr; // declare pointer to file

	filePtr = fopen(file, "w"); // open file

	// iterate through each array element, copy string to temp variable, then write to file

	for (i = 0; i < size; i++) {
		strcpy(temp, array[i]);
		fprintf(filePtr, "%s\n", temp);
	}

	fclose(filePtr); // close file
	return; // pop function (and variables) off call stack and return control to main function
}