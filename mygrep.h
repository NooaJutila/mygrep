#pragma once
#include <string>
using namespace std;
int searchForString(string content, string searchTerm);
void searchFromFile(string content, string searchTerm);
class Exception : public exception{
private:
	string message;
public:
	Exception(const string& msg);
	const char* what() const noexcept override;
};