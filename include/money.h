#ifndef MONEY_H_
#define MONEY_H_

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <chrono>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

namespace money {

    const bool LOGGING = true;

    const std::string API_URL = "https://v6.exchangerate-api.com/v6/";
    const std::string API_ENDPOINT = "/latest/";

    //returns exchange rate destinationCurrency = exchangeRate * baseCurrency
    //EUR = exchangeRate(EUR, RSD, id) * RSD
    //returns 0 on error
    double exchangeRate(const std::string& baseCurrency, const std::string& destinationCurrency, const std::string& id);
    //double exchnageRate(const std::string& baseCurrency, const std::string& destinationCurrency); //open access version, rate limited, about once per hour
}

#endif