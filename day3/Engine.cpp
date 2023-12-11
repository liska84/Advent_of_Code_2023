#include "Engine.hpp"
#include <fstream>
#include <iostream>

std::vector<std::vector<char>> Engine::input;
std::vector<int> Engine::lonely;
std::vector<int> Engine::adjacent;

void printInput(const std::vector<std::vector<char>>& input) {

	int line = 0;

	for (auto &x : input) {
		for (const char &y : x) {
			std::cout << y;
		}
		std::cout << std::endl;
		line++;
	}
}

void Engine::readInput(const std::string& inputFile) {
    std::ifstream file(inputFile);

    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::vector<char> str;
            for (char ch : line) {
                if (ch != '\n')
                    str.push_back(ch);
            }
			input.push_back(str);
        }
        file.close();

		printInput(input);

	}
    else {
        std::cout << "Unable to open file";
    }
}

bool Engine::checker(int startX, int startY, int length) {
	int top = std::max(0, startY - 1);
	int bottom = std::min(static_cast<int>(input.size()) - 1, startY + 1);
	int left = std::max(0, startX - 1);
	int right = std::min(static_cast<int>(input[0].size()) - 1, startX + length);

	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			if (y == startY && x >= startX && x < startX + length)
				continue;
			if (!isdigit(input[y][x]) && input[y][x] != '.') {
				return false;
			}
		}
	}
	return true;
}

void Engine::checkInput() {
	for (int y = 0; y < input.size(); y++) {
		for (int x = 0; x < input[y].size(); x++) {
			std::string num;
			if (isdigit(input[y][x])) {
				num = input[y][x];
				int size = 1;
				while (x + size < input[y].size() && isdigit(input[y][x + size])) {
					num += input[y][x + size];
					size++;
				}
				x += size - 1;
				int number = std::stoi(num);
				if (checker(x - size + 1, y, size)) {
					lonely.push_back(number);
				} else
					adjacent.push_back(number);
			}
		}
	}

//	std::cout << "Lonely Numbers: ";
//	for (const auto& number : lonely) {
//		std::cout << number << " ";
//	}
//	std::cout << std::endl;
//
//	std::cout << "Adjacent Numbers: ";
//	for (const auto& number : adjacent) {
//		std::cout << number << " ";
//	}
//	std::cout << std::endl;
}

int Engine::sum() {
	int s = 0;

	for (auto &num : adjacent)
		s += num;
	return s;
}
