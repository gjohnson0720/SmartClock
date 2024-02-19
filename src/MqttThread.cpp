#include "MqttThread.h"
#include "log.h"
#include <string.h>
#include <string>
#include <iostream>
#include "Utilities.h"

#define CLIENT_ID "SmartClock-"
#define BROKER_ADDRESS "SmartClock.local"
#define MQTT_PORT 1883;
#define GARAGE_TEMP_TOPIC "home/garage/temperature"
#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

MqttThread::MqttThread(std::function<void(float)> _garageTempCallback) : garageTempCallback(_garageTempCallback)
{
}

MqttThread::~MqttThread()
{
    iot_client->loop_stop();
    iot_client->disconnect();
    iot_client.reset();
    mosqpp::lib_cleanup();
}

void MqttThread::Start()
{
    using namespace std::chrono;
    FILE_LOG(linfo) << " MqttThread start" << std::endl;
        
    int rc;

    std::string client_id = CLIENT_ID + Utilities::GetIpAddress();
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();

    iot_client = std::make_unique<mosqpp::mosquittopp>(client_id.c_str());
    iot_client->OnConnect = [&](int rc){OnConnect(rc);};
    iot_client->OnDisconnect = [&](int rc){OnDisconnect(rc);};
    iot_client->OnSubscribe = [&](int mid, int qos_count, const int *granted_qos){OnSubscribe(mid, qos_count, granted_qos);};
    iot_client->OnMessage = [&](const struct mosquitto_message *message){OnMessage(message);};
    int keepalive = DEFAULT_KEEP_ALIVE;
    iot_client->connect(host, port, keepalive);
    iot_client->loop_start();
}

void MqttThread::OnConnect(int rc)
{
    if (!rc)
    {
        std::cout << "Connected - code " << rc << std::endl;
        int ret = iot_client->subscribe(NULL, GARAGE_TEMP_TOPIC);
        if (ret != MOSQ_ERR_SUCCESS)
        {
            FILE_LOG(linfo) << "MqttThread subscribe to topic " << GARAGE_TEMP_TOPIC << " failed" << std::endl;
        }
    }
}

void MqttThread::OnDisconnect(int rc)
{
    std::cout << "Disconnected - code " << rc << std::endl;
}

void MqttThread::OnSubscribe(int mid, int qos_count, const int *granted_qos)
{
    std::cout << "Subscription succeeded." << std::endl;
}

void MqttThread::OnMessage(const struct mosquitto_message *message)
{
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];

    std::cout << "Received topic: " << message->topic << std::endl;
    std::cout << "Received " << (char*)message->payload << std::endl;

    if(!strcmp(message->topic, GARAGE_TEMP_TOPIC))
    {
        std::string payload((char*)message->payload, message->payloadlen);
        auto value = std::stof(payload);
        garageTempCallback(value);
    }
}

