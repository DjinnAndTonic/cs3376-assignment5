// file: DynPipe.cpp
// author: Chanh-Brian Nguyen
// date: 04/07/2017
// purpose: CS3376
// description:
// this program accepts 2-5 arguments that are all unix/linux commands and dynamically uses child processes to exexecute the given commands.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//function that uses read() and write() functions to pass information from process to process via pipes
void runProg(int source, int dest){
 ssize_t bytesR, bytesW;
 char buffer[BUFSIZ];

 while((bytesR = read(source, buffer, BUFSIZ)) > 0){
  bytesW = 0;
  while(bytesW < bytesR)
   bytesW += write(dest, buffer + bytesW, bytesR - bytesW);
 } 
}

int main(int argc, char **argv){
 if(argc < 3 || argc > 6){
  printf("error\n");
  exit(1);
 }
 
 //create pipes for the stdin and stdout for use in the n-child processes
 int pipeIn[2];
 pipe(pipeIn);

 int pipeOut[2];
 pipe(pipeOut);
 
 //creation of child processes
 if(fork() == 0){
  //close write end for pipeIn and read end for pipeOut
  close(pipeIn[1]);
  close(pipeOut[0]);
  
  dup2(pipeIn[0], 0);
  dup2(pipeOut[1], 1);

  if((execvp(argv[1], argv+1)) == -1){
   perror("Invalid command");
   exit(1);
  }
  else{
   execvp(argv[1], argv+1);
  }
 }
 
 //close read end for pipeIn and write end for pipeOut
 close(pipeIn[0]);
 close(pipeOut[1]);

 runProg(0, pipeIn[1]);
 close(pipeIn[1]);
 
 runProg(pipeOut[0], 1);
 close(pipeOut[0]);
  
 sleep(1);
 /*for(int i = 1; i < argc; ++i){
  printf("%s\t", argv[i]);
 }
 printf("\n%d arguments\n", argc-1);*/
 printf("\nhello world");
 return(0);
}
