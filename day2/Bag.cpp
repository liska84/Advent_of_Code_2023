#include "Bag.hpp"

std::vector<std::map<int, std::vector<std::unordered_map<std::string, int>>>> Bag::data;
std::map<int, std::map<std::string, int>> Bag::power;

const std::map<std::string, int> bag = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

void Bag::parseString(const std::string& line) {
    std::istringstream iss(line);
    std::string game;

    std::getline(iss, game, ':');
    std::istringstream ns(game.substr(game.find_last_of(' ') + 1));
    int gameNumber;
    ns >> gameNumber;

    std::map<int, std::vector<std::unordered_map<std::string, int>>> gameData;
    std::vector<std::unordered_map<std::string, int>> tryouts;

    std::string subset;
    while (std::getline(iss, subset, ';')) {
        std::istringstream ss(subset);
        std::string pair;
        std::unordered_map<std::string, int> colorOccurrences;

        while (std::getline(ss, pair, ',')) {
            std::istringstream ps(pair);
            int occurrence;
            std::string color;

            ps >> occurrence >> color;
            colorOccurrences[color] = occurrence;
        }

        tryouts.push_back(colorOccurrences);
    }

    gameData[gameNumber] = tryouts;
    data.push_back(gameData);
}

void Bag::readInput(const std::string& input) {
    std::ifstream file(input);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            parseString(line);
        }
        file.close();
        for (const auto& gameMap : data) {
            for (const auto& gamePair : gameMap) {
                std::cout << "Game " << gamePair.first << ":" << std::endl;

                int tryoutNumber = 1;
                for (const auto& tryout : gamePair.second) {
                    std::cout << "  Tryout " << tryoutNumber++ << ":" << std::endl;
                    for (const auto& colorPair : tryout) {
                        std::cout << "    " << colorPair.first << ": " << colorPair.second << std::endl;
                    }
                }
            }
        }
    }
    else {
        std::cout << "Unable to open file";
    }
}

int Bag::sum() {

    int sumOfGameNumbers = 0;

    for (const auto& gameMap : data) {
        for (const auto& gamePair : gameMap) {
            int gameNumber = gamePair.first;
            bool validGame = true;

            for (const auto& tryout : gamePair.second) {
                for (const auto& colorPair : tryout) {
                    const std::string& color = colorPair.first;
                    int occurrence = colorPair.second;

                    if (bag.find(color) != bag.end() && occurrence > bag.at(color)) {
                        validGame = false;
                        break;
                    }
                }
                if (!validGame) {
                    break;
                }
            }
            if (validGame) {
                sumOfGameNumbers += gameNumber;
            }
        }
    }
    return sumOfGameNumbers;
}

void Bag::checkColor() {
    for (const auto& gameMap : data) {
        for (const auto& gamePair : gameMap) {
            int gameNumber = gamePair.first;
            std::map<std::string, int> maxColorValues;

            for (const auto& tryout : gamePair.second) {
                for (const auto& colorPair : tryout) {
                    const std::string& color = colorPair.first;
                    int occurrence = colorPair.second;

                    maxColorValues[color] = std::max(maxColorValues[color], occurrence);
                }
            }
            power[gameNumber] = maxColorValues;
        }
    }

    // for (const auto& gamePair : power) {
    //     std::cout << "Game " << gamePair.first << ":" << std::endl;
    //     for (const auto& colorPair : gamePair.second) {
    //         std::cout << "  " << colorPair.first << ": " << colorPair.second << std::endl;
    //     }
    // }
}

int Bag::pow() {
    int sumPow = 0;

    for (auto &i : power) {
        int pow = 1;
        for (auto &j : i.second) {
            pow *= j.second;
        }
        sumPow +=pow;
    }
    return  sumPow;
}
