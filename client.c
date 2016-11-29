/* client code*/
#include <stdio.h>
#include <rpc/rpc.h>
// #include <netconfig.h>
#include <stdlib.h>
#include "date.h"

main(argc, argv)
int argc;
char **argv;
{
	CLIENT *c1;
	char *server;
	long *lresult; /* return from bin_date_1 */
	char **sresult; /*return from str_date_1 */

	if (argc!=2) {
		fprintf(stderr, "usage: %s hostname\n", argv[0]);
		exit(1);
	}
	server = argv[1];/* get the name of server*/
	/*creat the client handle*/
	if ((c1=clnt_creat(server,DATE_PROG,DATE_VERS, "netpath"))==NULL) {
		clnt_pcreateerror(server);
		exit(1);
	}
	/* call the procedure bin_Date*/
	if ((lresult=bin_date_1(NULL, c1))==NULL){
		clnt_perror(c1,server);
		exit(1);
	}
	printf("time on %s is %1ld\n", server, *lresult);
	/*have the server convert the result to a date string */
	if ((sresult=str_date_1(lresult,c1))==NULL) {
		clnt_perror(c1,server);
		exit(1);
	}
	printf("date is %s\n", *sresult);
	clnt_destroy(c1); /*get rid of client handle*/
	exit(0);
}