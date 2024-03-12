#pragma once
#include <curl/curl.h>
#include <iostream>

size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    (void)contents;
    (void)userp;
    return size * nmemb;
}

/// @brief Do a quick HTTP-ping to /ping backend (for SisijaServers only)
/// @param baseUrl The URL to the Server
/// @return The ping time in milliseconds if failed -1
inline double httpPing(const std::string& baseUrl) {
    CURL *curl;
    CURLcode res;
    double totalTime = -1;

    std::string url = baseUrl + "/ping";

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        
        res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &totalTime);
            totalTime *= 1000;
        } else {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return totalTime;
}