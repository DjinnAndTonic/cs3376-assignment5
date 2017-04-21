// file: TwoPipesTwoChildren.cpp
// author: Chanh-Brian Nguyen
// date: 04/07/2017
// purpose: CS3376
// description:
// this program executes "ls -ltr | grep 3376 | wc -l", by dividing the three commands using 2 children processes and a parent process
//among the child and parent process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char **argv){
	int status;
	int childpid, child2pid;
	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};
	char *wc_args[] = {"wc", "-l", NULL};

	// create one pipe to send the output of "ls" process to "grep" process
	int pipes[2];
	pipe(pipes);

	int pipes2[2];
	pipe(pipes2);
	
	//printf("testpoint1");
		
	// fork the first child (to execute cat)
	if((childpid = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}
	if (childpid == 0) {

		//printf("testpoint2");
		// replace cat's stdout with write part of 1st pipe
		dup2(pipes[1], 1);
		// close all pipes (very important!); end we're using was safely copied
		close(pipes[0]);
		close(pipes[1]);
		execvp(*cat_args, cat_args);
		exit(0);
			
	}
	if((child2pid = fork()) == -1){
		perror("Error creating a child process");
		exit(1);
	}
	if(child2pid == 0){
		//printf("testpoint3");
		dup2(pipes[0], 0);
		close(pipes[0]);
		close(pipes[1]);
			
		dup2(pipes2[1], 1);
		close(pipes2[0]);		
		close(pipes2[1]);
		execvp(*grep_args, grep_args);
	}
	else {
		// replace grep's stdin with read end of 1st pipe
		dup2(pipes2[0], 0);
		close(pipes[0]);
		close(pipes[1]);
		close(pipes2[0]);
		close(pipes2[1]);
		execvp(*wc_args, wc_args);
	}
	return(0);
}
