#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pcap.h>

#include<sys/time.h>

#include"initrawsock.h"

void print_0xpcaphdr(struct pcap_file_header *pcap_hdr);

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

	struct pcap_file_header pcap_hdr;
	struct pcap_pkthdr pkt_hdr;

	/*struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);*/

	pcap_hdr.magic = (bpf_int32)0xa1b2c3d4;
	//pcap_hdr.magic = TCPDUMP_MAGIC;???
	pcap_hdr.version_major = PCAP_VERSION_MAJOR;
	pcap_hdr.version_minor = PCAP_VERSION_MINOR;
	pcap_hdr.thiszone = 0;
	pcap_hdr.sigfigs = 0;
	pcap_hdr.snaplen = 0x00040000;
	pcap_hdr.linktype = 0x00000001;

	//gettimeofday(&(pkt_hdr.ts), 0);

	FILE *fp;
	fp = fopen("test.pcap", "wb");

	while (1){
		if (((size = read(sock, buf, sizeof(buf))) <= 0)){
			perror("read");
		}
		else{
#if 1
			printf("***\n");
			gettimeofday(&(pkt_hdr.ts), 0);
			pkt_hdr.caplen = size;
			pkt_hdr.len = size;

			print_0xpcaphdr(&pcap_hdr);
#else
			printf("size: %d\n",size);
			hexdump(buf, size);
#endif

			fclose(fp);
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

void output_pcaphdr(struct pcap_file_header *pcap_hdr, FILE *fp){
	
}

void print_0xpcaphdr(struct pcap_file_header *pcap_hdr){
	printf("%08x\n", htonl(pcap_hdr->magic));
	printf("%04x\n", htons(pcap_hdr->version_major));
	printf("%04x\n", htons(pcap_hdr->version_minor));
	printf("%08x\n", htonl(pcap_hdr->thiszone));
	printf("%08x\n", htonl(pcap_hdr->sigfigs));
	printf("%08x\n", htonl(pcap_hdr->snaplen));
	printf("%08x\n", htonl(pcap_hdr->linktype));
}
