#include "Calibration.hpp"
#include <iostream>

int main() {

    Calibration::readFile("input.txt");
    Calibration::readFileDigits("input.txt");
    // Calibration::check();
    std::cout << "Sum of all calibration values1 is : " << Calibration::sum1 << std::endl;
    std::cout << "Sum of all calibration values2 is : " << Calibration::sum2 << std::endl;

    return 0;
}
