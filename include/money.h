#ifndef MONEY_H_
#define MONEY_H_

#include <iostream>
#include <string>
#include <map>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace money {

    const std::string DEFAULT_CURRENCY = "EUR";
    const std::string API_URL = "https://v6.exchangerate-api.com/v6/";
    const std::string API_ENDPOINT = "/latest/";

    std::map<std::string, double> getExchangeRates(const std::string& id, const std::string& baseCurrency = DEFAULT_CURRENCY);

}

#endif //MONEY_H_