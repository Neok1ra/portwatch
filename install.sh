#!/bin/bash
echo "[*] Installing PortWatcher X..."

apt update -y
apt install -y libpcap-dev python3-pip tor curl build-essential

pip3 install -r requirements.txt

# Compile C core
cd src/core
gcc -Wall -O2 -o ../../bin/pw_x_linux pw_x.c -lpcap -lpthread
strip ../../bin/pw_x_linux
cd ../..

echo "[+] PortWatcher X installed!"
echo "[+] Run: ./bin/pw_x_linux eth0 192.168.1.100"