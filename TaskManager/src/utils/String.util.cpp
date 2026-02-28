#include "String.util.h"

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
std::string toLower(const std::string& s) {
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return result;
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
bool BothAreSpaces(char lhs, char rhs) {
	return (lhs == rhs) && (lhs == ' ');
}

//INPUT: 
//OUTPUT: 
//PRECONDITION: 
//POSTCONDITION: 
void trim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
	std::string::iterator new_end = std::unique(s.begin(), s.end(), BothAreSpaces);
	s.erase(new_end, s.end());
}

