#!/bin/bash

current_dir=$(pwd)

java -Xms2m -Xmx8m\
  -server -cp $(for i in lib/hmi-gateway-*.jar ; do echo -n $i: ; done). com.bosch.pmt.hmi.util.DesktopNotification

