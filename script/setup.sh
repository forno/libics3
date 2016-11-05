#!/bin/sh
invalidPID(){
  [ $1 -lt 1 ] && return 0
  [ $1 -lt 3 ] && return 1
  [ $1 -lt 6 ] && return 0
  [ $1 -lt 9 ] && return 1
  return 0
}
if [ $# -gt 0 ]; then
  expr $1 + 1 > /dev/null 2>&1
  inputCheck=$?
else
  inputCheck=5
fi
if [ $inputCheck -gt 1 ]; then
  echo "Please select your device"
  echo "1. ICS USB ADAPTER"
  echo "2. SERIAL USB ADAPTER"
  echo "3~5: nothing"
  echo "6. ICS USB ADAPTER HS"
  echo "7. SERIAL USB ADAPTER HS"
  echo "8. DUAl USB ADAPTER HS"
  read onePID
  expr $onePID + 1 > /dev/null 2>&1
  INTCHECK=$?
  if [ $INTCHECK -gt 1 ]; then
    echo "Invalid argument"
    return 1
fi
else
  onePID=$1
fi
if invalidPID $onePID; then
  echo "Out of range"
  return 1
fi
sudo modprobe ftdi-sio
sudo chmod 666 /sys/bus/usb-serial/drivers/ftdi_sio/new_id
echo 165c 000$onePID > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
echo "ttyUSB{x} created : {x} is number."
