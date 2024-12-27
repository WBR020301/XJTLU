#!/bin/bash

current_dir=$(pwd)

export BIND_TO_DEVICE=vlan62
export VSOMEIP_CONFIGURATION=${current_dir}/conf/someip-hmi.json
export VSOMEIP_APPLICATION_NAME=Bosch_Head_Unit

java \
  -Xms32m -Xmx128m \
  -DBIND_TO_DEVICE=vlan62  \
  -DVSOMEIP_CONFIGURATION=${current_dir}/conf/someip-hmi.json \
  -DVSOMEIP_APPLICATION_NAME=Bosch_Head_Unit \
  -Dlog4j.configuration=file:${current_dir}/conf/log4j2.xml\
  -server -cp $(for i in lib/*.jar ; do echo -n $i: ; done). com.bosch.pmt.hmi.Main
