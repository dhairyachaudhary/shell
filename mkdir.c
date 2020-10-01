#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int d_exists(const char *path)
{
	struct stat probs;
	stat(path, &probs);
	if (S_ISDIR(probs.st_mode)){
		return 0;
	}
	return 1;
}


int main(int argc,char **argv)
{

	if(argv[1]==NULL){
		fprintf(stderr, "uwu: \"mkdir\" missing operand\n");
	}

	int pos1=0, pos2=0, option=0, isargpresent=0;

	int i=1;

	while(argv[i]!=NULL){
		if (strcmp(argv[i],"-v")==0 && option==0){
			option=1;
			pos1=i;
		} 

		else if (strcmp(argv[i],"-v")==0 && option!=0 && option!=1){
			option=3;
			pos2=i;
		} 

		else if (strcmp(argv[i],"-p")==0 && option==0){
			option=2;
			pos1=i;
		} 

		else if (strcmp(argv[i],"-p")==0 && option!=0 && option!=2){
			option=3;
			pos2=i;
		} 

		i++;

	}

	if (option==0){
		int j=1;

		while (argv[j]!=NULL){

			if(d_exists(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(check){
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}

			j++;
		}
	}

	else if (option==1){
		int j=1;

		while (argv[j]!=NULL){

			if (j==pos1){
				j++;
				continue;
			}

			if(d_exists(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(!check){
					printf("mkdir: created directory %s\n",argv[j]);
				}
				else{
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}


			j++;
		}
	}

	else if (option==2){
		int j=1;

		while (argv[j]!=NULL){

			if (j==pos1){
				j++;
				continue;
			}


			if(d_exists(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(check){
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}


			j++;
		}

	}

	else if (option==3){
		int j=1;

		while (argv[j]!=NULL){

			if (j==pos1 || j==pos2){
				j++;
				continue;
			}


			if(d_exists(argv[j])){
				int check;
				char* dirname=argv[j];
				check=mkdir(dirname,0777);

				if(!check){
					printf("mkdir: created directory %s\n",argv[j]);
				}
				else{
					fprintf(stderr, "uwu: directory not created\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "uwu: file aready exists\n");
			}


			j++;
		}
	}

	else {
		fprintf(stderr, "uwu: improper format\n");
	}

	return 1;

}