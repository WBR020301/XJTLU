@echo off

set CP="lib/*"

java -DVSOMEIP_APPLICATION_NAME=Bosch_HMI_GW -DVSOMEIP_CONFIGURATION=conf/someip-hmi.json -DBIND_TO_DEVICE=vlan62 -Djava.awt.headless=true -Dtinylog.configuration=conf/tinylog.properties -DAPPLICATION_CONFIGURATION=conf/application.json -cp %CP% %JAVA_OPTS% com.bosch.pmt.hmi.Main
