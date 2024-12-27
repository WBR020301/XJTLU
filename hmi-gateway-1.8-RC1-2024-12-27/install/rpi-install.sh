#!/bin/bash

echo "Please run at current directory"

# install hmi-gateway
sudo mkdir /opt/hmi-gateway
sudo cp -r ../ /opt/hmi-gateway

sudo apt update
sudo apt install vlan

sudo systemctl enable systemd-networkd
sudo systemctl start systemd-networkd

sudo modprobe 8021q
echo "8021q" | sudo tee -a /etc/modules

echo "setup vlan62"
sudo cp 10-vlan62.network /etc/systemd/network/10-vlan62.network
sudo cp 20-vlan62.netdev /etc/systemd/network/20-vlan62.netdev
sudo cp 30-vlan62.network /etc/systemd/network/30-vlan62.network

sudo chmod 444 /etc/systemd/network/10-vlan62.network
sudo chmod 444 /etc/systemd/network/20-vlan62.netdev
sudo chmod 444 /etc/systemd/network/30-vlan62.network

echo "create vlan62 interface"
sudo ip link add link eth0 name vlan62 type vlan id 62
sudo ip link set dev vlan62 up

echo "install hmi gateway service"
sudo cp hmi-gateway.service /etc/systemd/system/hmi-gateway.service
sudo cp vlan62.service /etc/systemd/system/vlan62.service

# disable unnecessary system services
echo "disable unnecessary services"
sudo systemctl disable apt-daily.service
sudo systemctl disable apt-daily-upgrade.service
sudo systemctl disable bluetooth.service
sudo systemctl disable hciuart.service
sudo systemctl disable avahi-daemon.service
sudo systemctl disable triggerhappy.service
sudo systemctl disable nfs-common.service
sudo systemctl disable wpa_supplicant@eth0.service
sudo systemctl disable ModemManager.service
sudo systemctl disable NetworkManager-wait-online.service
sudo systemctl disable systemd-networkd-wait-online.service
sudo systemctl disable alsa-restore.service
sudo systemctl disable sound.target
sudo systemctl disable bluetooth.target
sudo systemctl disable apt-daily.timer
sudo systemctl disable apt-daily-upgrade.timer
sudo systemctl disable man-db.timer
sudo systemctl disable dpkg-db-backup.timer


echo "enable services"
sudo systemctl daemon-reload
sudo systemctl enable hmi-gateway.service
sudo systemctl enable vlan62.service

sudo systemctl start hmi-gateway.service
sudo systemctl start vlan62.service

# install jre
sudo apt-get install openjdk-10-jre-headless
sudo apt-get install wiringpi_3.10_armhf.deb

sudo reboot





