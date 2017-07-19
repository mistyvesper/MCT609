// Author: Christine Mahler
// MCT Assignment 7 - Question 1

// Write a program that reads in a file containing several lines of text 
// and then prints only those strings that end with the letters ed. The program should do the following:
// a. Prompt the user for the name of a text file(if the file does not exist, display an error message and re - prompt)
// b. Read in a series of strings from the text file and store these in an array of strings, dynamically allocating memory for each element
// c. Loop through the populated string array and find elements that end with the characters "ed"
// d. Display on screen a list of only those strings that end with "ed"

#include <stdio.h> // standard input/output header
#include <string.h> // string header for strcmp, strcpy, tolower, and strrchr functions

#define MAX_FILENAME 50 // define filename size constant
#define MAX_LINES 1000 // define max lines per file
#define MAX_STRING 50 // define max string size per line

void prompt(char **input); // preprocess prompt function for prompting the user for an input file
void lines(const char * file, int * fileLines); // preprocess lines function for input file error handling
void read(const char * file, char * records[MAX_LINES]); // preprocess read function for reading input file
void find(char * records1[MAX_LINES], char * records2[MAX_LINES], int fileLines, int * foundLines); // preprocess find function for locating words that end in "ED"
void display(char * records[MAX_LINES], int foundLines); // preprocess display function to display results to screen

// The main function calls the prompt, lines, read, find, and display functions to search input files for words ending in "ed"
// and then displays those results on the screen. The search was designed to be case-insensitive.

int main(void) {
	char * inputFile = { NULL }; // declare and initialize pointer to string for storing input file name
	int fileLines = 0; // declare fileLines variable for counting total number of records in file
	char * fileRecords[MAX_LINES] = { NULL };  // declare and initialize pointer to string array for storing file records
	char * newFileRecords[MAX_LINES] = { NULL }; // declare and initialize pointer to string array for storing file records ending in "ed"
	int foundLines = 0; // declare foundLines variable for counting total number of records ending in "ed"
	int i; // declare counter for freeing dynamically allocated memory

	// program intro

	printf("%s\n", "####################################### FIND WORDS ENDING IN 'ED' #######################################");
	printf("%s\n\n", "                                            (Enter 0 to Exit)                                           ");

	do {
		fileLines = 0; // reset fileLines variable
		prompt(&inputFile);
		lines(inputFile, &fileLines); 
	} while (fileLines > MAX_LINES); // check if fileLines exceeds maximum # of lines allowed
	
	read(inputFile, &fileRecords); 

	find(fileRecords, newFileRecords, fileLines, &foundLines); 

	// display results

	if (foundLines == 0) {
		printf("\n%s\n\n", "No matching records found."); 
	}
	else {
		printf("\n%s%d%s%d%s\n\n", "The results are in! (", foundLines, " of ", fileLines, " records)");  
		display(newFileRecords, foundLines); 
		printf("\n"); // formatting
	}

	// release dynamically allocated memory

	free(inputFile);
	for (i = 0; i < fileLines; i++) {
		free(fileRecords[i]);
	}
	for (i = 0; i < foundLines; i++) {
		free(newFileRecords[i]);
	}

	// pause before exiting program

	system("pause");
	return 0;
}

// prompt function prompts user to enter input filename and then checks for errors, e.g. filename exceeds MAX_FILENAME 
// characters or if file exists - also allows user to enter sentinel value to exit

void prompt(char **input) {
	char temp[MAX_FILENAME] = { NULL }; // declare and initialize temp array for dynamically allocating memory to input pointer
	int c; // declare variable for flushing unwanted characters

	do {
		memset(temp, '\0', sizeof(temp)); // reset temp array

		printf("%s%d%s%d%s", "Enter input file (filename may not exceed ", MAX_FILENAME, " characters and ", MAX_LINES, " lines): ");
		scanf("%49s", temp);
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters
		
		if (temp[48] != '\0') { // check if input length exceeds MAX_FILENAME
			printf("\n%s%d%s\n\n", "ERROR - Filename exceeds ", MAX_FILENAME, " characters. Try again.");
		}
		
		if (fopen(temp, "r") == NULL && strcmp(temp, "0") != 0 && temp[48] == '\0') { // check if input file exists
			printf("\n%s\n\n", "ERROR - Input file not found. Try again.");
		}
		
		if (strcmp(temp, "0") == 0) { // check if sentinel value entered
			printf("\n%s\n\n", "Goodbye!");
			system("pause");
			exit();
		}
	} while (fopen(temp, "r") == NULL && strcmp(temp, "0") != 0); // check if input file exists or if sentinel value entered


	*input = malloc(strlen(temp) + 1); // dynamically allocate memory to dereferenced input argument
	strcpy(*input, temp); // copy temp pointer to dereferenced input argument 
	
	return;
}

// lines function determines the total number of records in a file and returns an error if it exceeds MAX_LINES

void lines(const char * file, int * fileLines) {
	FILE * filePtr; // declare file pointer for opening file
	char temp[MAX_STRING] = { NULL }; // declare temp array for "flushing" unwanted records

	filePtr = fopen(file, "r"); // open file
	while (!feof(filePtr) && *fileLines < MAX_LINES + 1) { // while end of file is not reached and the total # of records does not exceed MAX_LINES
		fscanf(filePtr, "%50s", &temp); // flush unwanted records in order to move to next line - will read in a different function
		
		if (temp[49] != '\0') { // check if input length exceeds MAX_STRING
			printf("\n%s%d%s\n", "ERROR - File record exceeds ", MAX_STRING, " characters. Exiting program.");
			printf("\n%s\n\n", "Goodbye!");
			system("pause");
			exit();
		}

		(*fileLines)++; // increment dereferenced fileLines variable
	}
	fclose(filePtr); // close file

	if (*fileLines > MAX_LINES) { // check if # of records exceeds MAX_LINES
		printf("\n%s\n\n", "ERROR - Too many lines in file. Try again.");
	}

	return;
}

// read function reads file records in to records array

void read(const char * file, char * records[MAX_LINES]) {
	FILE * filePtr; // declare file pointer for opening file
	char temp[MAX_STRING]; // declare temp array for dynamically allocating memory to records pointer
	int i = 0; // declare and initialize counter for iterating through records pointer

	filePtr = fopen(file, "r"); // open file
	while (!feof(filePtr)) { // while end of line is not reached
		fscanf(filePtr, "%50s", &temp); // read in record to temp array
		records[i] = calloc(strlen(temp) + 1, sizeof(char)); // dynamically allocate memory
		strcpy(records[i], temp); // copy temp array to i element of records pointer
		i++; // increment counter
	}
	fclose(filePtr); // close file

	return;
}

// find function finds records ending in "ed" (not case-sensitive) and copies to new array

void find(char * records1[MAX_LINES], char * records2[MAX_LINES], int fileLines, int * foundLines) {
	char * tempArray[MAX_LINES] = { NULL }; // declare and initialize temp array of pointers for storing copy of records1 pointers with last 2 letters converted to lowercase
	char * comp = "ed"; // comparison string
	int i; // declare counter for iterating through tempArray copies
	int j; // declare counter for iterating through tempArray comparisons
	int k = 0; // declare and initialize counter for iterating through records2 array

	for (i = 0; i < fileLines; i++) {
		tempArray[i] = calloc(strlen(records1[i]) + 1, sizeof(char)); // dynamically allocate memory to i element of tempArray
		strcpy(tempArray[i], records1[i]); // copy i element of records1 to i element of tempArray
		tempArray[i][strlen(tempArray[i]) - 1] = tolower(tempArray[i][strlen(tempArray[i]) - 1]); // convert 2nd to last character of i element to lowercase (last element is '\0')
		tempArray[i][strlen(tempArray[i]) - 2] = tolower(tempArray[i][strlen(tempArray[i]) - 2]); // convert 3rd to last character of i element to lowercase
	}
	
	for (j = 0; j < fileLines; j++) {
		if (strrchr(tempArray[j], 'e') != NULL) { // check if 'e' in tempArray
			if (strcmp(strrchr(tempArray[j], 'e'), comp) == 0) { // check if last occurrence of 'e' character in tempArray returns pointer that is equal to the comp string
				records2[k] = calloc(strlen(records1[j]) + 1, sizeof(char)); // dynamically allocate memory to k element of records2
				strcpy(records2[k], records1[j]); // copy j element of records1 to k element of records2
				(*foundLines)++; // increment dereferenced foundLines variable
				k++; // increment counter
			}
		}
	}

	// release dynamically allocated memory for tempArray

	for (i = 0; i < fileLines; i++) {
		free(tempArray[i]);
	}

	return;
}

// display function displays all records ending in ed by iterating through records array of pointers

void display(char * records[MAX_LINES], int foundLines) {
	int i = 0; // declare and initialize counter for iterating through records array of pointers

	for (i = 0; i < foundLines; i++) {
		printf("%s\n", records[i]); // display i element of records
	}

	return;
}