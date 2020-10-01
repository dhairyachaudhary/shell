#include <dirent.h>
#include<string.h>
#include<stdio.h>

int main(int argc, char **argv) {
	DIR *directory1;
	struct dirent *de;

	int pos1=0, pos2=0, option=0, isargpresent=0;

	int i=1;

	while (argv[i]!=NULL){
		if (strcmp(argv[i],"-1")==0 && option==0){
			option=1;
			pos1=i;
		} 

		else if (strcmp(argv[i],"-1")==0 && option!=0 && option!=1){
			option=3;
			pos2=i;
		} 

		else if (strcmp(argv[i],"-a")==0 && option==0){
			option=2;
			pos1=i;
		} 

		else if (strcmp(argv[i],"-a")==0 && option!=0 && option!=2){
			option=3;
			pos2=i;
		} 

		else if (strcmp(argv[i],"-a")!=0 && strcmp(argv[i],"-1")!=0){
			isargpresent=1;
		}

		i++;
	}

	if (option==0){

		if (isargpresent==1){

			int j=1;

			while (argv[j]!=NULL){
				directory1 = opendir(argv[j]);

				if (directory1==NULL){
					fprintf(stderr, "uwu: cannot open specified directory\n");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((de = readdir(directory1)) != NULL){
					if((de->d_name[0]!='.')){
						printf("%s\t ", de->d_name);
					}
				}

				printf("\n\n");
				closedir(directory1);
				j++;
			}

		} else {

			directory1 = opendir(".");

			if (directory1==NULL){
				fprintf(stderr, "uwu: cannot open specified directory\n");
				return 1;
			}

			while ((de = readdir(directory1)) != NULL){
				if((de->d_name[0]!='.')){
					printf("%s\t ", de->d_name);
				}
			}
			printf("\n");
			closedir(directory1);
		}
	}

	else if (option==1){

		if (isargpresent==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==pos1){
					j++;
					continue;
				}

				directory1 = opendir(argv[j]);

				if (directory1==NULL){
					fprintf(stderr, "uwu: cannot open specified directory\n");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((de = readdir(directory1)) != NULL){
					if((de->d_name[0]!='.')){
						printf("%s\n", de->d_name);
					}
				}

				printf("\n");
				closedir(directory1);
				j++;
			}

		} else {

			directory1 = opendir(".");

			if (directory1==NULL){
				fprintf(stderr, "uwu: cannot open specified directory\n");
				return 1;
			}

			while ((de = readdir(directory1)) != NULL){
				if((de->d_name[0]!='.')){
					printf("%s\n", de->d_name);
				}
			}
			closedir(directory1);
		}

	}

	else if (option==2){
		if (isargpresent==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==pos1){
					j++;
					continue;
				}

				directory1 = opendir(argv[j]);

				if (directory1==NULL){
					fprintf(stderr, "uwu: cannot open specified directory\n");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((de = readdir(directory1)) != NULL){
					printf("%s\t ", de->d_name);
				}

				printf("\n\n");
				closedir(directory1);
				j++;
			}

		} else {

			directory1 = opendir(".");

			if (directory1==NULL){
				fprintf(stderr, "uwu: cannot open specified directory\n");
				return 1;
			}

			while ((de = readdir(directory1)) != NULL){
				printf("%s\t ", de->d_name);
			}
			printf("\n");
			closedir(directory1);
		}
	}

	else if (option==3){
		if (isargpresent==1){

			int j=1;

			while (argv[j]!=NULL){

				if (j==pos1 || j==pos2){
					j++;
					continue;
				}

				directory1 = opendir(argv[j]);

				if (directory1==NULL){
					fprintf(stderr, "uwu: cannot open specified directory\n");
					j++;
					continue;
				}

				printf("%s:\n", argv[j]);

				while ((de = readdir(directory1)) != NULL){
					printf("%s\n", de->d_name);
				}

				printf("\n");
				closedir(directory1);
				j++;
			}

		} else {

			directory1 = opendir(".");

			if (directory1==NULL){
				fprintf(stderr, "uwu: cannot open specified directory\n");
				return 1;
			}

			while ((de = readdir(directory1)) != NULL){
				printf("%s\n", de->d_name);
			}
			closedir(directory1);
		}
	}

	else {
		fprintf(stderr, "uwu: improper format\n");
	}

	return 1;
}
