#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <dirent.h>	
#include <errno.h>
extern int errno;// perror
// #include <sys/types.h>
#include <sys/wait.h>
#define true 1
#define false 0
#define str_size 100 //100 is assumed to be max number of commands given
#define get_sec_token int cnt=0;while(token!=NULL){cnt++;token=strtok(NULL," ");if(cnt==1){break;}}
#define get_sec_flag int cnt=0;while(flag!=NULL){cnt++;flag=strtok(NULL," ");if(cnt==1){break;}}
#define get_rest int cnt2=0;while(rest!=NULL){cnt2++;rest=strtok(NULL," ");if(cnt2==1){break;}}
#define print_all_tokens while(token!=NULL){printf("%s ",token);token=strtok(NULL," ");}
#define HISTORY_MAX_SIZE 100
#define make_other_tokens 	char* flag;strcpy(flag,token);get_sec_flag char* rest;strcpy(rest,token);get_rest

static const char *history[HISTORY_MAX_SIZE];
unsigned history_count = 0;
int echo_check=0;


void print_dir(){
	char buff[1024];
	getcwd(buff,sizeof(buff));
	if(echo_check==0){
		printf("\nDir: %s",buff);
	}
	else{
		printf("Dir: %s",buff);
		echo_check=0;
	}
}
void add_command_to_history(const char *command){
   if(history_count<HISTORY_MAX_SIZE) {
   		history[history_count++]=strdup(command);
   }
}

int checkToken(char *token){
	//internal commands
	if(strcmp(token,"cd")==0){
		return 1;	
	}
	else if(strcmp(token,"echo")==0){
		return 2;
	}
	else if(strcmp(token,"history")==0){
		return 3;
	}
	else if(strcmp(token,"pwd")==0){
		return 4;
	}

	//external commands	
	else if(strcmp(token,"ls")==0){
		return 6;
	}
	else if(strcmp(token,"cat")==0){
		return 7;
	}
	else if(strcmp(token,"date")==0){
		return 8;
	}
	else if(strcmp(token,"rm")==0){
		return 9;
	}
	else if(strcmp(token,"mkdir")==0){
		return 10;
	}	

	//invalid command for my shell
	else{
		return 11;
	}	
}
void func_cd(char *token){
	get_sec_token  //macro
	char path[str_size];//path is directory
	strcpy(path,token);
    char cwd[str_size];
    if(token[0] != '/'){
        getcwd(cwd,sizeof(cwd));
        strcat(cwd,"/");
        strcat(cwd,path);
        chdir(cwd);
        if(chdir(cwd) == -1){
			fprintf(stderr, "vsh: Error changing directory\n");
			perror("Error");
		}
    }
    else{
        chdir(token);
        if(chdir(token) == -1){
			fprintf(stderr, "vsh: Error changing directory\n");
		}
    }
}
void func_echo(char* token){
	get_sec_token
	// make_other_tokens
	if(strcmp(token,"-n")==0){
		token=strtok(NULL," ");
		print_all_tokens; //macro
		echo_check=1;
	}
	else if(token[0]=='*'){
		DIR*p;
		struct dirent *d;
		char cwd[str_size];
		getcwd(cwd,sizeof(cwd));
		printf("%s \n",strerror(errno));//Error handling
		p=opendir(cwd);
		while(d=readdir(p)){
			printf("%s ",d->d_name);
		}
	}
	else{
		print_all_tokens  //macro
	}
}
int check1=0;
void func_history(char* token){
	make_other_tokens
	if(flag==NULL && rest==NULL){
		for(int i=0;i<history_count;i++){
			printf("%s \n",history[i]);
		}
	}
	else{
		if(strcmp(flag,"-d")==0){
			if(check1==1){
				printf("Line does not exist");
				return;
			}
			if(rest==NULL){
				printf("history: -d: option requires an argument");
			}
			else{
				for(int i=0;i<history_count;i++){
					if(i==atoi(rest)-1)continue;
					printf("%s \n",history[i]);
				}
			}
		}
		else if(strcmp(flag,"-c")==0){
			printf("History Cleared");
			check1=1;
		}
		else{
			printf("Invalid command");
		}
	}
}

void func_pwd(char* token,char* environ){
	print_dir();
	// printf("\n %s \n",strerror(errno));
}
void func_ls(char* token){
	make_other_tokens
	int pid=fork();
	if(pid<0){
		printf("error");
	}
	else if(pid==0){
		execl("/home/ddhroov10/Desktop/OS/Question_2/ls_exe",token,flag,rest,NULL);
	}
	else{
		wait(NULL);
	}
}
void func_cat(char* token){
	make_other_tokens
	int pid=fork();
	if(pid<0){
		printf("error");
	}
	else if(pid==0){
		execl("/home/ddhroov10/Desktop/OS/Question_2/cat_exe",token,flag,rest,NULL);
	}
	else{
		wait(NULL);
	}
}
void func_date(char* token){
	make_other_tokens
	int pid=fork();
	if(pid<0){
		printf("error");
	}
	else if(pid==0){
		execl("/home/ddhroov10/Desktop/OS/Question_2/date_exe",token,flag,rest,NULL);
	}
	else{
		wait(NULL);
	}
}
void func_rm(char* token){
	make_other_tokens
	int pid=fork();
	if(pid<0){
		printf("error");
	}
	else if(pid==0){
		execl("/home/ddhroov10/Desktop/OS/Question_2/rm_exe",token,flag,rest,NULL);
	}
	else{
		wait(NULL);
	}
}
void func_mk_dir(char* token){
	make_other_tokens
	int pid=fork();
	if(pid<0){
		printf("error");
	}
	else if(pid==0){
		execl("/home/ddhroov10/Desktop/OS/Question_2/mkdir_exe",token,flag,rest,NULL);
	}
	else{
		wait(NULL);
	}
}
int main(int argc,char **argv){
	char environ_arr[1000];
	getcwd(environ_arr,1000);
	int childPid;
	char *cmdLine;
	int cntr=0;
	char** stringList = malloc(str_size* sizeof(char*));
	for(int i=0;i<str_size;i++) {
 		stringList[i] = (char*)malloc(str_size+1);
	}

	while(true){
		print_dir();
		cmdLine=readline("\n >>>");
		if(strlen(cmdLine)==0)continue;
		stringList[cntr++]=cmdLine;
		add_command_to_history(cmdLine);
		char *token=strtok(stringList[cntr-1]," ");
		if(strcmp(token,"exit")==0){
			break;
		}
		//internal commands
		if(checkToken(token)<=5){  
			switch(checkToken(token)){
				case(1):
					func_cd(token);
					break;
				case(2):
					func_echo(token);
					break;
				case(3):
					func_history(token);
					break;
				case(4):
					func_pwd(token,environ_arr);
					break;
			}
		}
		//external commands
		else if(checkToken(token)<=10){
				switch(checkToken(token)){
					case(6):
						func_ls(token);
						break;
					case(7):
						func_cat(token);
						break;
					case(8):
						func_date(token);
						break;
					case(9):
						func_rm(token);
						break;
					case(10):
						func_mk_dir(token);
						break;
				}
		}
		else{
			printf("Command does not exist");
		}
		free(cmdLine);
	}
}