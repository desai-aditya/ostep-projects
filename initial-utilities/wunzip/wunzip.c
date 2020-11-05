#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

int main(int argc, char ** argv)
{

	if(argc<=1)
	{
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	for(int fileidx = 1; fileidx < argc; fileidx++)
	{
		FILE * f = fopen(argv[1],"r");
		if(f == NULL)
		{
			printf("wunzip: cannot open file\n");
			exit(1);
		}
		int countchar=0;
		char c=0;

		while(1)
		{
			if(feof(f))break;
			countchar=0;
			fread(&countchar,sizeof(int),1,f);	
			//printf("%d\n",countchar);
			//countchar=ntohl(countchar);
			//printf("%d\n",countchar);
			fread(&c,sizeof(char),1,f);
			for(int i = 0 ; i < countchar; i++)
			{
				fputc(c,stdout);
			}
		}
		fclose(f);
	}
	return 0;	
}
