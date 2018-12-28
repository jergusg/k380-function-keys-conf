#!/bin/sh


TOOL="$(dirname $0)/k380_conf"
# Check if device is our keyboard: 046D:B342
DEV="$(ls /sys/class/hidraw/ -l | grep 046D:B342 | grep -o 'hidraw[0-9]*$')"

# Run if parameter $1 is nothing or it is k380 keyboard
if test -n "$DEV" && (test -z "$1" || test "/dev/$DEV" = "$1")
then
    echo "Found K380 at $DEV"
    $TOOL -d "/dev/$DEV" -f on
fi


