#!/bin/bash

echo "Please run at current directory"

# install hmi-gateway
sudo mkdir /opt/hmi-gateway
sudo cp -r ../ /opt/hmi-gateway

echo "install hmi gateway service"
sudo cp hmi-gateway-ipc.service /etc/systemd/system/hmi-gateway.service

echo "enable services"
sudo systemctl daemon-reload
sudo systemctl enable hmi-gateway.service
sudo systemctl start hmi-gateway.service

sudo reboot





