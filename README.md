# usr_sdm_pi_ws
Workspace of Raspberry Pi for Underwater Snake-like Robot with Screw-drive Mechanism
## Installing

You can either build it yourself or use the prebuilt binaries:

### From Source

1. create debian-package

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

