#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define		PB_SIZE		15
#define		ERR_PSTRUCTALL	-1
#define		ERR_PSTRALL	-2
#define		ERR_FO		-3

const char *FOUTFORMAT = "%s";
const char *OUTPUTFILENAME = "./out.txt";

typedef struct packet_s
{
	FILE *fp;
	char *pmex;
	unsigned int pmsize;
} packet_t;

void *kblistener(packet_t*);

int main(int args, char *argc[])
{
	packet_t *packet = (packet_t*) malloc(sizeof(packet_t));

	if(packet == NULL)
	{
		fprintf(stdout, "#%d: Bad packet pointer allocation!\n", ERR_PSTRUCTALL);
		return ERR_PSTRUCTALL;
	}

	packet->pmex = (char*) malloc(PB_SIZE * sizeof(char));

	if(packet->pmex == NULL)
	{
		fprintf(stdout, "#%d: Bad packet string message allocation!\n", ERR_PSTRALL);
		return ERR_PSTRALL;
	}

	if((packet->fp = fopen(OUTPUTFILENAME, "w+")) == NULL)
	{
		fprintf(stdout, "#%d: Error in file opening!\n", ERR_FO);
		return ERR_FO;
	}

	while(kblistener(packet));

	if(packet->fp)		fclose(packet->fp);
	if(packet->pmex)	free(packet->pmex);
	if(packet)		free(packet);
	return 0;
}

void *kblistener(packet_t *packet)
{
	fgets(packet->pmex, PB_SIZE, stdin);
	packet->pmex[strlen(packet->pmex)-1] = '\0';
	packet->pmsize = strlen(packet->pmex);
	if(!strcmp(packet->pmex, "eof"))
	{
		fprintf(packet->fp, "\n");
		return NULL;
	}
	fprintf(packet->fp, FOUTFORMAT, packet->pmex);
	return (void*) 1;
}
