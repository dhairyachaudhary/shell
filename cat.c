#include<stdio.h>
#include<string.h>

int exists(const char *fname)
{
	FILE *file;
	if ((file = fopen(fname, "r")))
	{
		fclose(file);
		return 1;
	}
	return 0;
}

int main(int argc,char **argv){


	if(argv[1]==NULL){
		fprintf(stderr, "uwu: \"cat\" missing operand\n");
	}

	else{

		int pos1=0, pos2=0, option=0;

		int i=1;

		while(argv[i]!=NULL){
			if (strcmp(argv[i],"-n")==0 && option==0){
				option=1;
				pos1=i;
			} 

			else if (strcmp(argv[i],"-n")==0 && option!=0 && option!=1){
				option=3;
				pos2=i;
			} 

			else if (strcmp(argv[i],"-E")==0 && option==0){
				option=2;
				pos1=i;
			} 

			else if (strcmp(argv[i],"-E")==0 && option!=0 && option!=2){
				option=3;
				pos2=i;
			} 

			i++;

		}

		if (option==0){

			int j=1;
			while (argv[j]!=NULL){
				if(exists(argv[j])==0){
					fprintf(stderr, "uwu: file not found\n");
				}

				else{
					FILE *file;
					char line[100];
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("\n");
						}
						printf("%s",line);
						it++;
					}
					fclose(file);
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

				if(exists(argv[j])==0){
					fprintf(stderr, "uwu: file not found\n");
				}

				else{
					FILE *file;
					char line[100];
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("\n");
						}
						printf("     %d  %s",(it+1),line);
						it++;
					}
					fclose(file);
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

				if(exists(argv[j])==0){
					fprintf(stderr, "uwu: file not found\n");
				}

				else{
					FILE *file;
					char line[100];
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("$\n");
						}
						printf("%s",line);
						it++;
					}
					fclose(file);
				}
				j++;
			}

			
		}

		else if (option==3){

			int j=1;
			while (argv[j]!=NULL){
				if (j==pos1){
					j++;
					continue;
				}

				if(exists(argv[j])==0){
					fprintf(stderr, "uwu: file not found\n");
				}

				else{
					FILE *file;
					char line[100];
					file=fopen(argv[j],"r");
					int it=0;
					while(fscanf(file,"%[^\n]\n",line)!=EOF){
						if (it!=0){
							printf("$\n");
						}
						printf("     %d  %s",(it+1),line);
						it++;
					}
					fclose(file);
				}
				j++;
			}

		} 

		else {
			fprintf(stderr, "uwu: improper format\n");
		}

	}

	return 1;
	
}