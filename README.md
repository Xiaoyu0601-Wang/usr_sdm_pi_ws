# usr_sdm_pi_ws
ROS2 Humble Workspace of Raspberry Pi Controller for Underwater Snake-like Robot with Screw-drive Mechanism

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
mv debian-template/wiringpi-3.0-1.deb .
# install it
sudo apt-get install ./wiringpi-3.0-1.deb
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
