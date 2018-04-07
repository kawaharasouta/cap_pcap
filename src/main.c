#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"initrawsock.h"

int main(int argc, char **argv, char *envp[]){
	int sock, size;
	u_char buf[2048];

	if (argc < 2){
		fprintf(stderr, "usage: ./main [dev-name]\n");
		exit(1);
	}

	if ((sock = initrawsock(argv[1], 0, 0)) < 0){
		fprintf(stderr, "InitRawSocket:error:%s\n", argv[1]);
		exit(1);
	}

	//printf("sock: %d\n",sock);

	while (1){
		if (((size = read(sock, buf, sizeof(buf))) <= 0)){
			perror("read");
			printf("read 0\n");

		}
		else{
#if 0
			printf("size: %d\n",size);
			hexdump(buf, strlen(buf));
#else
			printf("size: %d\n",size);
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
