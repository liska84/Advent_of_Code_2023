#include "Bag.hpp"

int main() {

    Bag::readInput("input.txt");
    std::cout << "Sum of valid game numbers: " << Bag::sum() << std::endl;
    Bag::checkColor();
    std::cout << "Sum of the power of the sets: " << Bag::pow() << std::endl;

    return 0;
}