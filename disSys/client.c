#include<stdio.h>
#include<rpc/rpc.h>
#include<netconfig.h>
#include"date.h"

main(argc, argv)
int argc;
char **argv;
{
	CLIENT *c1;
	char *server;
	long *lresult;
	char **sresult;

	if (argc != 2){
		fprintf(stderr, "usage: %s hostname\n", argv[0]);
		exit(1);
	}
	server = argv[1];

	if ((c1=clnt_create(server, DATE_PROG, DATE_VERS, "netpath")) == NULL){
		clnt_pcreateerror(server);
		exit(1);
	}
	
	if ((lresult=bin_date_1(NULL, c1)) == NULL){
		clnt_perror(c1, server);
		exit(1);
	}
	printf("time on %s is %ld\n", server, *lresult);

	if ((sresult=str_date_1(lresult, c1)) == NULL){
		clnt_perror(c1, server);
		exit(1);
	}
	printf("date is %s\n", *sresult);
	clnt_destroy(c1);
	exit(0);
}
