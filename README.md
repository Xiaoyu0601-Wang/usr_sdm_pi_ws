# usr_sdm_pi_ws
ROS2 Humble(or Jazzy) Workspace of Raspberry Pi Controller for Underwater Snake-like Robot with Screw-drive Mechanism

# Installation
You can either build it yourself or use the prebuilt binaries:
  - Ubuntu 22.04(Or 24.02) Server
  - ROS2 Humble
  - WiringPi (for RS485-CAN-HAT)
  - Realsense (for iD405)

## Install Ubuntu 22.04 server on Raspberry Pi Zero 2W
Use Raspberry Pi Imager to set up the image loader.

## Install ROS2 Humble on Ubuntu 22.04 server
For the USR-SDM client, ROS2 Humble is used on the Ubuntu 22.04 server for Raspberry Pi Zero 2W.
```sh
# install necessary packages
sudo apt-get install build-essential cmake git locales curl wget gnupg lsb-release python3 python3-pip vim
# add ros2 repository
sudo apt-get install software-properties-common
sudo add-apt-repository universe
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
```
Since USR-SDM client with Raspberry Pi Zero 2W is a system without a desktop, the ros-base is chosen for installation to save space.
```sh
# install ros2 humble and colcon (Ubuntu 22.02)
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install ros-humble-ros-base python3-colcon-common-extensions
```
```sh
# install ros2 jazzy and colcon (Ubuntu 24.02)
sudo apt-get update && sudo apt-get upgrade
sudo apt-get install ros-jazzy-ros-base python3-colcon-common-extensions
```
Add source and export to `~/.bashrc`:
```sh
# source ros2 humble and colcon (Ubuntu 22.02)
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
echo "export _colcon_cd_root=/opt/ros/humble/" >> ~/.bashrc
```
```sh
# source ros2 jazzy and colcon (Ubuntu 24.02)
echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc
echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
echo "export _colcon_cd_root=/opt/ros/jazzy/" >> ~/.bashrc
```

## Install WiringPi
WiringPi is a performant GPIO access library written in C for Raspberry Pi boards.
### From Source
Create Debian-package
```sh
# fetch the source
sudo apt-get install git
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi
# build the package
./build debian
mv debian-template/wiringpi_3.6_arm64.deb .
# install it
sudo apt-get install ./wiringpi_3.6_arm64.deb
```
### Access GPIO pins without root
```sh
sudo apt-get install rpi.gpio-common
# Create a gpio group:
sudo groupadd gpio
# Add your user to the gpio group:
sudo usermod -aG gpio $USER
# Create a udev rule file:
sudo nano /etc/udev/rules.d/99-gpio.rules
# Add the following lines to the file:
SUBSYSTEM=="gpio", KERNEL=="gpiochip*", ACTION=="add", RUN+="/bin/chgrp gpio /dev/gpiochip0"
SUBSYSTEM=="gpio", KERNEL=="gpiochip*", ACTION=="add", RUN+="/bin/chmod g+rw /dev/gpiochip0"
SUBSYSTEM=="gpio", KERNEL=="gpio*", ACTION=="add", RUN+="/bin/chgrp gpio /dev/gpio*"
SUBSYSTEM=="gpio", KERNEL=="gpio*", ACTION=="add", RUN+="/bin/chmod g+rw /dev/gpio*"
SUBSYSTEM=="gpio", KERNEL=="gpiomem", ACTION=="add", RUN+="/bin/chgrp gpio /dev/gpiomem"
SUBSYSTEM=="gpio", KERNEL=="gpiomem", ACTION=="add", RUN+="/bin/chmod g+rw /dev/gpiomem"
# 
sudo adduser "${USER}" dialout
# 
sudo chown root.gpio /dev/gpiomem
sudo chmod g+rw /dev/gpiomem
```

## RS485-CAN-HAT
Website: https://www.waveshare.com/wiki/RS485_CAN_HAT
```sh
# Edit the config.txt file using your preferred text editor.
sudo nano /boot/firmware/config.txt
# Add or modify the necessary lines to configure the MCP2515 CAN controller with a 12 MHz crystal.
# For nano, press Ctrl + X, then Y to confirm changes, and Enter to save.
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=12000000,interrupt=25,spimaxfrequency=2000000
# Check if the CAN interface is available:
sudo apt-get install net-tools
ifconfig -a
# Load the necessary kernel modules:
sudo modprobe can
sudo modprobe can_dev
sudo modprobe mcp251x
# To make the modules load at boot, add them to /etc/modules:
echo "can" | sudo tee -a /etc/modules
echo "can_dev" | sudo tee -a /etc/modules
echo "mcp251x" | sudo tee -a /etc/modules
# Bring up the CAN interface with the desired bitrate (e.g., 500000):
sudo ip link set can0 up type can bitrate 500000
```
### Install CAN Utilities
Install the can-utils package to test and work with the CAN interface:
```sh
sudo apt install can-utils
cansend can0 123#11223344AABBCCDD
```

## Install Realsense


# Optimize Build Environment
## Use Swap Space
Increase the swap space to provide more virtual memory for the build process.
```sh
# Install dphys-swapfile and dphys-config
sudo apt-get install dphys-swapfile dphys-config
sudo dphys-swapfile swapoff
sudo nano /etc/dphys-swapfile
```
Change the CONF_SWAPSIZE to a larger value, for example, 2048 (2GB). Save and exit, then:
```sh
sudo dphys-swapfile setup
sudo dphys-swapfile swapon
```
