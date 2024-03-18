#include <iostream>

int main() {
	int count;
	int result = 0;
	std::cin >> count;
	for (int i = 0; i < count; ++i) {
		int a;
		int b;
		int c;
		std::cin >> a >> b >> c;
		if ((a + b + c) >= 2) {
			result += 1;
		}
	}
	std::cout << result;
}