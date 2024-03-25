#include <iostream>
#include <string>

int main() {
	std::string inputLine;
	std::cin >> inputLine;
	int count_1 = 0;
	int count_2 = 0;
	int count_3 = 0;
	for (int index = 0; index < inputLine.size(); ++index) {
		if (inputLine[index] == '1') {
			count_1 += 1;
		}
		if (inputLine[index] == '2') {
			count_2 += 1;
		}
		if (inputLine[index] == '3') {
			count_3 += 1;
		}
	}
	std::string outputLine;
	for (int index = 0; index < count_1; ++index) {
		outputLine += "1+";
	}
	for (int index = 0; index < count_2; ++index) {
		outputLine += "2+";
	}
	for (int index = 0; index < count_3; ++index) {
		outputLine += "3+";
	}
	outputLine.pop_back();
	std::cout << outputLine;
}