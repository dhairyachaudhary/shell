#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

//Initializing history of size 500
char prevcalls[500][100*sizeof(char*)];
int numcalls=0;

int exists(const char* lookingfor){
	//Helper function that returns details about a directory 
	DIR* thisdir=opendir(lookingfor);
	if (thisdir!=NULL){
		return 1;
	} else if (errno==ENOTDIR){
		return 0;
	} return -1;
}

int execute(char** command){
	if (command[0] == NULL) {
		//No command entered
		return 1;
	} 

	else if (strcmp(command[0],"exit")==0){
		//Exit command. Status will be set to zero and hence loop will stop running when this is called.
		return 0;
	} 

	else if (strcmp(command[0],"cd")==0){
		char location[50]; 

		if (command[1]==NULL || strcmp(command[1],"~")==0) {
			//Switches to home directory
			chdir(getenv("HOME"));
			printf("%s %s\n", "Current Directory:", getcwd(location, 50));
		} 

		else if (command[2]!=NULL && command[2]!="-L"){
			//Error Handling
			fprintf(stderr, "uwu: too many arguments\n");
			exit(1);
		} 

		else {
			if (exists(command[1])==1){
				//Switches to directory input by user
				chdir(command[1]); 
				printf("%s %s\n", "Current Directory:", getcwd(location, 50));
			} else {
				//Error handling
				fprintf(stderr, "uwu: no such file or directory\n");
				exit(1);
			}
		}

		return 1;
	} 

	else if (strcmp(command[0],"echo")==0){
		if(command[1]==NULL){
			//No input
			printf("\n");
		}
		else if (command[1]!=NULL){
			if(strcmp(command[1],"*")==0){
				//Implementation of "*" flag
				DIR *d1;
				d1 = opendir("."); 
				struct dirent *bruh;
				while(d1)
				{
					bruh = readdir(d1);
					if (!bruh) break;
					if(bruh->d_name[0]!='.'){
						printf("%s  \t", bruh->d_name);
					}

				}
				closedir(d1);
				printf("\n");
			}

			else if(strcmp(command[1],"-n")==0){
				//Implementation of "-n" flag
				int p=2;

				while(1){
					if(command[p]==NULL){
						break;
					}
					p++;
				}

				int q=2;
				while (q!=p){
					if (q!=2){
						printf(" ");
					}
					printf("%s",command[q]);
					q++;
				}
			}

			else {
				//For valid string input
				int index1=1;
				while(1){
					if(command[index1]==NULL){
						break;
					}
					index1=index1+1;
				}

				for(int i=1;i<index1;i++)
				{
					printf("%s ",command[i]);
				}
				printf("\n");

			} 
		} 

		else {
			fprintf(stderr, "uwu: invalid input\n");
		}
		return 1;
	} 

	else if (strcmp(command[0],"pwd")==0){
		if (command[1]==NULL || strcmp(command[1],"-L")==0 ||  strcmp(command[1],"-P")==0){
			char location[100]; 
			printf("%s\n", getcwd(location, 100));
		} else {
			//Error handling
			fprintf(stderr, "uwu: invalid input\n");
			exit(1);
		}
		return 1;
	} 

	else if (strcmp(command[0],"history")==0){
		if (command[1]==NULL){
			//Prints all elements in history
			for(int i=0;i<numcalls;i++){
				printf("%s",prevcalls[i]);
			}
		} 

		else if (strcmp(command[1],"-c")==0){
			//Clears history
			numcalls=0;
		} 

		else if (strcmp(command[1],"-a")==0){
			//Writes current history to the history file
			FILE *file ; 
			file=fopen("history.txt", "w") ; 

			if (file==NULL) { 
				fprintf(stderr, "uwu: error accessing history file\n");
				exit(1);
			} 

			else { 
				int i=0;
				while (i!=numcalls){
					if (strlen(prevcalls[i])>0) { 
						fputs(prevcalls[i], file) ;    
						fputs("\n", file) ; 
					} 
					i++;
				}
				fclose(file) ; 
			}
		} 

		else {
				//Error handling
			fprintf(stderr, "uwu: invalid input\n");
			exit(1);
		}

		return 1;
	}

	else {
		//For other commands

		char p[]="/home/dhairya/Documents/os1.2/";
		strcat(p,command[0]);
		command[0]=p;

		pid_t pid;
		int status;
		pid = fork();

		if (pid<0) {
			fprintf(stderr, "uwu: invalid command\n");
			exit(1);
		}

		else if (pid==0) {
			if (execvp(command[0],command)==-1) {
				fprintf(stderr, "uwu: invalid command\n");
				exit(1);
			}
			exit(1);
		} 

		else {
			do { 
				wait(NULL); 
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		return 1;
	}
}

int main(int argc, char **argv){
	//loop ends when status is 0
	int status=1;

	while (status){
		printf("\033[0;31muwu's shell>>> \033[0m");

		char *userinput=NULL;
		ssize_t size1=0;
		int getip;

		//Taking user input
		getip=getline(&userinput,&size1,stdin);

		if(getip==-1){
			if(feof(stdin)){
				exit(1);
			}
			else{
				perror("Error 1: ");
				exit(1);
			}
		}

		//Adding command entered to history
		strcpy(prevcalls[numcalls],userinput);
		numcalls++;

		char** separatedinput=malloc(100*sizeof(char*));

		//Processing input
		char *curr;
		curr=strtok(userinput," \n");
		int i=0;
		while(curr!=NULL){
			separatedinput[i]=curr;
			i++;
			curr=strtok(NULL," \n");
		}
		separatedinput[i]=NULL;

		//Calling the execute function that contains the details about all functions
		status=execute(separatedinput);

		//Freeing memory
		free(separatedinput);
		free(userinput);
	}
}
