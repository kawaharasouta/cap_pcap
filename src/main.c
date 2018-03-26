#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"initrawsock.h"

int main(int argc, char **argv){
	int sock, size;
	char buf[2048];

	if (argc < 2){
		fprintf(stderr, "usage: ./main [dev-name]\n");
		exit(1);
	}

	if (sock = initrawsock(argv[1], 1, 0) < 0){
		fprintf(stderr, "InitRawSocket:error:%s\n", argv[1]);
		exit(1);
	}

	while (1){
		if ((size = read(sock, buf, sizeof(buf)) < 0)){
			perror("read");
		}
		else{
#if 0
			hexdump(buf, strlen(buf));
#else
			hexdump(buf, size);
#endif
		}
	}
}


void hexdump(u_int16_t *buf, int size){
	int i;
	for (i = 0;i < size; i++){
		fprintf(stdout, "%04x ", *(buf + i));
		if ((i + 1) % 8 == 0){
			fprintf(stdout, "\n");
		}
	}
	fprintf(stdout, "\nfin\n");
}
