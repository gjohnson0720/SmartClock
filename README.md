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


Setup to build on Linux
sudo apt install git cmake build-essential pkg-config libcurl4-gnutls-dev mosquitto mosquitto-clients libmosquitto-dev libgtk-3-dev

git clone https://github.com/gjohnson0720/SmartClock.git


cd SmartClock
git clone https://github.com/nlohmann/json.git json  -- need to fix repo to pull this automatically
mkdir build
cd build
cmake ..
make

