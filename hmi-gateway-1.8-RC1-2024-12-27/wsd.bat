@echo off

set CP="lib/*"

java -Xms32m -Xmx128m -cp %CP% %JAVA_OPTS% MonoWebSocketServer