#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char *PWD(void);
char **formatCommand(char*);
int createForkPrint(char**);
int createForkOutput(char*, char**);


int main(int argc, char *argv[]) {
	char temp[BUFSIZ];
	while((gets(temp,256,stdin)) != EOF) {
		if(strcmp(temp, "exit") == 0) {
			//If the input from the user is exit then close the program by returning 0
			printf("Closing Krash\n");
			return 0;
		} else if(strcmp(temp, "pwd") == 0) {
			//If the input from the use is pwd run the pwd function.
			printf("%s\n", PWD());
		} else if (strcmp(temp, "help") == 0) {
			//If the input from the user is help run the print help function.
			printHelp();
		} else if(strstr(temp, "cd")) {
			//If the input from the user includes cd run the cd function.
			CD(temp);
		} else if(strstr(temp, ">")) {
			char *last = strrchr(temp, ' ');
			if (last != NULL) {
    			char *filename = last+1; //get the filename
    			char *command = strtok(temp, ">");
				char **commands = formatCommand(command); //format the commands
				createForkOutput(filename, commands);
			} else {
				printf("%s\n", "Error with the filename");
			}
		} 
		else {
			char **commands = formatCommand(temp);
			createForkPrint(commands);
		}
	}

	return 0;

}

/*
Name: formatCommand
Description: Function takes a string of commands and loops through them and adds them to an array of strings.
Inputs: a string
Ouputs: array of strings
*/
char **formatCommand(char *string) {
	char *ret; 
	ret = strtok(string, " ");
	char **stringArray = malloc(3 * sizeof(char*));
	int i = 0;
	
	while( ret != NULL ) {
		stringArray[i] = malloc(20 * sizeof(char));
		stringArray[i] = ret;
		i++;
		ret = strtok(NULL, " ");
	}
	stringArray[i] = NULL;
	return stringArray;
}

/*
Name: CD
Description: Function changes current working directory
Inputs: file path to change location to.
Ouputs: NA
*/
void CD(char *str) {
	char *token;
	token = strtok(str, " ");
	while(token != NULL) {
		if (strcmp(token, "cd") != 0) {
			chdir(token);
		}
	token = strtok(NULL, " ");
	}
}

/*
Name: PWD
Description: Function to print the current working directory.
Inputs: None
Ouputs: Returns string of the current working directory
*/
char *PWD(void) {
	static char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		return 'Could not get directory.';
	}
	else {
		return cwd;
	}
}

/*
Name: createForkOutput
Description: Function to create a child fork and use it to execute a bash command
Inputs: array of commands, filename
Ouputs: returns process id
*/
int createForkOutput(char filename[], char **arguments) {
	int pid = fork();
	int status;
	if (pid < 0) {
		return pid;
	} else if (pid == 0) {
		close(STDOUT_FILENO);
		open(filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
		char a[] = "/bin/";
		strcat(a, arguments[0]);
		execvp(a, arguments);
		return pid;
	} else {
		wait(&status);
		return pid;
	}
	return pid;
}

/*
Name: createForkPrint
Description: Function to create a child fork and use it to execute a bash command, prints to stdout
Inputs: array of commands
Ouputs: returns process id
*/
int createForkPrint(char **arguments) {
	int pid = fork();
	int status;
	if (pid < 0) {
		return pid;
	} else if (pid == 0) {
		char a[] = "/bin/";
		strcat(a, arguments[0]);
		execv(a, arguments);
		return pid;
	} else {
		wait(&status);
		return pid;
	}
	return pid;
}

/*
Name: printHelp
Description: Function that prints a help message for Krash's tools
Inputs: NA
Ouputs: NA
*/
void printHelp() {
	printf("'exit' - close program\n");
	printf("'pwd' - print working directory\n");
	printf("'cd' - change directory\n");
	printf("'help' - more information about the use of Krash\n");
}