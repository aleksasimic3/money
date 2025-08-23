#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

#include "money.h"

const std::string ID_FILENAME = "id";

std::string toUpper(const std::string& s);

//money.exe 100 EUR RSD
int main(int argc, char* argv[]) {

    if(argc < 4) {
        std::cerr << "Usage: money [AMOUNT] [BASE_CURRENCY] [DESTINATION_CURRENCY]\n";
        return -1;
    }

    //terrible, add validation
    double amount = std::stod(argv[1]);
    std::string baseCurrency = toUpper(argv[2]);
    std::string destinationCurrency = toUpper(argv[3]);

    std::ifstream idFile = std::ifstream(".\\bin\\id");
    std::string id;
    idFile >> id;

    double destinationAmount = money::exchangeRate(baseCurrency, destinationCurrency, id) * amount;

    std::cout << amount << ' ' << baseCurrency << " = " << destinationAmount << ' ' << destinationCurrency << '\n';
 
    return 0;
}

std::string toUpper(const std::string& s) {
    std::string upperCase;
    for(auto c : s) upperCase += toupper(c);
    return upperCase;
}