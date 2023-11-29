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


**Setup to build on Linux**
sudo apt install git cmake build-essential pkg-config libcurl4-gnutls-dev mosquitto mosquitto-clients libmosquitto-dev libgtk-3-dev

git clone https://github.com/gjohnson0720/SmartClock.git


cd SmartClock
git clone https://github.com/nlohmann/json.git json  -- need to fix repo to pull this automatically
mkdir build
cd build
cmake ..
make

1. Edit the path in file SmartClock.sh to point to the folder you built SmartClock into

2. Copy the file SmartClock.sh to /home/pi/SmartClock/build.
 
3. Edit SmartClock.desktop with the paths to your SmartClock build folder.  Copy SmartClock.desktop to /home/pi/.config/autostart folder.
   It might be different in your case. Just open your home folder and enable view hidden folders. open .config/autostart. If you don't see autostart folder, then create a folder called autostart within .config folder.  



Disable screen blanking
https://pimylifeup.com/raspberry-pi-disable-screen-blanking/



sudo apt install mosquitto libmosquitto-dev
