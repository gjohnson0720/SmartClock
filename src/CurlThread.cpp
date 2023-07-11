#include "CurlThread.h"
#include <chrono>
#include "TimeUtils.h"
#include <curl/curl.h>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

CurlThread::CurlThread(const std::vector<CurlThreadConfig>& config_) : configs(config_)
{
    
}

CurlThread::~CurlThread()
{
    
}

void CurlThread::Start()
{
    thread = std::thread(&CurlThread::Run, this);
}

void CurlThread::Run()
{
    const auto* config = FindNextWaitTime();
    if (config == nullptr)
        return;
    auto diff = config->GetTimeDelta();
    std::this_thread::sleep_for(diff);
    config->urlContentsCallback(RetrieveUrl(config->url));
}

const CurlThreadConfig* CurlThread::FindNextWaitTime()
{
    using namespace std::chrono_literals;
    CurlThreadConfig* config = nullptr;
    auto minDiff = std::chrono::system_clock::duration::max();
    for (auto& c : configs)
    {
        auto diff = c.GetTimeDelta();
        if (diff.count() < 0)
            diff += 24h;
        if (diff < minDiff)    
        {
            minDiff = diff;
            config = &c;
        }
    }
    return config;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string CurlThread::RetrieveUrl(std::string url)
{
    if (url.find("https://") != std::string::npos)
        return RetrieveUtlFromCurl(url);
    else
        return RetrieveUtlFromFile(url);
}

std::string CurlThread::RetrieveUtlFromCurl(std::string url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
    }
    return readBuffer;
}

std::string CurlThread::RetrieveUtlFromFile(std::string url)
{
    std::ifstream file(url, std::ios::in);
    if (file)
    {
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }    
    return "";
}