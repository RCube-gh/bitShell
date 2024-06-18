#include<stdio.h>
#include<stdlib.h>
#include<regex.h>
#include<string.h>



int b2d(char *n);
void printBin(char *s);

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
		char input_str[1024];
		// scanf("%[^\n]%*s",input_str);
		scanf("%s",input_str);
		// fgets(input_str, sizeof(input_str), stdin);
		len=(int)strlen(input_str);
		reti = regexec(&re, input_str, 0, NULL, 0);
		if(len%8!=0||reti){
			printf("ERROR: INVALID COMMAND\n");
			printf("print binary\n");
			printBin(input_str);
			continue;
		}

		char command_string[256];
		for(int i=0;i<(len/8);i++){
			dec = b2d(&input_str[i*8]);
			command_string[i]=(char)dec;
		}
		printf("%s\n",command_string);
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
