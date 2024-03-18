#include <iostream>
#include <vector>

int main() {
	int count_users;
	int control_user_id;
	std::cin >> count_users >> control_user_id;
	control_user_id -= 1;
	std::vector<int> user_results;
	for (int index = 0; index < count_users; ++index) {
		int user_result;
		std::cin >> user_result;
		user_results.push_back(user_result);
	}
	int count_of_finalists = 0;
	for (int index = 0; index < count_users; ++index) {
		if (user_results[index] > 0 && user_results[index] >= user_results[control_user_id]) {
			count_of_finalists++;
		}
	}
	std::cout << count_of_finalists;
}