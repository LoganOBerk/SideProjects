#pragma once

#include <string>
#include <algorithm>

// Convert a string to lowercase (returns a new string)
std::string toLower(const std::string& s);

// Helper to check if two characters are both spaces (for trimming)
bool BothAreSpaces(char lhs, char rhs);

// Trim leading and trailing whitespace from a string (in-place)
void trim(std::string& s);

// Case-insensitive hash functor for unordered containers
struct CaseInsensitiveHash {
    size_t operator()(const std::string& s) const {
        return std::hash<std::string>()(toLower(s));
    }
};

// Case-insensitive equality comparison functor for unordered containers
struct CaseInsensitiveEqual {
    bool operator()(const std::string& a, const std::string& b) const {
        return toLower(a) == toLower(b);
    }
};
