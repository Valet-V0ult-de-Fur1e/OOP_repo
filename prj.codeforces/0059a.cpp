#include <iostream>
#include <string>
#include <algorithm>

int main() {
	std::string line;
	int lower_count = 0;
	std::cin >> line;
	for (int index = 0; index < line.size(); ++index) {
		if (std::isupper(line[index])) {
			lower_count++;
		}
	}
	if (lower_count <= line.size() - lower_count) {
		std::transform(line.begin(), line.end(), line.begin(), tolower);
	}
	else {
		std::transform(line.begin(), line.end(), line.begin(), toupper);
	}
	std::cout << line;
}