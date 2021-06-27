#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#define str_size 100
#include <errno.h>
extern int errno;
int main(int argc , char* argv[]){
	// printf("chal rha hai");
	// printf("theek %d",argc);
	// printf("\n %s he %s ho %s ha ",argv[0],argv[1],argv[2]);
	DIR*p;
	struct dirent *d;
	char cwd[str_size];
	getcwd(cwd,sizeof(cwd));

	p=opendir(cwd);
	if(argc==1){
		while(d=readdir(p)){
			if(d->d_name[0] == '.' && d->d_name[1]=='.') {
				printf("%s \n",d->d_name);
			}
			else if(d->d_name[0] == '.' && d->d_name[1]!='\0') {
        		continue;
    		}
    		else {
    			printf("%s \n",d->d_name);
    		}
			
		}
	}
	else if(argc==2){
		if(strcmp(argv[1],"-a")==0){   //Command -1
			while(d=readdir(p)){
				printf("%s \n",d->d_name);
			}
		}
		else if(strcmp(argv[1],"-A")==0){  //Command - 2
			while(d=readdir(p)){
				if(d->d_name[0] == '.' && d->d_name[1]=='\0'){
					continue;
				}
				else if(d->d_name[0] == '.' && d->d_name[1]=='.') {
					continue;
				}
				else{
					printf("%s \n",d->d_name);
				}
			}
		}
		else{
			printf("Invalid argument");
		} 
	}
	else if(argc>=3){
		printf("Excess number of arguments");
	}
	return 0;
}