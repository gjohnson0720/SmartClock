# SmartClock

Setup Raspberry Pi
- Download and install the Raspberry Pi OS Imager from https://www.raspberrypi.com/software/
- Write the Raspberry Pi OS to an SD Card
- Run Raspberry PI with SD Card
- Get all updates 
    sudo apt update
    sudo apt upgrade
- setup ssh
    sudo raspi-config
    choose 3 -> I2 -> Yes
- ssh pi@<192.168.2.7>
- set hostname
    sudo nano /etc/hostname
    replace the name with the new host name
    sudo reboot

Install dependencies
- To install mqtt on pi
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
sudo apt install git cmake build-essential pkg-config libcurl4-gnutls-dev libmosquitto-dev libgtk-3-dev

git clone https://github.com/gjohnson0720/SmartClock.git


cd SmartClock
git clone https://github.com/nlohmann/json.git json  -- need to fix repo to pull this automatically
mkdir build
cd build
cmake ..
make

To Auto start SmartClock at startup
- crontab -e
- press enter to select nano
- at the end of the window, enter "@reboot /home/rpi/SmartClock/build/SmartClock.sh"
- Ctrl-O, Ctrl-W
- sudo reboot

1. Edit the path in file SmartClock.sh to point to the folder you built SmartClock into

2. Copy the file SmartClock.sh to /home/pi/SmartClock/build.
 
3. Edit SmartClock.desktop with the paths to your SmartClock build folder.  Copy SmartClock.desktop to /home/pi/.config/autostart folder.
   It might be different in your case. Just open your home folder and enable view hidden folders. open .config/autostart. If you don't see autostart folder, then create a folder called autostart within .config folder.  



Disable screen blanking
https://pimylifeup.com/raspberry-pi-disable-screen-blanking/
- sudo raspi-config
- select 2 -> Screen Blanking -> No


sudo apt install mosquitto libmosquitto-dev
