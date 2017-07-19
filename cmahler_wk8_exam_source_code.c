// Author: Christine Mahler
// MCT609 Final Exam

// The purpose of this program is to load rainfall records for several weather stations in Ireland that are either stored in the C:/datasets folder or in another directory as indicated by the user.
// The program will then provide a list of options to process the rainfall records that include:

// 1. Displaying rainfall records by location, year, and month
// 2. Sorting raindays from highest to lowest for a particular location and saving the results to a new file
// 3. Identifying the highest volume of rain for a particular location and displaying the results to the screen
// 4. Identifying wettest location by aggregating the total rainfall since the records began
// 5. Calculating the average number of rain days per month for a particluar location since the records began
// 6. Loading files from a dynamically selected directory
// 7. Reloading the original files
// 8. Exiting the program

// The program will continue to display the menu until the exit option is selected and will handle a maximum of MAX_LOCATIONS locations and MAX_RECORDS records.

#include <stdio.h> // standard input/output header
#include <time.h> // time header for time function
#include <string.h> // string header for comparing strings
#include <stdlib.h> // standard library header for converting strings to integers
#include <dirent.h> // dirent header for reading files from indicated directory (Part B Modification)

#define MAX_STRING 50 // define global variable for max string length
#define MAX_LOCATIONS 10 // define global variable for max locations
#define MAX_RECORDS 10000 // define global variable for max rainfall records

// define location struct with locationNum, locationName, and dateTime variables

struct location {
	unsigned int locationNum;
	char * locationName;
	time_t dateTime;
};

// define rainfall struct with locationNum, year, month, totalRainfall, mostRainfall, and raindays variables

struct rainfall {
	unsigned int locationNum;
	unsigned int year;
	unsigned int month;
	float totalRainfall;
	float mostRainfall;
	int raindays;
};

typedef struct location Location; // define synonym for location struct
typedef struct rainfall Rainfall; // define synonym for rainfall struct

void load_data(const char * files[MAX_LOCATIONS], Location * const locArray, Rainfall * const rainArray, int * records, int * filepaths, int prefixLength); // preprocess load_data function that takes pointers to files, locations, and rainfall records and to a records, filenames, and prefixLength integer and that returns no value
void display_menu(); // preprocess display_menu function that takes no arguments and returns no value
void view_rainfall_year_month(Location * const locArray, Rainfall * const rainArray, int records, int filepaths); // preprocess view_rainfall_year_month function that takes pointers to locations and rainfall records and a records and filenames integer and that returns no value
void sort_raindays_by_year_month(const char * files[MAX_LOCATIONS], Location * const locArray, Rainfall * const rainArray, int records, int filepaths, int prefixLength); // preprocess sort_raindays_by_year_month function that takes pointers to locations and rainfall records and a records, filenames, and prefixLength integer and that returns no value
void highest_volume_rain_one_day(Location * const locArray, Rainfall * const rainArray, int records, int filepaths); // preprocess highest_volume_rain_one_day function that takes pointers to locations and rainfall records and a records and filenames integer and that returns no value
void wettest_location_Ireland(Location * const locArray, Rainfall * const rainArray, int records, int filepaths); // preprocess wettest_location_Ireland function that takes pointers to locations and rainfall records and a records integer and filenames and that returns no value
void average_monthly_rainy_days(Location * const locArray, Rainfall * const rainArray, int records, int filepaths); // preprocess average_monthly_rain_days function that takes pointers to locations and rainfall records and a records and filenames integer and that returns no value
void part_B_unique_query(const char * otherFiles[MAX_LOCATIONS], int * prefixLength, int * filepaths);
void exit_mrda(); // preprocess exit_mrda function that takes no arguments and returns no value

// main function displays menu of options and prompts user for selection, then calls function depending on the selection made

int main(void) {
	char input[MAX_STRING] = { NULL }; // declare and initialize input character array for storing menu selection
	int selection = 0; // declare selection variable for storing converted value of menu selection
	int c; // declare variable for flushing unwanted characters
	Location locations[MAX_LOCATIONS] = { NULL }; // declare and initialize an array of location structs with a max of MAX_LOCATIONS
	Rainfall rainfalls[MAX_RECORDS] = { NULL }; // declare and initialize an array of rainfall structs with a max of MAX_RECORDS
	char * files[5] = { "C:/datasets/BelfastRainfall.txt", "C:/datasets/CorkRainfall.txt", "C:/datasets/DublinRainfall.txt", "C:/datasets/GalwayRainfall.txt", "C:/datasets/LimerickRainfall.txt" }; // declare and initialize an array of pointers to strings for storing hard-coded filename paths
	char * otherFiles[MAX_LOCATIONS] = { NULL }; // declare and initialize an array of pointers to strings for dynamically storing Part B filenames
	int records = 0; // declare and initialize records counter for storing total number of rainfall records loaded in to rainfalls array
	int filepaths = 0; // declare and initialize files counter for storing total number of filepaths
	int * filePrefixLength = 0; // declare and initialize counter for storing file path of Part B file paths

	load_data(&files, locations, rainfalls, &records, &filepaths, 0); // call load_data function with address of files pointers, locations array, rainfalls array, address to records and filepaths counters, and filePrefixLength counter equal to 0
	
	// while the selection is not 7 (exit_mrda), prompt user for menu selection, store input in selection variable, and check for errors / prompt again as necessary

	while (selection != 8) {
		system("cls"); // clear screen
		display_menu(); // call display_menu function

		// display total # of records and files loaded

		printf("\n%s%d%s%d%s\n", "**", records, " total records from ", filepaths, " files loaded.**");

		do {
			memset(input, '\0', sizeof(input)); // reset input array
			selection = 0; // reset selection variable

			printf("\n%s", "Enter a selection #: "); // prompt the user for a menu item
			scanf("%49s", &input); // read the input in to the input variable as a string (in order to test for invalid values)
			while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

			selection = atoi(input); // convert input to integer and assign to selection variable

			// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

			if (strchr(input, '.') != NULL || selection > 8 || selection == 0 || selection < 0) {
				printf("\n%s\n", "ERROR - Invalid entry. Try again.");
			}

		} while (strchr(input, '.') != NULL || selection > 8 || selection == 0 || selection < 0);

		// call functions as determined by menu selection 

		switch (selection) {
		case 1:
			view_rainfall_year_month(locations, rainfalls, records, filepaths); // call view_rainfall_year_month function with locations and rainfalls arrays and records and filenames counter arguments
			break;
		case 2:
			
			// check if Part B files loaded and call function with appropriate arguments

			if (filePrefixLength == 0) {
				sort_raindays_by_year_month(&files, locations, rainfalls, records, filepaths, 0); // call sort_raindays_by_year_month function with address of hardcoded files, locations and rainfalls arrays and records and filenames counter arguments
			}
			else {
				sort_raindays_by_year_month(&otherFiles, locations, rainfalls, records, filepaths, filePrefixLength); // call sort_raindays_by_year_month function with address of Part B files, locations and rainfalls arrays and records and filenames counter arguments
			}
			break;
		case 3:
			highest_volume_rain_one_day(locations, rainfalls, records, filepaths); // call highest_volume_rain_one_day function with locations and rainfalls arrays and records and filenames counter arguments
			break;
		case 4:
			wettest_location_Ireland(locations, rainfalls, records, filepaths); // call wettest_location_Ireland function with locations and rainfalls arrays and records and filenames counter arguments
			break;
		case 5:
			average_monthly_rainy_days(locations, rainfalls, records, filepaths); // call average_monthly_rainy_days function with locations and rainfalls arrays and records and filenames counter arguments
			break;
		case 6:
			part_B_unique_query(&otherFiles, &filePrefixLength, &filepaths); // call part_B_unique_query function with address Part B files, filePrefixLength and filepaths counters 
			records = 0; // reset records counter

			// check if Part B files loaded and call load_data function with appropriate arguments

			if (filePrefixLength == 0) {
				load_data(&files, locations, rainfalls, &records, &filepaths, 0); // call load_data function with address of files pointers, locations array, rainfalls array, address to records and filepaths counters, and filePrefixLength counter equal to 0
				if (filepaths != 0) {
					printf("%s\n\n", "Original data was reloaded successfully."); // display successful reload message
				}
				else {
					printf("%s\n\n", "ERROR - No files loaded."); // display failure message
				}
				system("pause");
			}
			else {
				load_data(&otherFiles, locations, rainfalls, &records, &filepaths, filePrefixLength); // call load_data function with address of Part B files pointers, locations array, rainfalls array, address to records and filepaths counters, and filePrefixLength counter
				if (filepaths != 0) {
					printf("%s\n\n", "Part B files were loaded successfully."); // display successful reload message
				}
				else {
					printf("%s\n\n", "ERROR - No files loaded."); // display failure message
				}
				system("pause");
			}
			break;
		case 7:
			filepaths = 0; // reset filepaths counter
			records = 0; // reset records counter
			filePrefixLength = 0; // reset filePrefixLength counter
			load_data(&files, locations, rainfalls, &records, &filepaths, 0); // reload original data
			printf("\n%s\n\n", "Original data was reloaded successfully."); // display successful reload message
			system("pause"); // pause for user to view results
			break;
		case 8:
			exit_mrda(); // call exit_mrda function to exit program
			break;
		}
	}

	return 0; // exit main function
}

// define function for loading location data in to locations array and rainfall data in to rainfalls array by reading the files indicated

void load_data(const char * files[MAX_LOCATIONS], Location * const locArray, Rainfall * const rainArray, int * records, int * filepaths, int prefixLength) {
	FILE *filePtr; // declare file pointer (for opening and reading files)
	char * file = { NULL }; // declare and initialize file pointer to string (for parsing file for location name)
	int i, j, k; // declare counters for iterating through files and through filepath names
	time_t rawtime; // declare variable for getting current date and time
	char * location = { NULL }; // declare and initialize pointer to string for storing location name
	int maxLoc; // declare variable for storing maxiu
	int maxFiles; // declare variable for storing maximum files loaded

	// check if Part B files loaded (dereferenced filepaths counter will be greater than 0) and set maxFiles variable accordingly
	
	if (*filepaths > 0) {
		maxFiles = *filepaths; // maxFiles for Part B files will be equal to the total number of files loaded
	}
	else {
		maxFiles = sizeof(files) + 1; // maxFiles for original files will be equal to the size of the files array + 1
	}

	// for each hard-coded file, parse the filename for the location, store the location details in the locations array, and then open each file and store each record in the rainfalls array

	for (i = 0; i < maxFiles; i++) {
		if (i > MAX_LOCATIONS - 1) {
			break;
		}
		file = calloc(strlen(files[i]), sizeof(char)); // dynamically allocate memory for the file string
		strcpy(file, files[i]); // copy the i element of the files array to the file pointer
		location = calloc(strlen(files[i]), sizeof(char)); // dynamically allocate memory for the location string

		// check if Part B files loaded (to determine length of filename prefix)

		if (strstr(files[i], "C:/datasets/") != NULL) {
			j = strlen("C:/datasets/"); // reset the j counter to the length of the "C:/datasets/"
		}
		else {
			j = prefixLength + 1; // reset the j counter to the length returned by the part_B_unique_query function
		}

		k = 0; // reset the k counter to 0 (for incrementing through the location string)

		// parse the filename for the location name by starting at the end of the "C:/datasets/" prefix and iterating through until "Rainfall.txt" is reached (equivalent to j + 8 position)

		while (file[j + 8] != '.') {
			location[k] = file[j]; // store location name in location string
			j++; // increment j by 1
			k++; // increment k by 1
		}

		// add records to locations array

		locArray[i].locationName = calloc(k, sizeof(char)); // dynamically allocate memory to the i element of the locArray.locationName array
		strcpy(locArray[i].locationName, location); // copy the parsed location name to the i element of the locArray.locationName array
		locArray[i].locationNum = i + 1; // assign a location number to the i element of the locArray.locationNum array
		locArray[i].dateTime = time(&rawtime); // assign the current date and time to the i element of the locArray.dateTime array

		// add records to the rainfalls array

		filePtr = fopen(files[i], "r"); // open the file
		if (filePtr != NULL) { // check if opening the file was successful
			while (!feof(filePtr) && *records < MAX_RECORDS) { // while the end of the file is not reached
				rainArray[*records].locationNum = locArray[i].locationNum; // assign the location number to the *records element of the rainArray.locationNum array
				// read each respective value in to the dereferenced records element of the rainArray.year, rainArray.month, rainArray.totalRainfall, rainArray.mostRainfall, and rainArray.raindays arrays
				fscanf(filePtr, "%d%d%f%f%d", &rainArray[*records].year, &rainArray[*records].month, &rainArray[*records].totalRainfall, &rainArray[*records].mostRainfall, &rainArray[*records].raindays);
				if (i == 0 && (rainArray[*records].year == NULL || rainArray[*records].month == NULL) && !feof(filePtr)) { // check if first record is NULL (meaning invalid values or empty file)
					(*records) = 0; // reset records count
					(*filepaths) = 0; // reset filepaths count
					maxLoc = 0; // reset maxLoc
					break; // exit loop
				} else if (rainArray[*records].year != NULL && !feof(filePtr)) { // check for blank lines and move to next line if found
					(*records)++; // increment dereferenced records variable by 1
				}
			}
			if (maxFiles == sizeof(files) + 1) {
				(*filepaths)++; // increment dereferenced filepaths variable by 1
			}
			fclose(filePtr); // close file
			free(location); // release memory for location pointer to string
		}
		else {
			maxLoc = 0;
		}
	} 

	// incrememnt through each rainArray record to determine the max location ID (for determining how many files were loaded)

	for (i = 0; i < *records - 1; i++) {
		maxLoc = rainArray[i].locationNum;
		if (rainArray[i].locationNum < rainArray[i + 1].locationNum) {
			maxLoc = rainArray[i + 1].locationNum;
		}
	}

	// check if the dereferenced filepaths variable is greater than the max location ID and change the dereferenced filepaths variable as needed

	if (*filepaths > maxLoc) {
		*filepaths = maxLoc;
	} 

	return; // pop function off call stack and return control to main function
}

// define function for displaying program header and menu on screen

void display_menu() {

	// print program header and menu to screen
	
	printf("\n%s\n", "________________________________Met Eireann Rainfall Data Analysis (MRDA)________________________________");
	printf("%s\n\n", "                                        Choose an Option Below");
	printf("%s%d%s%d%s\n\n", "*NOTE: The program will only load a maximum of ", MAX_LOCATIONS, " files and ", MAX_RECORDS, " records.*");
	printf("%s\n", "1. View Rainfall Information by Year and Month");
	printf("%s\n", "2. Sort Rain Days by Year and Month");
	printf("%s\n", "3. View the Highest Volume of Rain in one day");
	printf("%s\n", "4. View the Wettest Location in Ireland");
	printf("%s\n", "5. View the Average Monthly Rain days");
	printf("%s\n", "6. Part B - MODIFICATION [Process All Files]");
	printf("%s\n", "7. Reload original files."); 
	printf("%s\n", "8. Exit MRDA");

	return; // pop function off call stack and return control to main function
}

// define function for displaying rainfall by location, year, and month

void view_rainfall_year_month(Location * const locArray, Rainfall * const rainArray, int records, int filepaths) {
	char input[MAX_STRING] = { NULL }; // declare and initialize string for storing requested location number that may not be more than MAX_STRING characters 
	int locID; // declare variable for storing converted location number input
	int year; // declare variable for storing requested year
	int month; // declare variable for storing requested month
	char * monthName = { NULL }; // declare and initialize string for storing full month name
	int minYear; // declare variable for storing earliest year in rainfalls array
	int maxYear; // declare variable for storing latest year in rainfalls array
	int minLoc; // declare variable for storing minimum location number (used for error handling of input)
	int maxLoc; // declare variable for storing maximum location number (used for error handling of input)
	int i, j; // declare counters for iterating through rainfall records and locations
	int c; // declare variable for flushing unwanted characters

	// display menu of locations to select from based on what was loaded in to the rainArray

	printf("\n%s\t%s", "ID", "Location Name"); // table header

	// iterate through rainArray

	for (i = 0; i < records; i++) {
		
		// set minLoc equal to the first location number returned
		
		if (i == 0) {
			minLoc = rainArray[i].locationNum;
		}

		maxLoc = rainArray[i].locationNum; // set maxLoc equal to the i element of rainArray.locationNum (will change as loop iterates)
		locID = rainArray[i].locationNum; // set locID equal to the i element of rainArray.locationNum (will be used to determine location name below)
		j = 0; // reset j counter for iterating through locArray

		// to determine location name, iterate through locArray until matching locID found

		while (locID != locArray[j].locationNum) {
			j++; 
		}

		// print unique location numbers and names

		if (i == 0 || maxLoc > rainArray[i - 1].locationNum) {
			printf("\n%d\t%s", locArray[j].locationNum, locArray[j].locationName);
		}
	}	

	// prompt for the location number until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		locID = 0; // reset locID variable

		printf("\n\n%s", "Choose a location (enter location ID or -1 to return to main menu): "); // prompt for location number
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		locID = atoi(input); // convert input to integer and assign to locID variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (locID == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || locID > maxLoc || locID == 0 || locID < 0) {
			printf("\n%s", "ERROR - Invalid entry. Try again.");
		}
	} while (locID == 0 || strchr(input, '.') != NULL || locID > maxLoc || locID < 0);

	// determine earliest year in rainArray by iterating through rainArray until minimum year value found (for error handling in year prompt)

	for (i = 0; i < records; i++) {
		if (i == 0) {
			minYear = rainArray[i].year;
		}
		if (rainArray[i].locationNum == locID && minYear > rainArray[i+1].year) {
			minYear = rainArray[i + 1].year;
		}
	}

	// determine latest year in rainArray by iterating through rainArray until maximum year value found (for error handling in year prompt)

	for (i = 0; i < records; i++) {
		if (i == 0) {
			maxYear = rainArray[i].year;
		}
		if (rainArray[i].locationNum == locID && maxYear < rainArray[i + 1].year) {
			maxYear = rainArray[i + 1].year;
		}
	}

	// prompt for the year until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		year = 0; // reset year variable

		printf("\n%s%d%s%d%s", "Enter a year between ", minYear, " and ", maxYear, " (or -1 to return to main menu): "); // prompt for year
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		year = atoi(input); // convert input to integer and assign to year variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (year == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || year < minYear || year > maxYear  || year == 0) {
			printf("\n%s%d%s%d%s\n", "ERROR - Invalid entry. Only values ", minYear, "-", maxYear, " accepted. Please try again.");
		}
	} while (year == 0 || strchr(input, '.') != NULL || year < minYear || year > maxYear);

	// prompt for the month until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		month = 0; // reset month variable

		printf("\n%s", "Enter a month between 1 and 12 (or -1 to return to main menu): "); // prompt for month
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		month = atoi(input); // convert input to integer and assign to month variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (month == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || month > 12 || month == 0) {
			printf("\n%s\n", "ERROR - Invalid entry. Only values 1-12 accepted. Please try again.");
		}
	} while (month == 0 || strchr(input, '.') != NULL || month > 12);

	// determine full month name for month # provided

	switch (month) {
	case 1:
		monthName = calloc(strlen("January"), sizeof(char));
		monthName = "January";
		break;
	case 2:
		monthName = calloc(strlen("February"), sizeof(char));
		monthName = "February";
		break;
	case 3:
		monthName = calloc(strlen("March"), sizeof(char));
		monthName = "March";
		break;
	case 4:
		monthName = calloc(strlen("April"), sizeof(char));
		monthName = "April";
		break;
	case 5:
		monthName = calloc(strlen("May"), sizeof(char));
		monthName = "May";
		break;
	case 6:
		monthName = calloc(strlen("June"), sizeof(char));
		monthName = "June";
		break;
	case 7:
		monthName = calloc(strlen("July"), sizeof(char));
		monthName = "July";
		break;
	case 8:
		monthName = calloc(strlen("August"), sizeof(char));
		monthName = "August";
		break;
	case 9:
		monthName = calloc(strlen("September"), sizeof(char));
		monthName = "September";
		break;
	case 10:
		monthName = calloc(strlen("October"), sizeof(char));
		monthName = "October";
		break;
	case 11:
		monthName = calloc(strlen("November"), sizeof(char));
		monthName = "November";
		break;
	case 12:
		monthName = calloc(strlen("December"), sizeof(char));
		monthName = "December";
		break;
	}

	i = 0; // reset i counter
	j = 0; // reset j counter

	// iterate through rainArray until matching location number, year, and month is found

	while (rainArray[i].locationNum != locID || rainArray[i].year != year || rainArray[i].month != month) {
		if (i == records) {
			break;
		}
		i++;
	}

	// check if i element of rainArray.locationNum, rainArray.year, and rainArray.month match input provided

	if (rainArray[i].locationNum == locID && rainArray[i].year == year && rainArray[i].month == month) {

		// iterate through locArray until matching location number found

		while (locArray[j].locationNum != locID) {
			j++;
		}

		// print matching record
		
		printf("\n%s%s%s%s%s%d%s\n", "The rainfall records for ", locArray[j].locationName, " for ", monthName, " ", rainArray[i].year, " are as follows:");
		printf("\n%s\t%s\t%s", "Total Rainfall", "Most Rainfall in a Day", "Number of Rainy Days");
		printf("\n%.1f\t\t%.1f\t\t\t%d\n\n", rainArray[i].totalRainfall, rainArray[i].mostRainfall, rainArray[i].raindays);
	}
	else {
		printf("\n%s\n\n", "No records found."); // print "no records found" if no matching records found
	}

	system("pause"); // pause to allow user to view results
	return; // pop function off call stack and return control to main function
}

// define function for sorting raindays from highest to lowest for a particular location and save results to new file

void sort_raindays_by_year_month(const char * files[MAX_LOCATIONS], Location * const locArray, Rainfall * const rainArray, int records, int filepaths, int prefixLength) {
	Rainfall copyRainArray[MAX_RECORDS] = { NULL }; // declare and initialize a copy of the rainArray
	int copyItems = 0; // declare and initialize counter for keeping track of number of copied records
	Rainfall tempRainArray[1] = { NULL }; // declare and intialize a copy of a single rainArray element
	char input[MAX_STRING]; // declare and initialize string for storing requested location number that may not be more than MAX_STRING characters  
	int locID; // declare variable for storing converted location number input
	int minLoc; // declare variable for storing minimum location number (used for error handling of input)
	int maxLoc; // declare variable for storing maximum location number (used for error handling of input)
	char * locationName = { NULL }; // declare and initialize a pointer to a string for storing the location name
	char * filePrefix = { NULL }; // declare and initialize the filename prefix (for saving the sorted array)
	char temp[MAX_STRING] = { NULL }; // declare and initialize string for storing filename prefix for Part B files (for saving the sorted array)
	char * fileSuffix = "_by_rainydays.txt"; // declare and initialize the filename suffix (for saving the sorted array)
	char * fileName = { NULL }; // declare and initialize a pointer to a string for storing the full filename (for saving the sorted array)
	int fileNameSize; // declare for storing full filename size (for saving the sorted array)
	int i, j, k; // declare counters for iterating through the rainArray records and filename characters
	int c; // declare variable for flushing unwanted characters
	FILE * filePtr; // declare file pointer (for opening and writing files)

	// display menu of locations to select from based on what was loaded in to the rainArray

	printf("\n%s\t%s", "ID", "Location Name"); // table header

	// iterate through rainArray

	for (i = 0; i < records; i++) {

		// set minLoc equal to the first location number returned

		if (i == 0) {
			minLoc = rainArray[i].locationNum;
		}

		maxLoc = rainArray[i].locationNum; // set maxLoc equal to the i element of rainArray.locationNum (will change as loop iterates)
		locID = rainArray[i].locationNum; // set locID equal to the i element of rainArray.locationNum (will be used to determine location name below)
		j = 0; // reset j counter for iterating through locArray

		// to determine location name, iterate through locArray until matching locID found

		while (locID != locArray[j].locationNum) {
			j++;
		}

		// print unique location numbers and names

		if (i == 0 || maxLoc > rainArray[i - 1].locationNum) {
			printf("\n%d\t%s", locArray[j].locationNum, locArray[j].locationName);
		}
	}

	// prompt for the location number until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		locID = 0; // reset locID variable

		printf("\n\n%s", "Choose a location (enter location ID or -1 to return to main menu): "); // prompt for location number
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		locID = atoi(input); // convert input to integer and assign to locID variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (locID == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || locID > maxLoc || locID == 0 || locID < 0) {
			printf("\n%s", "ERROR - Invalid entry. Try again.");
		}
	} while (locID == 0 || strchr(input, '.') != NULL || locID > maxLoc || locID < 0);

	// check if Part B files loaded and set filePrefix accordingly

	if (strstr(files[0], "C:/datasets/") != NULL) {
		filePrefix = "C:/datasets/";
	}
	else {
		for (i = 0; i <= prefixLength; i++) {
			temp[i] = files[0][i];
		}
		filePrefix = calloc(prefixLength, sizeof(char));
		strcpy(filePrefix, temp);
	}

	i = 0; // reset i counter
	j = 0; // reset j counter
	k = 0; // reset k counter

	// iterate through locArray until matching location number found

	while (locArray[i].locationNum != locID) {
		i++;
	}

	locationName = calloc(strlen(locArray[i].locationName) + 1, sizeof(char)); // dynamically allocate memory for locationName string
	strcpy(locationName, locArray[i].locationName); // copy i element of locArray.locationName to locationName string
	fileNameSize = strlen(filePrefix) + strlen(locationName) + strlen(fileSuffix) + 1; // set fileNameSize equal to the combined lengths of the filePrefix, locationName, and fileSuffix strings + 1 for the terminating character
	fileName = calloc(fileNameSize, sizeof(char)); // dynamically allocate memory for the fileName string

	// concatenate filePrefix, locationName, and fileSuffix strings

	for (i = 0; i < fileNameSize; i++) {
		if (i < strlen(filePrefix)) {
			fileName[i] = filePrefix[i];
		}
		else if (i < strlen(filePrefix) + strlen(locationName)) {
			fileName[i] = locationName[j];
			j++;
		}
		else {
			fileName[i] = fileSuffix[k];
			k++;
		}
	}

	// copy all rainArray elements with location equal to the input location number to copyRainArray

	for (i = 0; i < records; i++) {
		if (rainArray[i].locationNum == locID) { // check if the location number equals the requested location
			copyRainArray[copyItems]= rainArray[i];
			copyItems++; // increment copyItems by 1 for each record added (to be used in sort)
		}
	}

	// complete bubble sort of copyRainArray by comparing each element to each other and swapping as necessary

	for (i = 0; i < copyItems; i++) {
		for (j = 0; j < copyItems - 1; j++) {
			if (copyRainArray[j].raindays < copyRainArray[j + 1].raindays) {
				tempRainArray[0] = copyRainArray[j];
				copyRainArray[j] = copyRainArray[j + 1];
				copyRainArray[j + 1] = tempRainArray[0];
			}
		}
	}
	
	filePtr = fopen(fileName, "w"); // open file for writing
	if (filePtr == NULL) { // check if opening file was successfull
		printf("\n\n%s\n", "ERROR writing to file."); // print error message if unable to open file
	}
	else {

		// iterate through each sorted copyRainArray element to write record to file

		for (k = 0; k < copyItems; k++) { 
			fprintf(filePtr, "%d\t%d\t%.1f\t%.1f\t%d\n", copyRainArray[k].year, copyRainArray[k].month, copyRainArray[k].totalRainfall, copyRainArray[k].mostRainfall, copyRainArray[k].raindays);
		}

		printf("\n%s%s%s\n\n", "File writing was successful. Please see ", fileName, " for the sorted records."); // display location of file
		fclose(filePtr); // close file
	}

	free(locationName); // release memory for locationName string
	free(fileName); // release memory for fileName string

	system("pause"); // pause to allow user to view results
	return; // pop function off call stack and return control to main function
}

// define function for identifying the highest volume of rain for a particular location and display the results to the screen

void highest_volume_rain_one_day(Location * const locArray, Rainfall * const rainArray, int records, int filepaths) {
	Rainfall copyRainArray[MAX_RECORDS] = { NULL }; // declare and initialize a copy of the rainArray
	int copyItems = 0; // declare and initialize counter for keeping track of number of copied records
	char input[MAX_STRING]; // declare and initialize string for storing requested location number that may not be more than MAX_STRING characters 
	int locID; // declare variable for storing converted location number input
	int minLoc; // declare variable for storing minimum location number (used for error handling of input)
	int maxLoc; // declare variable for storing maximum location number (used for error handling of input)
	float mostRainfall; // declare variable for storing most cumulative 
	int i, j; // declare counters for iterating through locArray and rainArray
	int c; // declare variable for flushing unwanted characters
	
	// display menu of locations to select from based on what was loaded in to the rainArray

	printf("\n%s\t%s", "ID", "Location Name"); // table header

	// iterate through rainArray

	for (i = 0; i < records; i++) {

		// set minLoc equal to the first location number returned

		if (i == 0) {
			minLoc = rainArray[i].locationNum;
		}

		maxLoc = rainArray[i].locationNum; // set maxLoc equal to the i element of rainArray.locationNum (will change as loop iterates)
		locID = rainArray[i].locationNum; // set locID equal to the i element of rainArray.locationNum (will be used to determine location name below)
		j = 0; // reset j counter for iterating through locArray

		// to determine location name, iterate through locArray until matching locID found

		while (locID != locArray[j].locationNum) {
			j++;
		}

		// print unique location numbers and names

		if (i == 0 || maxLoc > rainArray[i - 1].locationNum) {
			printf("\n%d\t%s", locArray[j].locationNum, locArray[j].locationName);
		}
	}

	// prompt for the location number until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		locID = 0; // reset locID variable

		printf("\n\n%s", "Choose a location (enter location ID or -1 to return to main menu): "); // prompt for location number
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		locID = atoi(input); // convert input to integer and assign to locID variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (locID == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || locID > maxLoc || locID == 0 || locID < 0) {
			printf("\n%s", "ERROR - Invalid entry. Try again.");
		}
	} while (locID == 0 || strchr(input, '.') != NULL || locID > maxLoc || locID < 0);

	i = 0; // reset i counter

	// copy all rainArray elements with location equal to the input location number to copyRainArray 

	for (i = 0; i < records; i++) {
		if (rainArray[i].locationNum == locID) { // check if the location number equals the requested location
			copyRainArray[copyItems] = rainArray[i];
			copyItems++; // increment copyItems by 1 for each record added (to be used in sort)
		}
	}

	mostRainfall = copyRainArray[0].mostRainfall; // set the mostRainfall variable equal to the first record of copyRainfalls.mostRainfall

	// iterate through copyRainArray to determine highest volume

	for (i = 0; i < copyItems; i++) {
		if (mostRainfall < copyRainArray[i + 1].mostRainfall) { // check if mostRainfall is less than the subsequent record
			mostRainfall = copyRainArray[i + 1].mostRainfall; // set mostRainfall equal to subsequent record
		}
	}

	printf("\n%s%s%s%.1f%s\n\n", "The highest volume of rain in a single day for ", locArray[locID - 1].locationName, " is: ", mostRainfall, " mm."); // display results to screen

	system("pause"); // pause to allow user to view results
	return; // pop function off call stack and return control to main function
}

// define function to identify wettest location by aggregating total rainfall since records began

void wettest_location_Ireland(Location * const locArray, Rainfall * const rainArray, int records, int filepaths) {
	float cumRainfall[MAX_LOCATIONS] = { 0 }; // declare and initialize array of floats for storing cumulative rainfall per location
	float wettestLocation; // declare float variable for storing max cumulative rainfall out of all locations
	int wettestLocationID = 0; // declare and initialize variable for storing location ID of location with the most cumulative rainfall
	int i, j; // declare counters for iterating through locArray and rainArray

	// for each element of the cumRainfall (equivalent to the location number - 1), calculate the total cumulative rainfall

	for (i = 0; i < filepaths; i++) {
		for (j = 0; j < records; j++) {
			if (rainArray[j].locationNum == (i + 1)) { 
				cumRainfall[i] += rainArray[j].totalRainfall;
			}
		}
	}

	wettestLocation = cumRainfall[0]; // initialize the wettestLocation variable by setting it equal to the first element of the cumRainfall array

	// iterate through the cumRainfall array to identify max cumulative rainfall and associated location number

	for (i = 0; i < filepaths; i++) {
		if (cumRainfall[i] < cumRainfall[i + 1]) {
			wettestLocation = cumRainfall[i + 1];
			wettestLocationID = i + 1;
		}
	}

	// display all locations and total cumulative rainfall for each to screen

	printf("\n%s%20s\t%s", "ID", "Location Name", "Cumulative Rain");
	for (i = 0; i < filepaths; i++) {
		printf("\n%d%20s\t%.0f%s", locArray[i].locationNum, locArray[i].locationName, cumRainfall[i], "mm");
	}

	// display wettest location to screen

	printf("\n\n%s%s%s%.0f%s\n\n", "The wettest location in Ireland is ", locArray[wettestLocationID].locationName, " with a total cumulative rainfall of ", wettestLocation, " mm.");

	system("pause"); // pause to allow user to view results
	return; // pop function off call stack and return control to main function
}

// define function for calculating the average number of rain days per month for a particluar location since the records began

void average_monthly_rainy_days(Location * const locArray, Rainfall * const rainArray, int records, int filepaths) {
	char input[MAX_STRING] = { NULL }; // declare and initialize string for storing requested location number that may not be more than MAX_STRING characters 
	int locID; // declare variable for storing converted location number input
	int minLoc; // declare variable for storing minimum location number (used for error handling of input)
	int maxLoc; // declare variable for storing maximum location number (used for error handling of input)
	float totalDays = 0; // declare and initialize a variable for storing the total number of raindays per location
	int totalRecords = 0; // declare and initialize a variable for storing the total number of records per location
	int i, j; // declare counters for iterating through locArray and rainArray
	int c; // declare variable for flushing unwanted characters

	// display menu of locations to select from based on what was loaded in to the rainArray

	printf("\n%s\t%s", "ID", "Location Name"); // table header

	// iterate through rainArray

	for (i = 0; i < records; i++) {

		// set minLoc equal to the first location number returned

		if (i == 0) {
			minLoc = rainArray[i].locationNum;
		}

		maxLoc = rainArray[i].locationNum; // set maxLoc equal to the i element of rainArray.locationNum (will change as loop iterates)
		locID = rainArray[i].locationNum; // set locID equal to the i element of rainArray.locationNum (will be used to determine location name below)
		j = 0; // reset j counter for iterating through locArray

		// to determine location name, iterate through locArray until matching locID found

		while (locID != locArray[j].locationNum) {
			j++;
		}

		// print unique location numbers and names

		if (i == 0 || maxLoc > rainArray[i - 1].locationNum) {
			printf("\n%d\t%s", locArray[j].locationNum, locArray[j].locationName);
		}
	}

	// prompt for the location number until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input string
		locID = 0; // reset locID variable

		printf("\n\n%s", "Choose a location (enter location ID or -1 to return to main menu): "); // prompt for location number
		scanf("%49s", &input); // read input in to string
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		locID = atoi(input); // convert input to integer and assign to locID variable

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (locID == -1) {
			return;
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if (strchr(input, '.') != NULL || locID > maxLoc || locID == 0 || locID < 0) {
			printf("\n%s", "ERROR - Invalid entry. Try again.");
		}
	} while (locID == 0 || strchr(input, '.') != NULL || locID > maxLoc || locID < 0);


	// calculate the total number of raindays and records per location
	
	for (i = 0; i < records; i++) {
		if (rainArray[i].locationNum == locID) {
			totalDays += rainArray[i].raindays;
			totalRecords++;
		}
	}

	// display the results to the screen

	printf("\n%s%s%s%.0f\n\n", "The average number of raindays per month for ", locArray[locID - 1].locationName, " is: ",  totalDays / totalRecords);
	
	system("pause"); // pause to allow user to view results
	return; // pop function off call stack and return control to main function
}

// define function for loading files from a dynamically selected directory

void part_B_unique_query(const char * otherFiles[MAX_LOCATIONS], int * prefixLength, int * filepaths) {
	char input[MAX_STRING + 2] = { NULL }; // declare and initialize string for storing requested location number that may not be more than MAX_STRING + 2 characters (to handle input > MAX_STRING and prevent buffer overflow issues) 
	int convInput; // declare variable for storing converted directory input (used for sentinel value)
	DIR *directory; // declare pointer to directory
	struct dirent *dir; // declare pointer to directory struct
	char * temp = { NULL }; // declare and initialize a pointer to a string for storing filename (without path because d_name returns only the name of the file and not the full path)
	int lengthError; // declare flag for indicating whether or not the input length exceeded MAX_STRING
	int i; // declare counter for iterating through input and otherFiles array
	int c; // declare variable for flushing unwanted characters

	// prompt for the directory until a valid entry or sentinel value is provided

	do {
		memset(input, '\0', sizeof(input)); // reset input array
		lengthError = 0; // reset lengthError flag

		printf("\n%s", "Enter a directory to read files from (or -1 to return to main menu): "); // prompt the user for a menu item
		scanf("%51s", &input); // read the input in to the input variable as a string (in order to test for invalid values)
		while ((c = getchar()) != '\n' && c != EOF); // flush unwanted characters

		convInput = atoi(input); // convert input to integer and assign to convInput variable (for checking for sentinel value)

		// check for sentinel value and pop function off call stack / return control to main function if entered

		if (convInput == -1) {
			return;
		}

		// check if input length exceeds MAX_STRING and return an error if it does

		if (strlen(input) + 1 > MAX_STRING + 1) {
			printf("\n%s%d%s\n", "ERROR - File path may not be longer than ", MAX_STRING, " characters. Try again.");
			lengthError = 1; // set lengthError flag equal to 1 to prevent next error message from displaying
		}

		// check for invalid input (e.g. float, string, or invalid selection) and return an error if invalid input provided

		if ((directory = opendir(input)) == NULL && lengthError == 0) {
			printf("\n%s\n", "ERROR - Directory does not exist. Try again.");
		}
	} while ((directory = opendir(input)) == NULL || strlen(input) + 1 > MAX_STRING + 1);

	i = 0; // reset i counter

	// iterate through input until terminating character found (for checking if "/" is included at the end of input)

	while (input[i + 1] != '\0') {
		i++;
	}

	// check if "/" is included at the end of input and add as necessary (to avoid errors with filepath names)

	if (input[i] != '/' && i + 1 < MAX_STRING - 2) {
		input[i + 1] = '/';
		*prefixLength = i + 1; // update derefenced prefixLength as needed
	}
	else {
		*prefixLength = i; // update derefenced prefixLength as needed
	}

	i = 0; // reset i counter

	// open directory and check if valid files found- 

	do {
		if ((dir = readdir(directory)) != NULL && strstr(dir->d_name, "Rainfall.txt") != NULL) {
			otherFiles[i] = calloc(strlen(dir->d_name) + *prefixLength, sizeof(char)); // dynamically allocate memory to i element of otherFiles array
			temp = calloc(strlen(dir->d_name) + *prefixLength, sizeof(char)); // dynamically allocate memory to temp
			strcpy(temp, input); // copy input to temp
			strcpy(otherFiles[i], strcat(temp, dir->d_name)); // copy concatenated input and filename to i element of otherFiles array
			i++; // increment i by 1
		}
	} while (dir != NULL);

	closedir(directory); // close directory

	*filepaths = i; // set dereferenced filepaths counter to total number of valid files found

	// check if valid files found

	if (i == 0) {
		*prefixLength = 0; // reset prefixLength
		printf("\n%s\n","No files found in the directory indicated. Reloading original files..."); // display no files found message
	}

	printf("\n"); // print new line for formatting purposes
	return;
}

// define function for exiting program

void exit_mrda() {
	printf("\n%s\n\n", "Cheers!"); // display exit message
	system("pause"); // pause before exiting program
	exit(main); // exit program
}