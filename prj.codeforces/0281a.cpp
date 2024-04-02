#include <string>
#include <iostream>

int main() {
	std::string company_name;
	std::cin >> company_name;
	company_name[0] = towupper(company_name[0]);
	std::cout << company_name;
}