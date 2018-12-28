#!/bin/sh

file=k380_conf
gcc -o $file $file.c

BUILD_SH=$(readlink -f "$0")
BUILD_PATH=$(dirname "$BUILD_SH")
FN_ON="$BUILD_PATH/fn_on.sh"
UDEV_RULES="$BUILD_PATH/80-k380.rules"

echo "ACTION==\"add\", KERNEL==\"hidraw[0-9]*\", RUN+=\"$FN_ON /dev/%k\"" > $UDEV_RULES
echo "To automatically turn on fn using udev rules, run the following command"
echo "    sudo cp $UDEV_RULES /etc/udev/rules.d/ && sudo udevadm control --reload"

