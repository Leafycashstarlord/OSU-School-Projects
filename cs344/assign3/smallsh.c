//Name: Jackson E. Rollins
//Date: 2/10/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int isBackground = 1;

//Function that catches the SIGTSTP call, toggling the allowance of background processes
void catchSIGTSTP(int signal){
	char* message;
	int msgLen;
	if(isBackground == 1){
		message = "Entering foreground-only mode (& is now ignored)\n";
		msgLen = 49;
		isBackground = 0;
	}else{
		message = "Exiting foreground-only mode\n";
		msgLen = 29;
		isBackground = 1;
	}

	write(1, message, msgLen);
	fflush(stdout);
}

//Function that takes user input and parses it into character arrays
void getUserInput(char* uInput[], int* fgbg, char fileIn[], char fileOut[], int cpid){
	char input[512];

//Input prompt
	printf(": ");
	fflush(stdout);
	fgets(input, 512, stdin);

//Parse data & variable expansion
	char* token = strtok(input, " \n");
	for(int i = 0; token; i++){
		if(strcmp(token, "&") == 0){
			*fgbg = 1;
		}else if(strcmp(token, "<") == 0){
			token = strtok(NULL, " \n");
			strcpy(fileIn, token);
		}else if(strcmp(token, ">") == 0){
			token = strtok(NULL, " \n");
			strcpy(fileOut, token);
		}else{
			uInput[i] = strdup(token);
			for(int j = 0; uInput[i][j]; j++){
				if(uInput[i][j] == '$' && uInput[i][j+1] == '$'){
					uInput[i][j] = '\0';
					snprintf(uInput[i], 512, "%s%d", uInput[i], cpid);
				}
			}
		}
		token = strtok(NULL, " \n");
	}
}

//Function that executes any other commands given from the user
void otherCommands(char* uInput[], int* fgbg, char fileIn[], char fileOut[], int cpid, int* status, struct sigaction SA){
	int fIn;
	int fOut;

//Forking
	cpid = fork();
	switch(cpid){
		case -1:
			perror("Error\n");
			exit(1);
			break;

		//Handles input/output redirection, default cntl+C, and execution
		case 0:
			SA.sa_handler = SIG_DFL;
			sigaction(SIGINT, &SA, NULL);

			if(strcmp(fileIn, "")){
				fIn = open(fileIn, O_RDONLY);
				if(fIn == -1){
					printf("cannot open %s for input\n", fileIn);
					fflush(stdout);
					exit(1);
				}
				if(dup2(fIn, 0) == -1){
					perror("dup2");
					exit(2);
				}
				fcntl(fIn, F_SETFD, FD_CLOEXEC);
			}else if(*fgbg){
				fIn = open("dev/null", O_RDONLY);
				if(fIn == -1){
					perror("open");
					exit(1);
				}
				if(dup2(fIn, 0) == -1){
					perror("dup2");
					exit(2);
				}
			}

			if(strcmp(fileOut, "")){
				fOut = open(fileOut, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fOut == -1){
					printf("cannot open %s\n", fileOut);
					fflush(stdout);
					exit(1);
				}
				if(dup2(fOut, 0) == -1){
					perror("dup2");
					exit(2);
				}
				fcntl(fOut, F_SETFD, FD_CLOEXEC);
			}

			if(execvp(uInput[0], uInput)){
				printf(" %s is not a valid command\n", uInput[0]);
				fflush(stdout);
				exit(2);
			}
			break;
		
		//Wait for foreground to finish
		default:
			if(*fgbg && isBackground){
				printf("Background PID: %i\n", cpid);
				break;
			}else{
				waitpid(cpid, status, 0);
			}
	}
}

//Main function that takes the input, processes the commands, and then executes them if something
//else wasn't called for
int main(int argc, char *argv[]){
	char fileIn[256] = "";
	char fileOut[256] = "";
	char* uInput[512];

	int status = 0;
	int fgbg = 0;
	int cpid = getpid();
	int prompt = 1;

	struct sigaction SIGINT_action = {{0}};
	struct sigaction SIGTSTP_action = {{0}};
	
	//Single Handlers
	SIGINT_action.sa_handler = SIG_IGN;
	SIGINT_action.sa_flags = 0;
	sigfillset(&SIGINT_action.sa_mask);
	sigaction(SIGINT, &SIGINT_action, NULL);

	SIGTSTP_action.sa_handler = catchSIGTSTP;
	SIGTSTP_action.sa_flags = 0;
	sigfillset(&SIGTSTP_action.sa_mask);
	sigaction(SIGTSTP, &SIGTSTP_action, NULL);

	do{
		//Get user input
		getUserInput(uInput, &fgbg, fileIn, fileOut, cpid);

		//Checks for commnets/blank lines, the stats/cd/exit commands, and other commands
		if(uInput[0][0] == '\0' || uInput[0][0] == '#'){
			continue;
		}else if(strcmp(uInput[0], "status") == 0){
			if(WIFEXITED(status)){
				printf("exit value %i\n", WEXITSTATUS(status));
			}else{
				printf("terminated by signal %i\n", status);
			}
		}else if(strcmp(uInput[0], "cd") == 0){
			if(uInput[1] == NULL){
				chdir(getenv("HOME"));
			}else{
				chdir(uInput[1]);
			}
		}else if(strcmp(uInput[0], "exit") == 0){
			prompt = 0;
		}else{
			otherCommands(uInput, &fgbg, fileIn, fileOut, cpid, &status, SIGINT_action);
		}
		
		//Cleans up variables and files
		for(int i = 0; uInput[i]; i++){
			uInput[i] = NULL;
		}
		fgbg = 0;
		fileIn[0] = '\0';
		fileOut[0] = '\0';

		//Call the exit status
		cpid = waitpid(-1, &status, WNOHANG);
		while(cpid > 0){
			printf("background process %i is done: ", cpid);
			if(WIFEXITED(status)){
				printf("exit value %i\n", WEXITSTATUS(status));
			}else{
				printf("terminated by signal %i\n", status);
			}
			cpid = waitpid(-1, &status, WNOHANG);
		}
	}while(prompt);

	return 0;
}
