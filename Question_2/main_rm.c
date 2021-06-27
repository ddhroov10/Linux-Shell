#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
extern int errno;
int main(int argc, char *argv[]){
	if(argc==2){
		int c=unlink(argv[1]);
		printf("%d\n", c);
		if(c==-1)printf("%s",strerror(errno));
	}
	if(argc==3){
		int c;
		if(strcmp(argv[1],"-v")==0){
			c=unlink(argv[2]);
			if(c==-1)printf("%s %s",argv[2],strerror(errno));

		}
		else if(strcmp(argv[1],"-d")==0){
			c=remove(argv[2]);
			// printf("sdjkf");
			if(c==-1)printf("%s",strerror(errno));
		}
	}
}