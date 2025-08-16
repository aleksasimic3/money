#include <iostream>
#include <fstream>
#include <vector>

#include "money.h"

const std::string ID_FILENAME = "id";
const std::string DEFAULT_CURRENCY = "RSD";
const std::vector<std::string> DEFAULT_CURRENCIES = {"EUR", "USD", "CHF", "GBP", "JPY", "CAD", "AUD", "CNY"};

int main() {

    std::ifstream idFile(ID_FILENAME);
    //find path to file and change working dir
    //check if open and prompt if not
    std::string id;
    idFile >> id;

    std::string baseCurrency = DEFAULT_CURRENCY;
    std::map<std::string, double> rates = money::getExchangeRates(id, baseCurrency);

    //free form output or convert
    std::vector<std::string> currencies = DEFAULT_CURRENCIES;
    for(auto it = currencies.begin(); it != currencies.end(); it++) {
        //std::cout << "1 " << baseCurrency << " = " << rates[*it] << ' ' << *it << '\n';
        std::cout << "1 " << *it << " = " << (1.0/rates[*it]) << ' ' << baseCurrency << '\n'; //if less than 1 then do *10 or *100

    }

    return 0;
}