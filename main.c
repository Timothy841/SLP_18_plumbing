#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define PC 0
#define CP 1
#define READ 0
#define WRITE 1

void change(char *line){
	for (int i = 0; i<strlen(line); i++){
		if (line[i] == 'h'){
			line[i] = 'H';
		}
	}
}

int main(){
	int fds[2][2];
	pipe(fds[PC]);
	pipe(fds[CP]);
	char line[100];
	printf("This changes 'h' to 'H'\n");
	int f = fork();
	while (1){
		if (f){//parent
			printf("Input:\n");
			char input[100];
			fgets(input, 100, stdin);
			write(fds[PC][WRITE], input, 100);
			read(fds[CP][READ], line, sizeof(line));
			printf("%s", line);
		}
		else{//child
		  read(fds[PC][READ], line, sizeof(line));
		  change(line);
		  write(fds[CP][WRITE], line, sizeof(line));
		}
	}
}
