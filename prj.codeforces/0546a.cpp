#include<iostream>

int main() {
	int k, n, w;
	std::cin >> k >> n >> w;
	int count = k * (1 + w) * w / 2;
	if (count > n) {
		std::cout << count - n;
	}
	else {
		std::cout << 0;
	}
}