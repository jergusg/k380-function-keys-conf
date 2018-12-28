# k380-function-keys-conf
Make function keys default on Logitech k380 bluetooth keyboard.

## Instructions

1) First install `gcc`. On Ubuntu run:
```
sudo apt install gcc
```
2) Download installation files https://github.com/jergusg/k380-function-keys-conf/releases/ (Source code).

3) Connect your K380 keyboard via bluetooth to your computer.

4) Run `build.sh`

```
./build.sh
```

5) To switch keyboard's upper keys to F-keys run:

```
sudo ./k380_conf -d /dev/hidrawX -f on
```
Where X is number of your keyboard hidraw interface. Possibly `0, 1, 2, 3`.

### Switch keys to F-keys automatically

Follow instructions your received when you built `k380_conf`:
```
sudo cp /your-build-path/80-k380.rules /etc/udev/rules.d/ && sudo udevadm control --reload
```
Now, when you reconnect your keyboard it will be automatically switched to F-keys mode.

## Based on

<http://www.trial-n-error.de/posts/2012/12/31/logitech-k810-keyboard-configurator/>

<https://github.com/embuc/k480_conf>

look there for more information
