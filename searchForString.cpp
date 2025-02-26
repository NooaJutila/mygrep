#include<iostream>
#include<cstring>
#include<algorithm>
#include<cctype>
#include "mygrep.h"
#include"options.h"
using namespace std;

int searchForString(string content, string searchTerm) {

	char* contentPtr = &content[0];  // This returns a non-const pointer to the data
	char* searchTermPtr = &searchTerm[0];  // Same for searchTerm

	//	strlen() wants const char* variables and thus they're used. size_t is a type for strlen() and it's an unsigned integer.
	size_t searchTermLength = strlen(searchTermPtr);
	size_t contentLength = strlen(contentPtr);


	//	converts strings to lowercase if user chose so
	if (ignoreCase) {
		for (int i = 0; i < contentLength; i++) {
			*(contentPtr + i) = tolower(*(contentPtr + i));
		}
		for (int i = 0; i < searchTermLength; i++) {
			*(searchTermPtr + i) = tolower(*(searchTermPtr + i));
		}
	}

	//	variable to track how many characters match between the content and the searchterm after
	//	the first character of the search term has been matched to one in the content.
	int matchingCharacters = 0;

	//	this loop iterates over the entire content string
	for (int i = 0; i < contentLength;) {

		//	this for-loop checks if a letter matches with the starting character of the search term
		//	loop ends when the search term has been checked
		if (*(contentPtr + i) == *searchTermPtr) {

			for (int j = 0; j < searchTermLength; j++) {

				//	if so, try to match the rest of the term
				if (*(contentPtr + i) == *(searchTermPtr + j)) {
					matchingCharacters++;
					i++;
				}

				//	if the next letter doesn't match, return i to its pre-loop value,
				//	reset matching characters and break this loop
				else {
					i -= matchingCharacters;
					matchingCharacters = 0;
					break;
				}
			}
		}
		if (matchingCharacters == searchTermLength) {
			//	search term matched, returning with index of first letter
			return i - matchingCharacters;
		}
		i++;
	}
	//	search term not found, returning with 1'000'000'000, unlikely an actual index and used to indicate an unfound search term
	return 1'000'000'000;
}