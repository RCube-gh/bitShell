#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


int b2d(char *n);
void printBin(char *s);
void execute(char *cs);

int main(void){

	const char regex[] = "([01])";
	int len;
	regex_t re;
	regmatch_t m;
	int reti;
	int dec;

	reti = regcomp(&re, "^[01]+$", REG_EXTENDED);
	if(reti){
		fprintf(stderr, "failed to compile regex\n");
		return 1;
	}

	for(;;){
		printf("> ");
		char input_str[1024]="";
		for(int i=0;i<1024;i++){
			input_str[i]='\0';
		}
		// scanf("%s",input_str);
		// fgets(input_str, sizeof(input_str), stdin);
		if(fgets(input_str, sizeof(input_str),stdin) != NULL){
		len=(int)strlen(input_str);
			if(len>0&&input_str[len-1]=='\n'){
				input_str[len-1]='\0';
			}
		}
		len--;
		reti = regexec(&re, input_str, 0, NULL, 0);
		if(len%8!=0||reti){
			printf("ERROR: INVALID COMMAND\n");
			printf("print binary\n");
			printBin(input_str);
			continue;
		}
		char command_string[256]="";
		for(int i=0;i<(len/8);i++){
			dec = b2d(&input_str[i*8]);
			command_string[i]=(char)dec;
		}
		printf("%s\n",command_string);
		execute(command_string);
	}
	return 0;
}


int b2d(char *n){
	int d = 0;
	int base = 1;
	for(int i=7;i>=0;i--){
		if((char)n[i]=='1')d+=base;
		base*=2;
	}
	return d;
}

void printBin(char *s){
	int l=strlen(s);
	for(int i=0;i<l;i++){
		printf("  %c: ",s[i]);
		for(int j=7;j>=0;j--){
			if(s[i] & (1 << j)){
				printf("1");
			}else{
				printf("0");
			}
			
		}
		printf("\n");
	}

}

void execute(char *cs){
		char *token = strtok(cs, " ");
		int nargs=0;
		char *args[30];
		args[nargs++]=token;
		while(token!=NULL){
			token=strtok(NULL, " ");
			if(token!=NULL)args[nargs++]=token;
		}
		args[nargs]='\0';
		execv(args[0],args);
}
