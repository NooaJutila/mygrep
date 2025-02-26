#include<iostream>
#include<fstream>
#include"mygrep.h"
#include"options.h"
using namespace std;

Exception::Exception(const string& msg) : message(msg){}

const char* Exception::what() const noexcept {
	return message.c_str();
}

void searchFromFile(string content, string searchTerm) {
	ifstream contentFile(content);
	try {
		if (!contentFile) {
			throw Exception("Failed to open file: " + content);
		}
	}
	catch (const Exception& exception) {
		cerr << "Exception occurred: " << exception.what() << endl;
		exit(-1);
	}

	string line;
	int lineNumber = 0, index = 0, lineCount = 0;

	while (getline(contentFile, line)) {
		++lineNumber;

		try {
			if (contentFile.fail()) { // Check for read errors
				throw runtime_error("Issue reading from file: " + content);
			}
		}
		catch (const runtime_error& error) {
			cerr << "Runtime error occurred: " << error.what() << endl;
		}

		index = searchForString(line, searchTerm);

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

	if (occurences && !reverseSearch) {
		cout << endl << "Occurences of lines containing " << '"' << searchTerm << '"' << ": " << lineCount << endl;
	}
	else if (occurences && reverseSearch) {
		cout << endl << "\tOccurences of lines NOT containing " << '"' << searchTerm << '"' << ": " << lineNumber-lineCount << endl;
	}
	try {
		if (contentFile.bad()) {
			throw Exception("IO error while reading file: " + content);
		}
	}
	catch (const Exception& exception) {
		cerr << "Exception occurred: " << exception.what() << endl;
		exit(-1);
	}

	contentFile.close();
}