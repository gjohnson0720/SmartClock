#include "MqttThread.h"
#include <mosquittopp.h>
#include "log.h"
#include <string.h>
#include <string>
#include <iostream>

#define CLIENT_ID "Client_ID"
#define BROKER_ADDRESS "192.168.2.7"
#define MQTT_PORT 1883;
#define GARAGE_TEMP_TOPIC "home/garage/temperature"
#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

MqttThread::MqttThread(std::function<void(float)> _garageTempCallback) : garageTempCallback(_garageTempCallback)
{
}

MqttThread::~MqttThread()
{
    mosqpp::lib_cleanup();
}

void MqttThread::Start()
{
    thread = std::thread(&MqttThread::Run, this);
}

void MqttThread::Run()
{
    using namespace std::chrono;
    FILE_LOG(linfo) << " MqttThread start" << std::endl;
        
    int rc;

    char client_id[] = CLIENT_ID;
    char host[] = BROKER_ADDRESS;
    int port = MQTT_PORT;

    mosqpp::lib_init();

    auto iot_client = std::make_unique<mosqpp::mosquittopp>(client_id);
    iot_client->OnConnect = [&](int rc){OnConnect(rc);};
    iot_client->OnSubscribe = [&](int mid, int qos_count, const int *granted_qos){OnSubscribe(mid, qos_count, granted_qos);};
    iot_client->OnMessage = [&](const struct mosquitto_message *message){OnMessage(message);};
    int keepalive = DEFAULT_KEEP_ALIVE;
    iot_client->connect(host, port, keepalive);
    int ret = iot_client->subscribe(NULL, GARAGE_TEMP_TOPIC);
    if (ret != MOSQ_ERR_SUCCESS)
    {
        FILE_LOG(linfo) << "MqttThread subscribe to topic " << GARAGE_TEMP_TOPIC << " failed" << std::endl;
    }

    iot_client->loop_forever(-1, 1);
}

void MqttThread::OnConnect(int rc)
{
    if (!rc)
    {
        std::cout << "Connected - code " << rc << std::endl;
    }
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
