#include<stdio.h>
#include<stdlib.h>

int main(int argc, char ** argv)
{
	if (argc < 2) {
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}
	char prevchar,curchar;
	int countcurchar;

	for(int i = 1 ; i < argc; i++)
	{
		FILE * f = fopen(argv[i],"r");
		if(f==NULL)
		{
			printf("wzip: cannot open file\n");
			exit(1);
		}
		if(i==1)
		{
			prevchar = fgetc(f);
			countcurchar = 1;
		}
		while((curchar = fgetc(f)) != EOF)
		{
			if(curchar == prevchar)
			{
				countcurchar++;
			}
			else
			{
				fwrite((int*)&countcurchar,sizeof(int),1,stdout);
				fputc(prevchar,stdout);
				prevchar = curchar;
				countcurchar = 1;
			}
		}
		fclose(f);
	}
	if(countcurchar>0)
	{
		fwrite((int*)&countcurchar,sizeof(int),1,stdout);
		fputc(prevchar,stdout);
	}
	return 0;	
}
