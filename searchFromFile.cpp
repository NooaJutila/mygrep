#include<iostream>
#include<fstream>
#include "mygrep.h"
#include"options.h"
using namespace std;

void searchFromFile(string content, string searchTerm) {
	ifstream contentFile(content);

	if (!contentFile) {
		throw runtime_error("Failed to open file: " + content);
	}


	string line;
	int lineNumber = 0, index = 0, lineCount = 0;

	while (getline(contentFile, line)) {

		if (contentFile.fail()) { // Check for read errors
			throw runtime_error("Issue reading from file: " + content);
		}

		index = searchForString(line, searchTerm);
		++lineNumber;

		//	if term is found, display it
		if (index != 1'000'000'000) {	//	1'000'000'000 is used to indicate unfound search term
			if (!reverseSearch) {
				if (lineNumbering) {
					cout << lineNumber << ":\t" << line << endl;
				}
				else {
					cout << line << endl;
				}
				++lineCount;
			}
		}

		// if term is NOT found, display it if reverse is on
		else if(index == 1'000'000'000) {
			if (reverseSearch) {
				if (lineNumbering) {
					cout << lineNumber << ":\t" << line << endl;
				}
				else {
					cout << line << endl;
				}
			}
		}
	}

	if (occurences) {
		cout << endl << "Occurences of lines containing " << '"' << content << '"' << ": " << lineCount << endl;
	}
	else if (occurences && reverseSearch) {
		cout << endl << "\tOccurences of lines NOT containing " << '"' << content << '"' << ": " << lineNumber-lineCount << endl;
	}

	if (contentFile.bad()) {
		throw runtime_error("IO error while reading file: " + content);
	}

	contentFile.close();
}