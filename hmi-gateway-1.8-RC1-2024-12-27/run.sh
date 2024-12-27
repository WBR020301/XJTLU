#!/bin/bash

current_dir=$(pwd)

export BIND_TO_DEVICE=vlan62
export VSOMEIP_CONFIGURATION=${current_dir}/conf/someip-hmi.json
export VSOMEIP_APPLICATION_NAME=Bosch_HMI_GW
export APPLICATION_CONFIGURATION=${current_dir}/conf/application.json

java -Xms16m -Xmx64m\
  -DBIND_TO_DEVICE=vlan62  \
  -DVSOMEIP_CONFIGURATION=${current_dir}/conf/someip-hmi.json \
  -DVSOMEIP_APPLICATION_NAME=Bosch_HMI_GW \
  -DAPPLICATION_CONFIGURATION=${current_dir}/conf/application.json \
  -Dlog4j.configurationFile=${current_dir}/conf/log4j2.xml \
  -Djava.awt.headless=true \
  -server -cp $(for i in lib/*.jar ; do echo -n $i: ; done). com.bosch.pmt.hmi.Main
