#include <iostream>
#include <string>

int main() {
	int lenght;
	std::string line;
	std::cin >> lenght >> line;
	int out = 0;
	for (int index = 1; index < lenght; ++index) {
		if (line[index - 1] == line[index]) {
			out++;
		}
	}
	std::cout << out;
}