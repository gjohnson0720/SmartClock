# SmartClock

sudo apt install libcurl4-gnutls-dev

To install mqtt on pi
https://randomnerdtutorials.com/how-to-install-mosquitto-broker-on-raspberry-pi/

1) sudo apt update && sudo apt upgrade
2) sudo apt install -y mosquitto mosquitto-clients
3) sudo systemctl enable mosquitto.service
4) to test it: mosquitto -v

Configure Mosquitto
1) sudo nano /etc/mosquitto/mosquitto.conf
2) add these lines to the end of the file
    listener 1883
    allow_anonymous true
3) Save and exit nano
4) sudo systemctl restart mosquitto


Build Paho mqtt
Building the Paho C library

Before building the C++ library, first, build and install the Paho C library, if not already present. Note, this version of the C++ library requires Paho C v1.3.8 or greater.

$ git clone https://github.com/eclipse/paho.mqtt.c.git
$ cd paho.mqtt.c
$ git checkout v1.3.8

$ cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
    -DPAHO_WITH_SSL=OFF -DPAHO_HIGH_PERFORMANCE=ON
$ sudo cmake --build build/ --target install
$ sudo ldconfig

git clone https://github.com/eclipse/paho.mqtt.cpp
$ cd paho.mqtt.cpp

$ cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=FALSE -DPAHO_BUILD_SAMPLES=TRUE -DPAHO_WITH_SSL=OFF

$ sudo cmake --build build/ --target install
$ sudo ldconfig
