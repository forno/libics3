sudo modprobe ftdi-sio
sudo chmod 666 /sys/bus/usb-serial/drivers/ftdi_sio/new_id
echo 165c 0008 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
echo "ttyUSB{x} created : {x} is number."
