#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LEN 10000


char buf[MAX_LINE_LEN];

void searchInFile(char * searchTerm,FILE * f)
{
	if(f==NULL)
	{
		fprintf(stdout,"wgrep: cannot open file\n");
		exit(1);
	}
	while(fgets(buf,MAX_LINE_LEN,f))
	{
		if(strstr(buf,searchTerm) )
		{
			printf("%s",buf);
		}
	}
}

int main(int argc, char ** argv)
{
	if(argc == 1)
	{
		fprintf(stdout,"wgrep: searchterm [file ...]\n");
		exit(1);
	}
	else if(argc == 2)
	{
		searchInFile(argv[1],stdin);
	}
	
	for(int i = 2; i < argc; i++)
	{
	
		FILE* f = fopen(argv[i],"r");
		searchInFile(argv[1],f);
	}
	return 0;	
}
