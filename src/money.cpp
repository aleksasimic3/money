#include "money.h"

namespace {
    size_t _getExchangeRateWriteCallback(char *data, size_t size, size_t nmemb, void *writeBuffer) {
        ((std::string*)writeBuffer)->append(data, size*nmemb);
        return size*nmemb;
    }
}

std::map<std::string, double> money::getExchangeRates(const std::string& id, const std::string& baseCurrency) {

    //check for existing rates and check the next_update field

    //curl sent req
    CURL *curl = curl_easy_init();
    if(!curl) {
        std::cerr << "Unable to initialize cURL.\n";
        return std::map<std::string, double>();
    }
    CURLcode res;
    std::string requestUrl = API_URL + id + API_ENDPOINT + baseCurrency;
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _getExchangeRateWriteCallback); //maybe use a lambda function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
        std::cerr << "ERROR durring transfer!\n";
        return std::map<std::string, double>();
    }

    //parse output
    //check status
    nlohmann::json ratesJson = nlohmann::json::parse(response)["conversion_rates"];
    std::map <std::string, double> rates;
    for(auto it = ratesJson.begin(); it != ratesJson.end(); it++) {
        rates[it.key()] = it.value();
    }

    //save as file for later use

    curl_easy_cleanup(curl);

    //return map
    return rates;
}