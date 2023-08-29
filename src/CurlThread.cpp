#include "CurlThread.h"
#include <chrono>
#include <ctime>
#include "TimeUtils.h"
#include <curl/curl.h>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

CurlThread::CurlThread()
{
}

CurlThread::~CurlThread()
{
}

void CurlThread::AddUrlToRetrieve(const CurlThreadConfig& config)
{
    configs.push_back(config);
    fs::create_directories(config.outputFolder);
}

void CurlThread::Start()
{
    thread = std::thread(&CurlThread::Run, this);
}


std::string CurlThread::GetFilePath(const CurlThreadConfig& config)
{
    using namespace std::chrono;
    auto now = system_clock::now();
    const std::time_t t_c = system_clock::to_time_t(now);
    auto secs = time_point_cast<seconds>(now);
    std::stringstream s;
    s << config.outputFolder << "/";
    s << std::put_time(std::gmtime(&t_c), "%F-%H-%M-%S");
    s << "." << config.fileExtension;
    return s.str();
}

void CurlThread::Run()
{
    for (auto& c : configs)
    {
        RetrieveUrl(c);
    }
    while (true)
    {
        auto config = FindNextWaitTime();
        if (config == nullptr)
        {
            std::cout << "No Curl config found, exiting thread" << std::endl;
            return;
        }
        auto diff = config->GetTimeDelta();
        std::cout << "Sleeping for " << (diff.count() / 1000000) << " msecs" << std::endl;
        std::this_thread::sleep_for(diff);
        RetrieveUrl(*config);
        config->SetNextTime();
    }
}

void CurlThread::RetrieveUrl(const CurlThreadConfig& config)
{
    auto contents = RetrieveUrl(config.url);
    config.urlContentsCallback(contents);
    if (!config.outputFolder.empty())
    {
        auto filePath = GetFilePath(config);
        std::ofstream file(filePath);
        file << "<!--" << config.url << "-->" << std::endl;
        file << contents;
        file.close();
    }
}

CurlThreadConfig* CurlThread::FindNextWaitTime()
{
    using namespace std::chrono_literals;
    CurlThreadConfig* config = nullptr;
    auto minDiff = std::chrono::system_clock::duration::max();
    for (auto& c : configs)
    {
        auto diff = c.GetTimeDelta();
        //std::cout << c.url << ": diff = " << diff.count() << std::endl;
        if (diff < minDiff)    
        {
            //std::cout << c.url << ": new mindiff = " << diff.count() << std::endl;
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

std::string CurlThread::RetrieveUrl(const std::string& url)
{
    if ((url.find("https://") != std::string::npos) || (url.find("http://") != std::string::npos))
        return RetrieveUrlFromCurl(url);
    else
        return RetrieveUrlFromFile(url);
}

std::string CurlThread::RetrieveUrlFromCurl(const std::string& url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
    }
    return readBuffer;
}

std::string CurlThread::RetrieveUrlFromFile(const std::string& url)
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