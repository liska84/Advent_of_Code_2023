#include "Calibration.hpp"
#include <string>
#include <fstream>
#include <cctype>
#include <map>
#include <iostream>

int Calibration::sum1 = 0;
int Calibration::sum2 = 0;

const std::map<std::string, std::string> Calibration::myMap = {
    {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"},
        {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
    };

const std::map<std::string, std::string> creepyMap = {
    {"oneight", "18"}, {"twone", "21"}, {"threeight", "38"}, {"fiveight", "58"},
        {"sevenine", "79"}, {"eightwo", "82"}, {"eighthree", "83"}, {"nineight", "98"}
};

std::vector<int> Calibration::init;
std::vector<int> Calibration::update;

std::vector<std::string> Calibration::initS;
std::vector<std::string> Calibration::updateS;

void Calibration::readFile(const std::string& input) {
    std::ifstream file(input);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::string calibrationValue;
            int digitCount = 0;
            initS.push_back(line);

            for (char & c : line) {
                if (isdigit(c)) {
                    digitCount++;
                }
            }

            if (digitCount > 1) {
                for (char & it : line) {
                    if (isdigit(it)) {
                        calibrationValue += it;
                        break;
                    }
                }
                for (auto it = line.rbegin(); it != line.rend(); ++it) {
                    if (isdigit(*it)) {
                        calibrationValue += *it;
                        break;
                    }
                }
            }
            else {
                for (char & it : line) {
                    if (isdigit(it)) {
                        calibrationValue += it;
                        calibrationValue += it;
                    }
                }
            }
            init.push_back( std::stoi(calibrationValue));
            sum1 += std::stoi(calibrationValue);
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file";
    }
}

std::string checkMap(std::string& result, std::map<std::string, std::string> myMap) {
    size_t pos;
    while (true) {
        std::string replace;
        size_t firstPos = std::string::npos;
        for (const auto& pair : myMap) {
            pos = result.find(pair.first);
            if (pos != std::string::npos && (firstPos == std::string::npos || pos < firstPos)) {
                firstPos = pos;
                replace = pair.first;
            }
        }
        if (firstPos != std::string::npos) {
            result.replace(firstPos, replace.length(), myMap.at(replace));
        }
        else {
            break;
        }
    }
    return result;
}

std::string Calibration::parseLine(const std::string& line) {
    std::string result = line;
    result = checkMap(result, creepyMap);
    result = checkMap(result, myMap);
    return result;
}

void Calibration::readFileDigits(const std::string& input) {
    std::ifstream file(input);
    if (file.is_open()) {
        std::string line;

        while (std::getline(file, line)) {
            std::string calibrationValue;

            std::string resLine = parseLine(line);
            updateS.push_back(resLine);

            for (auto it = resLine.begin(); it != resLine.end(); ++it) {
                if (isdigit(*it)) {
                    calibrationValue += *it;
                    break;
                }
            }

            for (auto it = resLine.rbegin(); it != resLine.rend(); ++it) {
                if (isdigit(*it)) {
                    calibrationValue += *it;
                    break;
                }
            }
            sum2 += std::stoi(calibrationValue);
            update.push_back( std::stoi(calibrationValue));
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file";
    }
}

void checker(std::vector<int>& init, std::vector<int>& update, std::vector<std::string>& initS, std::vector<std::string>& updateS) {
    if (init.size() != update.size())
        std::cout << "Number of calibration values DIFFER" << std::endl;

    for (size_t i = 0; i < init.size(); ++i) {

        if(init[i] != update[i]) {
            std::cout << "Line " << i + 1 << ": Init value: " << init[i] << " | Updated value: " << update[i] << std::endl;
            std::cout << initS[i] << std::endl;
            std::cout << updateS[i] << std::endl;
        }
    }
}

void Calibration::check() {
    checker(init, update, initS, updateS);
}
