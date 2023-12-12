#include "Engine.hpp"
#include <fstream>
#include <iostream>

std::vector<std::vector<char>> Engine::input;
std::vector<int> Engine::lonely;
std::vector<int> Engine::adjacent;
std::vector<int> Engine::adjacentMultiplications;

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

int Engine::sum(std::vector<int> vector) {
	int s = 0;

	for (auto &num : vector)
		s += num;
	return s;
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
	std::cout << sum(adjacent) << std::endl;
}

bool Engine::isAsteriskNear(int i, int j, int k, int r, int c) {
	for(int a = std::max(0, j - 1); a < std::min(c, k + 1); ++a) {
		if(i - 1 >= 0 && input[i - 1][a] == '*')
			return true;
		if(input[i][a] == '*')
			return true;
		if(i + 1 < r && input[i + 1][a] == '*')
			return true;
	}
	return false;
}

void Engine::processInput() {
	int r = input.size();
	int c = input[0].size();
	std::vector<std::vector<int>> adjs(r * c);

	for(int i = 0; i < r; ++i) {
		int j = 0;
		while(j < c) {
			if(!isdigit(input[i][j])) {
				j++;
				continue;
			}
			int k = j;
			int numval = 0;
			while(k < c && isdigit(input[i][k])) {
				numval = 10 * numval + (input[i][k] - '0');
				k++;
			}
			if(isAsteriskNear(i, j, k, r, c)) {
				for(int a = std::max(0, j - 1); a < std::min(c, k + 1); ++a) {
					if(i - 1 >= 0 && input[i - 1][a] == '*') {
						adjs[(i - 1) * c + a].push_back(numval);
					}
					if(input[i][a] == '*') {
						adjs[i * c + a].push_back(numval);
					}
					if(i + 1 < r && input[i + 1][a] == '*') {
						adjs[(i + 1) * c + a].push_back(numval);
					}
				}
			}
			j = k;
		}
	}
	for(auto & adj : adjs) {
		if(adj.size() == 2) {
			adjacentMultiplications.push_back(adj[0] * adj[1]);
		}
	}
	std::cout << sum(adjacentMultiplications) << std::endl;
}
