#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <string>
#include <map>
class Calibration {
public:
    Calibration() = default;
    ~Calibration() = default;

    static  int sum1;
    static  int sum2;

    static  void    readFile(const std::string& input);
    static void     readFileDigits(const std::string& input);
    static void     check();
private:

    static std::vector<int>    init;
    static std::vector<int>    update;
    static std::vector<std::string>    initS;
    static std::vector<std::string>    updateS;
    static const    std::map <std::string, std::string> myMap;
    static          std::string parseLine(const std::string& line);
};

#endif //CALIBRATION_H
