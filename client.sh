#!/bin/bash -e

trap "kill 0" SIGINT

#### Default Configuration

SERVER_IP=127.0.0.1
PROCESSES=1
MAX_PORTS=32
BASE_PORT=7000

show_help() {
cat << EOF
Naive Stress Test with cURL.
Usage: ./client.sh [-i SERVER_IP] [-b BASE_PORT] [-p PROCESSES] [-m MAX_PORTS]
Params:
  -i  Server ip address
      Defaults 127.0.0.1
  -b  Base port
      Defaults 7000
  -p  how many process to spawn
      Defaults to 1
  -m  Total ports counted from base port
      Defaults to 32
  -h  show this help text
EOF
}


#### CLI
while getopts ":i:p:b:m:h" opt; do
  case $opt in
    i)
      SERVER_IP=$OPTARG
      ;;
    p)
      PROCESSES=$OPTARG
      ;;
    b)
      PORTNO=$OPTARG
      ;;
    m)
      MAX_PORTS=$OPTARG
      ;;
    h)
      show_help
      exit 0
      ;;
    \?)
      show_help >&2
      echo "Invalid argument: $OPTARG" &2
      exit 1
      ;;
  esac
done

shift $((OPTIND-1))

for i in `seq 0 $(($PROCESSES-1))`; do
let BASEP=$BASE_PORT+$((i*MAX_PORTS))
  ./client $SERVER_IP $BASEP $MAX_PORTS & pidlist="$pidlist $!"
done

# Execute and wait
FAIL=0
for job in $pidlist; do
  wait $job || let "FAIL += 1"
done

# Verify if any failed
if [ "$FAIL" -eq 0 ]; then
  echo "SUCCESS!"
else
  echo "Failed Requests: ($FAIL)"
fi
