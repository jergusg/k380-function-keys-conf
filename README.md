# k380-function-keys-conf
Make function keys default on Logitech k380 bluetooth keyboard.

## Instructions

1) First install `build-essential` package (includes `gcc`, `make`, `libc-dev`, etc.).
```shell
# On Debian/Ubuntu run:
sudo apt install build-essential
# on CentOS/REHEL/Fedora
sudo dnf groupinstall "Development Tools"
# on Arch-linux 
sudo pacman -Sy base-devel
```
2) Download installation files https://github.com/jergusg/k380-function-keys-conf/releases/ (Source code).

3) Connect your K380 keyboard via bluetooth to your computer.

4) Run `sudo make install`

5) Get the number of your keyboard hidraw interface - `/dev/hidrawX` where X is `0, 1, 2, 3`.
```shell
sudo ./fn_on.sh
```

6) To switch keyboard's upper keys to F-keys run:
```
sudo k380_conf -d /dev/hidrawX -f on
```

### Switch keys to F-keys automatically

After install do the following:
```
sudo make reload
```
Now, when you reconnect your keyboard it will be automatically switched to F-keys mode.

## Based on

<http://www.trial-n-error.de/posts/2012/12/31/logitech-k810-keyboard-configurator/>

<https://github.com/embuc/k480_conf>

look there for more information
