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

int main(int argc, char **argv){
 if(argc < 3 || argc > 6){
  printf("error");
  exit(1);
 }
 
 int numArgs = argc-1;
 char* args[5];
 char* arg1;
 char* arg2;
 char* arg3;
 char* arg4;
 char* arg5;

 for(int i = 0; i < numArgs; ++i){
  args[i] = str
 }
if(numArgs == 2){
 arg1 = strtok(argv[1], ' ');
 arg2 = strtok(argv[2], ' ');
}
 
 return(0);
}
