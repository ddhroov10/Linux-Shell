#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
extern int errno;
int main(int argc, char *argv[100]){
	// printf("\n %s he %s ho %s ha ",argv[0],argv[1],argv[2]);
	if(argc==1){
		printf("Less arguments");
	}
	else if(argc==2){
	 		if(strcmp(argv[1],"--version")==0){   //Command - 1
	 		printf("\n mkdir (GNU coreutils) 8.2 \n Copyright (C) 2017 Free Software Foundation, Inc. \n License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n This is free software: you are free to change and redistribute it.\n There is NO WARRANTY, to the extent permitted by law.");
	 		}
	 		else{
	 			mkdir(argv[1],0700);
	 			printf("%s",strerror(errno));  //Error - 1
	 		}
	 }
	 else if(argc==3){
	 	if(strcmp(argv[1],"-v")==0){   //Command - 2
	 			int check=mkdir(argv[2],0777);  //system call
	 			printf("%s",strerror(errno));
	 	}
	 	else{
	 		printf("Invalid command");	//Error -2
	 	}
	 }
	 else{
	 	printf("Excess number of arguments");
	 }
}