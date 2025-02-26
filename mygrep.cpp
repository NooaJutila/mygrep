#include<iostream>
#include<string>
#include"mygrep.h"
#include"options.h"
using namespace std;


/*

	--- ARGUMENTS: ---

	NONE:

	the program asks the user for both strings and returns the index of the found string.

	NO -o GIVEN:

	1: <search term> 2: <filename>

	--------

	FIRST:

	-o: options enabled
	after -o:
	l: line numbering ENABLED
	o: occurences ENABLED
	i: capitalization IGNORED
	r: reverse search

	SECOND:
	
	<search term>

	THIRD:

	<filename>

*/

bool lineNumbering = false, occurences = false, ignoreCase = false, reverseSearch = false;

int main(int argc, char * argv[]) {
	string content, searchTerm;

	//	if no arguments are given; essentially increment 1
	if (argc == 1) {
		int index = 0;
		cout << "Give a search string: ";
		getline(cin, searchTerm);
		cout << "Give a string from which to search: ";
		getline(cin, content);
		
		try {
			if (content.length() < 1 || searchTerm.length() < 1) {
				throw runtime_error("Argument is too short (less than 1 character)");
			}
		}
		catch (const runtime_error& error) {
			cerr << "Runtime error: " << error.what() << endl;
		}
		
		index = searchForString(content, searchTerm, 0);
		if (index == 1'000'000'000) {	//	used to indicate unfound search term
			cout << '"' << searchTerm << '"' << " NOT found in " << '"' << content << '"' << '.' << endl;
		}
		else {
			cout << '"' << searchTerm << '"' << " found in " << '"' << content << '"' << " at letter index: " << index << endl;
		}
	}
	
	//	incorrect usage of mygrep, giving instructions
	else if (argc == 2) {
		cout << "./mygrep usage:\n-o: options enabled\nl: line numbering ENABLED\no: occurences ENABLED\ni : capitalization IGNORED\nr : reverse search\nempty arguments: program asks for string and search term\n";
		cout << "--example--\n./mygrep -oloi <search term> <filename>\nno options selected: ./mygrep <search term> <filename>\n./mygrep -> program asks for string and search term during runtime";
		exit(1);
	}

	//	no options are entered and a filename is used for content
	else if (argc == 3) {
		searchTerm = argv[1];
		content = argv[2];
		try {
			searchFromFile(content, searchTerm);
		}
		catch (const runtime_error& error) {
			cerr << "Runtime error: " << error.what() << endl;
		}
		catch (const exception& exception) {
			cerr << "Exception occurred: " << exception.what() << endl;
		}
		catch (...) {
			cerr << "Unknown error occurred" << endl;
		}
	}

	//	running with options enabled
	else if (argc == 4) {
		string options = argv[1];
		searchTerm = argv[2];
		content = argv[3];

		for (int i = 2; i < options.length(); i++) {
			char option = options[i];
			if (options[0] == '-' && options[1] == 'o') {
				switch (option) {
				case 'l':
					lineNumbering = true;
					break;
				case 'o':
					occurences = true;
					break;
				case 'i':
					ignoreCase = true;
					break;
				case 'r':
					reverseSearch = true;
					break;
				default:
					break;
				}
			}
			//	if no options are selected with -o; essentially increment 2
			else {
				cout << "Warning: No options selected!" << endl;
				searchTerm = argv[1];
				content = argv[2];
			}
		}
		try {
			searchFromFile(content, searchTerm);
		}
		catch (const runtime_error& error) {
			cerr << "Runtime error: " << error.what() << endl;
		}
		catch (const exception& exception) {
			cerr << "Exception occurred: " << exception.what() << endl;
		}
		catch (...) {
			cerr << "Unknown error occurred" << endl;
		}
	}


	return 0;
}