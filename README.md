# c10M
Quest to achieve 10M open socket connections on one commodity server

git clone ./server.sh -p 8 -b 7000 -m 32.git
cd c10M
make
cp sysctl.conf /etc/
sysctl --system

First terminal
---------------
./server.sh -p 8 -b 7000 -m 32

Second terminal
----------------
./client.sh -i 127.0.0.1 -p 8 -b 7000 -m 32

