# usr_sdm_pi_ws
ROS2 Humble Workspace of Raspberry Pi Controller for Underwater Snake-like Robot with Screw-drive Mechanism

# Installation
You can either build it yourself or use the prebuilt binaries:
  - WiringPi (for RS485-CAN-HAT)
  - Realsense (for iD405)
## Install Dependencies
Eigen3.0

## Install WiringPi
WiringPi is a performant GPIO access library written in C for Raspberry Pi boards.
### From Source
Create Debian-package
```sh
# fetch the source
sudo apt install git
git clone https://github.com/WiringPi/WiringPi.git
cd WiringPi

# build the package
./build debian
mv debian-template/wiringpi-3.0-1.deb .

# install it
sudo apt install ./wiringpi-3.0-1.deb
```

## Install Realsense



