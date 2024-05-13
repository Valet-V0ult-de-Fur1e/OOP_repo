#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

int main() {
    std::vector<std::tuple<std::string, int>> appCache {};
    std::vector<int> appStack(1000);
    int indexCommandLine = 0;

    std::ifstream ifstrm("input.in");
    if (ifstrm.is_open()) {
        std::string command;
        int value;
        while (ifstrm >> command >> value)
        {
            std::tuple<std::string, int> commandLine {command, value};
            appCache.push_back(commandLine);
            indexCommandLine ++;
        }
    }
    ifstrm.close();
}