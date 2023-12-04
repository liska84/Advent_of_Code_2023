#ifndef BAG_HPP
#define BAG_HPP
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

class Bag {
public:
    Bag() = default;
    ~Bag() = default;

    static std::vector<std::map<int, std::vector<std::unordered_map<std::string, int>>>> data;
    static std::map<int, std::map<std::string, int>> power;

    static void parseString(const std::string& line);
    static void readInput(const std::string& line);
    static int sum();
    static int pow();
    static void checkColor();

};


#endif