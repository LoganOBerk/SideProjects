#include <iomanip>

#include "Math.util.h"

//INPUT: m, an integer dividend; n, an integer divisor
//OUTPUT: the modulus result, always non-negative
//PRECONDITION: n is non-zero
//POSTCONDITION: returns a non-negative result of m mod n
int modulus(const int& m, const int& n) {
	if (n == 0) throw std::invalid_argument("Modulus divisor cannot be zero");
	if (n < 0) throw std::invalid_argument("Modulus divisor cannot be negative");
	if (n >= std::numeric_limits<int>::max()) throw std::out_of_range("Modulus divisor too large");
	if (m >= std::numeric_limits<int>::max()) throw std::out_of_range("Modulus dividend too large");
	if (m <= std::numeric_limits<int>::min()) throw std::out_of_range("Modulus dividend too small");
	return ((m % n) + n) % n;
}
