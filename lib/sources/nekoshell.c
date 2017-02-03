#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PATH_BUFF 256
#define MAX_ARGS 20

void writePrompt(){
	char path[PATH_BUFF];
	getcwd(path, PATH_BUFF);
	
	printf("nekoshell:[%s]>> ", path);
}

void changeDirectory(char *path){
	if(path == NULL) return;

	int cdStatus = chdir(path);
	if(cdStatus == -1){
		perror("cd error");
	}
	
}

void clearCommand(char *command){
	int commandLength = strlen(command);
	if(command[commandLength - 1] == '\n'){
		command[commandLength - 1] = '\0';
	}
}

void listenCommand(){
	writePrompt();

	char *command = NULL;
	int len = 0;
	int read = getline(&command, &len, stdin);

	if(read > 1){
		// clear command (remove new line if exist)
		clearCommand(command);

		char *commandArguments;
		commandArguments = strtok(command, " ");
		if(strcmp(commandArguments, "cd") == 0){

			commandArguments = strtok (NULL, " ");
			
			changeDirectory(commandArguments);
			
			return;
			
		}

		if(strcmp(commandArguments, "exit") == 0){
			exit(0);
		}

		// if its not shell command then its a program

		char fullPath[20];
		char *appName = commandArguments;
		char *pathToProgram = "/bin/";
		strcpy(fullPath, pathToProgram);
		strcat(fullPath, commandArguments);
		
		// run app in new process and wait for results
		int pid = fork();
		if(pid == 0){
			char *args[MAX_ARGS];
			args[0] = appName;
			int i;
			for(i = 1; i < MAX_ARGS - 2 && commandArguments != NULL; i++){
				commandArguments = strtok (NULL, " ");
				args[i] = commandArguments;
			}
			args[i] = 0;

			execvp(fullPath, args);
			perror("error");
			exit(1);

		} else{
			int status;
			wait(&status);
		}
	}

}
