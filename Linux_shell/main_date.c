#include <stdio.h>
#include <time.h>
#include <string.h>
#define UTC (-5)
#include <errno.h>
extern int errno;
int main(int argc, char *argv[]){
	// printf("\n %s he %s ho %s ha ",argv[0],argv[1],argv[2]);
	time_t local_time;
	struct  tm *ptr;
	char arr[1000];
	local_time = time(NULL);
	if(argv[1]==NULL){
		local_time = time(NULL);
		printf("%s",ctime(&local_time));
	}
	else if(strcmp(argv[1],"-u")==0 && argv[2]==NULL){  //Command -1
		ptr = gmtime(&local_time);
		strftime(arr, 1000, "%c", ptr);
		printf("%s\n",arr );
	}
	else if(strcmp(argv[1],"-R")==0 && argv[2]==NULL){  //Command -2
		ptr = localtime(&local_time);
		strftime(arr, 1000, "%a %d %h %Y %T %z", ptr);
		printf("%s\n",arr );
	}
	else if(argc>=3){
		printf("Excess no. of arguments supplied");  //Error 1
	}
	else{
		printf("Invalid command");  //Error 2
	}
}