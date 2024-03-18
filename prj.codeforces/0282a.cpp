#include <iostream>
#include <string>

int main() {
	int count_lines = 0;
	int value_of_x = 0;
	std::cin >> count_lines;
	for (int line_index = 0; line_index < count_lines; ++line_index) {
		std::string line;
		std::cin >> line;
		if (line == "++X" || line == "X++") {
			value_of_x += 1;
		}
		if (line == "--X" || line == "X--") {
			value_of_x -= 1;
		}
	}
	std::cout << value_of_x;
}