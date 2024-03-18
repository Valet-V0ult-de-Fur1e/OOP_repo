#include <iostream>
#include <string>
int main() {
	int count_words;
	std::cin >> count_words;
	for (int i = 0; i < count_words; ++i) {
		std::string word;
		std::cin >> word;
		if (word.length() > 10) {
			std::cout << word.front() << word.length() - 2 << word.back() << std::endl;
		}
		else {
			std::cout << word << std::endl;
		}
	}
}