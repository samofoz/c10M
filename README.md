**Note: This repo is a fork of https://github.com/ideawu/c1000k.git**

# c10M
Quest to achieve 10M open socket connections on one commodity server

AWS r5.4xlarge, Ubuntu 22.04 (achieved 16M!)
--------------------------------------------
apt update -y && apt install build-essential -y && git clone https://github.com/samofoz/c10M && cd c10M && make && cp sysctl.conf /etc/ && sysctl --system

Important
---------
Append blacklist.conf contents to /etc/modprobe.d/blacklist.conf. Reboot.

First terminal
---------------
ulimit -n 20000000 && ./server.sh -p 8 -b 7000 -m 64

Second terminal
----------------
ulimit -n 20000000 && ./client.sh -i 127.0.0.1 -p 8 -b 7000 -m 64

(Both server and client will appear hanged after 2M each for 8 processes)
