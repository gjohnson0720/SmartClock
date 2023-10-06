#pragma once

#include <thread>
#include <functional>

class MqttThread
{
public:  
    MqttThread(std::function<void(float)> garageTempCallback);
    ~MqttThread();

    void Start();

private:
    std::thread thread;
    std::function<void(float)> garageTempCallback;

    void Run();
    void OnConnect(int rc);
    void OnSubscribe(int mid, int qos_count, const int *granted_qos);
    void OnMessage(const struct mosquitto_message *message);
};