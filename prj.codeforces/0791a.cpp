#include <iostream>

int main() {
	int a, b;
	std::cin >> a >> b;
	int count_years = 0;
	while (a <= b)
	{
		a *= 3;
		b *= 2;
		count_years++;
	}
	std::cout << count_years;
}