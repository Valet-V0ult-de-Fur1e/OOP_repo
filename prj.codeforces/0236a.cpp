#include <iostream>
#include <string>
#include <set>

int main() {
	std::set<char> chars;
	std::string nickname;
	std::cin >> nickname;
	for (int index = 0; index < nickname.size(); ++index) {
		chars.insert(nickname[index]);
	}
	if (chars.size() % 2 == 0) {
		std::cout << "CHAT WITH HER!";
	}
	else {
		std::cout << "IGNORE HIM!";
	}
}