#include<stdio.h>
#include<string.h>
#include<time.h>

int main(int argc,char **argv) {
	time_t t;
	t = time(NULL);
	struct tm *timeid;

	if(argv[1]==NULL){ 
		timeid = localtime(&t);
		printf("%s", asctime(timeid));
	}

	else if(strcmp(argv[1],"--help")==0){
		printf("Usage: date [OPTION]... [+FORMAT] \n or:  date [-u|--utc|--universal] [MMDDhhmm[[CC]YY][.ss]] \n Display the current time in the given FORMAT \n   -u, --utc, --universal     print or set Coordinated Universal Time (UTC)\n   --help     \t\t      display this help and exit\n");

	}

	else if(strcmp(argv[1],"-u")==0 || strcmp(argv[1],"--utc")==0 || strcmp(argv[1],"--universal")==0){  
		timeid = gmtime(&t);
		printf("%s", asctime(timeid));
	}

	else {
		fprintf(stderr, "uwu: improper format\n");
	}

	return 1;
}