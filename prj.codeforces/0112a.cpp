#include <iostream>
#include <string>
#include <algorithm>


std::string myToLower(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char chr) { 
		return std::tolower(chr);
		}
	);
	return str;
}

int main() {
	std::string first_string;
	std::string second_string;
	std::cin >> first_string;
	std::cin >> second_string;
	if (myToLower(first_string) > myToLower(second_string)) {
		std::cout << 1;
	}
	else if (myToLower(first_string) < myToLower(second_string)) {
		std::cout << -1;
	}
	else {
		std::cout << 0;
	}
}