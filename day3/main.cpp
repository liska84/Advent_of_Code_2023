#include "Engine.hpp"

int main() {
	Engine::readInput("input.txt");
	Engine::checkInput();
	std::cout << Engine::sum() << std::endl;

    return 0;
}