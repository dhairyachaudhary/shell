#include<stdio.h> 
#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int exists(const char* lookingfor){
	DIR* thisdir=opendir(lookingfor);

	if(thisdir!=NULL){
		closedir(thisdir);
		return 0;
	} else if(errno==ENOTDIR) {
		return 1;
	} return -1;
}

int main(int c, char *argv[]) { 
	
	if(argv[1]==NULL){
		fprintf(stderr, "uwu: \"rm\" missing operand\n");
	}

	else{
		int pos1=0, pos2=0, option=0;

		int i=1;

		while(argv[i]!=NULL){
			if (strcmp(argv[i],"-i")==0 && option==0){
				option=1;
				pos1=i;
			} 

			else if (strcmp(argv[i],"-i")==0 && option!=0 && option!=1){
				option=3;
				pos2=i;
			} 

			else if (strcmp(argv[i],"-v")==0 && option==0){
				option=2;
				pos1=i;
			} 

			else if (strcmp(argv[i],"-v")==0 && option!=0 && option!=2){
				option=3;
				pos2=i;
			} 

			i++;

		}

		if (option==0){

			int j=1;

			while (argv[j]!=NULL){
				if(exists(argv[j])==1){
					remove(argv[j]);    
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
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

				if(exists(argv[j])==1){
					char* a=NULL;
					ssize_t sizea=0;
					printf("rm: remove file %s? ",argv[j]);
					getline(&a, &sizea, stdin);
					if(strcmp(a,"y\n")==0){
						remove(argv[j]);
					} else {
						//do nothing
					}
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
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

				if(exists(argv[j])==1){
					printf("%s\n",argv[j]);
					remove(argv[j]);   
				}
				else{
					fprintf(stderr, "uwu: improper format\n");
				}

				j++;

			}
		} 

		else if (option==3) {

			int j=1;

			while (argv[j]!=NULL){

				if (j==pos1 || j==pos2){
					j++;
					continue;
				}

				if(exists(argv[j])==1){
					char* a=NULL;
					ssize_t sizea=0;
					printf("rm: remove file %s? ",argv[j]);
					getline(&a, &sizea, stdin);
					if(strcmp(a,"y\n")==0){
						printf("removed %s\n",argv[j]);
						remove(argv[j]);
					} else {
						//do nothing
					}
				}

				else {
					fprintf(stderr, "uwu: improper format\n");
				}


				j++;
			}

		}

		else {
			fprintf(stderr, "uwu: improper format\n");
		}


		return 1; 

	}
}