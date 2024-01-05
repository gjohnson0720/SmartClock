#pragma once

#include <thread>
#include <functional>
#include <mosquittopp.h>

class MqttThread
{
public:  
    MqttThread(std::function<void(float)> garageTempCallback);
    ~MqttThread();

    void Start();

private:
    std::function<void(float)> garageTempCallback;
    std::unique_ptr<mosqpp::mosquittopp> iot_client;

    void OnConnect(int rc);
    void OnDisconnect(int rc);
    void OnSubscribe(int mid, int qos_count, const int *granted_qos);
    void OnMessage(const struct mosquitto_message *message);
};