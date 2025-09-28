#pragma once

#include <thread>
#include <list>
#include "CurlThreadConfig.h"
#include <chrono>
#include <condition_variable>
#include <mutex>

class CurlThread
{
public:  
    CurlThread();
    ~CurlThread();

    void AddUrlToRetrieve(const CurlThreadConfig& config);
    void Start();

private:
    std::thread thread;
    std::atomic<bool> stopFlag{false};
    std::condition_variable cv;
    std::mutex cv_m;
    std::list<CurlThreadConfig> configs;

    void Run();
    CurlThreadConfig* FindNextWaitTime();
    std::string RetrieveUrl(const std::string& url);
    std::string RetrieveUrlFromCurl(const std::string& url);
    std::string RetrieveUrlFromFile(const std::string& url);
    std::string GetFilePath(const CurlThreadConfig& config);
    void RetrieveUrl(const CurlThreadConfig& config);
};