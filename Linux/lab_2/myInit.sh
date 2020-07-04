#!/bin/sh
### BEGIN INIT INFO
# Provides:          myInit
# Required-Start:    $syslog $time $remote_fs
# Required-Stop:     $syslog $time $remote_fs
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
### END INIT INFO

PATH=/etc/init.d
DAEMON=/urs/local/sbin/myInit.sh

        KIND="myInit.sh"
        start() {
                echo -n "Starting $KIND services: "
                /usr/local/sbin/logStart.sh
                echo
        } 

        stop() {
                echo -n "Shutting down $KIND services: "
                /usr/local/sbin/logDown.sh
                echo
        } 

        case "$1" in
          start)
                  start
                ;;
          stop)
                  stop
                ;;
          *)
                echo $"Usage: $0 {start|stop|restart}"
                exit 1
        esac
        exit $?