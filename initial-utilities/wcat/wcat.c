#include<stdio.h>
#include<stdlib.h>

#define MAX_LINE_LEN 10000
char buf[MAX_LINE_LEN];
void printfile(char * filename)
{
	FILE* f = fopen(filename,"r");
	if(f==NULL)
	{
		fprintf(stdout,"wcat: cannot open file\n");
		exit(1);
	}
	while(fgets(buf,MAX_LINE_LEN,f))
	{
		printf("%s",buf);
	}
}

int main(int argc, char ** argv)
{
	for(int i = 1; i < argc; i++)
	{
		printfile(argv[i]);
	}
	return 0;	
}
