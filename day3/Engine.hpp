#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Engine {
public:
    Engine() = default;
    ~Engine() = default;
    static void readInput(const std::string& file);
	static void checkInput();
	static bool checker(int x, int y, int length);
	static int sum();
	static void checkGear();
	static void checkGearInput();

private:
    static std::vector<std::vector<char>> input;
	static std::vector<int> lonely;
	static std::vector<int> adjacent;
};



#endif
