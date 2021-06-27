#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
extern int errno;
int main(int argc , char* argv[]){
	// printf("\n %s he %s ho %s ha ",argv[0],argv[1],argv[2]);
	FILE *file;
	char c;
	ssize_t r;
	size_t length=0;
	char *cc = NULL;
	if(argc==2){
		file = fopen(argv[1],"r");
		// if(file==NULL)/////////////////////////
		c = fgetc(file);
		while(c!=EOF){
			printf("%c",c );
			c = fgetc(file);
		}
		fclose(file);
	}
	else if(argc==3){
		if(!strcmp(argv[1],"-b")){     //Command - 1
			FILE* filePointer;
			int bufferLength = 255;
			char buffer[bufferLength];
			filePointer = fopen(argv[2], "r");
			if(filePointer == NULL){
				// printf("Error in file opening\n");
				printf("%s \n",strerror(errno));
				return -1;
			}
			int cnt=0;
			while(fgets(buffer, bufferLength, filePointer)) {
				buffer[strcspn( buffer, "\r\n" )] = '\0';
				if ( buffer[0] == '\0' ){
					printf("\n");
					continue;
				}
				cnt++; 
			    printf("%d  %s\n",cnt,buffer);
			}
			fclose(filePointer);
		}
		if(!strcmp(argv[1],"-n")){   //Command -2
			file = fopen(argv[2],"r");
			if(file == NULL){
				// printf("Error in file opening\n");
				printf("%s \n",strerror(errno));//Error handling
				return -1;
			}
			int cnt =0;
			while((r = getline(&cc, &length,file))!=-1){
				cnt++;
				printf("%d  %s",cnt,cc);
			}
			fclose(file);
		}
	}
	else if(argc>=4){
		printf("Excess arguments");  //Error - 1
	}
	else{
		printf("Invalid Command");  //Error - 2
	}
}