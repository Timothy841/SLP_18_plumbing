#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
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
	int fds[2];
	pipe( fds );
	char line[100];
	int f = fork();
	if (f){//parent
		printf("Input:\n");
		write( fds[WRITE], "hello!", 7);
		read( fds[READ], line, sizeof(line) );
		printf("%s\n", line);
	}
	else{//child
	  read( fds[READ], line, sizeof(line) );
	  printf("%s\n", line);
	  change(line);
	  write(fds[WRITE], line, sizeof(line));
	  return 0;
	}
}