/*****************************************************
 * The TCP socket client to help you to test if your
 * OS supports c1000k(1 million connections).
 * @author: ideawu
 * @link: http://www.ideawu.com/
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>

int main(int argc, char **argv){
	if(argc <=  3){
		printf("Usage: %s ip base-port max-ports \n", argv[0]);
		exit(0);
	}

        time_t start = time(NULL);
        time_t end;
	int pid = getpid();
	struct sockaddr_in addr;
	const char *ip = argv[1];
	int base_port = atoi(argv[2]);
	int max_ports = atoi(argv[3]);
	int opt = 1;
	int bufsize;
	socklen_t optlen;
	int connections = 0;

	memset(&addr, sizeof(addr), 0);
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &addr.sin_addr);

	char tmp_data[10];
	int index = 0;
	while(1){
		if(++index >= max_ports){
			index = 0;
		}
		int port = base_port + index;
		//printf("connect to %s:%d\n", ip, port);

		addr.sin_port = htons((short)port);

		int sock;
		if((sock = socket(AF_INET, /*SOCK_NONBLOCK|*/SOCK_STREAM, 0)) == -1){
			goto sock_err;
		}
		if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){
			if(errno != EINPROGRESS)
				goto sock_err;
		}

		connections ++;

		if(connections % 1000 == 999){
			//printf("press Enter to continue: ");
			//getchar();
			printf("[%d][%d] connections: %d, fd: %d\n", pid, base_port, connections, sock);
		}
		//usleep(1 * 1000);

		//bufsize = 5000;
		//setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
		//setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));
	}

	return 0;
sock_err:
	end = time(NULL);
	printf("connections: %d, time taken = %f sec\n", connections, difftime(end, start));
	printf("error: %s\n", strerror(errno));
	return 0;
}
