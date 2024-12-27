#!/bin/bash

current_dir=$(pwd)

java \
  -Dlog4j.configurationFile=file:${current_dir}/conf/log4j2.xml \
  -Dtinylog.configuration=${current_dir}/conf/tinylog.properties \
  -Djava.awt.headless=true \
  -server -cp $(for i in lib/*.jar ; do echo -n $i: ; done). com.bosch.pmt.hmi.tools.ZMQClient "$@"
