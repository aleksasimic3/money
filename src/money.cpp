#include "money.h"

namespace {
    size_t _getExchangeRateWriteCallback(char *data, size_t size, size_t nmemb, void *writeBuffer) {
        ((std::string*)writeBuffer)->append(data, size*nmemb);
        return size*nmemb;
    }

    std::string _fetchData(const std::string& url) {

        std::string response;

        CURL *curl = curl_easy_init();
        if(!curl) {
            std::cerr << "Unable to initialize cURL.\n";
            return std::string();
        }
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _getExchangeRateWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            std::cerr << "ERROR durring transfer!\n";
            curl_easy_cleanup(curl);
            return std::string();
        }

        curl_easy_cleanup(curl);
        return response;
    }
}

//clean up code and add error checking
double money::exchangeRate(const std::string& baseCurrency, const std::string& destinationCurrency, const std::string& id) {

    double rate = 0;
    nlohmann::json allRates;
    bool cached = false;

    //check for local rates
    if(LOGGING) std::clog << "Checking for cached rates.\n";
    std::ifstream cachedRatesFile = std::ifstream(".\\bin\\" + baseCurrency + ".json"); //make it relative
    if(cachedRatesFile.is_open()) {
        if(LOGGING) std::clog << "\tFound cached file.\n";
        allRates = nlohmann::json::parse(cachedRatesFile); //catch exceptions
        if(allRates["time_next_update_unix"] > std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {
            if(LOGGING) std::clog << "\tCached rates are valid.\n";
            cached = true;
        }
        else if(LOGGING) std::clog << "\tCached rates are outdated.\n";
        cachedRatesFile.close();
    }

    //grab data from server and save it to file
    if(cached == false) {
        std::string url = API_URL + id + API_ENDPOINT + baseCurrency;
        if(LOGGING) std::clog << "Fetching data from sever, url: " << url << '\n';
        std::string response = _fetchData(url); //check return value
        allRates = nlohmann::json::parse(response); //catch exceptions
        if(allRates["result"] != "success") {
            if(LOGGING) std::clog << "API error.\n";
            std::cout << response << '\n';
            return 0;
        }
        if(LOGGING) std::clog << "\tSuccess.\n";
        if(LOGGING) std::clog << "\tSaving data for later.\n";
        std::ofstream file = std::ofstream(".\\bin\\" + baseCurrency + ".json");
        if(file.is_open()) {
            file << response;
            file.close();
        }
        else if(LOGGING) std::clog << "Failed to save rates.\n";
    }

    rate = allRates["conversion_rates"][destinationCurrency];

    if(LOGGING) std::clog << "Returnning rate " << rate << ".\n";
    return rate;
}