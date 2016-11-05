# BSD 2-Clause License
# 
# Copyright (c) 2016, Doi Yusuke
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
