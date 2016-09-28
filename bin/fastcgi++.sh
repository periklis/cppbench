#!/bin/bash
BIND=127.0.0.1:9000
USER=www-data

FCGIPP_CGI=$1
FCGIPP_CGI_NAME=`basename $FCGIPP_CGI`
FCGIPP_CGI_ARGS="- USER=$USER PATH=/usr/bin $FCGIPP_CGI"
RETVAL=0

start() {
      echo -n "Starting FastCGI++ App: "
      start-stop-daemon --quiet --start --background --chuid "$USER" --exec /usr/bin/env -- $FCGIPP_CGI_ARGS
      RETVAL=$?
      echo "$FCGIPP_CGI_NAME."
}

stop() {
      echo -n "Stopping FastCGI++ App: "
      killall -q -w -u $USER $FCGIPP_CGI
      RETVAL=$?
      echo "$FCGIPP_CGI_NAME."
}

case "$2" in
    start)
      start
  ;;
    stop)
      stop
  ;;
    restart)
      stop
      start
  ;;
    *)
      echo "Usage: fastcgi++.sh {start|stop|restart}"
      exit 1
  ;;
esac
exit $RETVAL
