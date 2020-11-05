#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFSIZE 10

char * readLines(FILE * filestream)
{
	if(feof(filestream))return NULL;
	char * buf = NULL;
	int size = BUFSIZE;
	int last = 0;

	do
	{
		size+= BUFSIZE;
		buf = realloc(buf,size);

		if(buf == NULL)
		{
			fprintf(stderr,"malloc failed");
			exit(1);
		}
		fgets(buf+last,BUFSIZE,filestream);
		last = strlen(buf);

	}while( !feof(filestream) && buf[last-1]!='\n');

	return buf;
}

typedef struct LLNode{
	char * filestr;
	struct LLNode * next;
}LLNode;



LLNode *  addToLLFromEnd(char * filestr, LLNode * nextNode)
{
	LLNode * newnode = (LLNode * ) malloc(sizeof(LLNode));
	newnode->filestr = filestr;
	newnode->next=nextNode;
	return newnode;
}

void printReverseList(LLNode * node, FILE * fout)
{
	while(node!=NULL)
	{
		fprintf(fout,"%s",node->filestr);
		node=node->next;
	}
}
int main(int argc, char ** argv)
{

	if(argc>=4)
	{
		fprintf(stderr,"usage: reverse <input> <output>\n");
		exit(1);
	}
	FILE * fin = fopen(argv[1],"r");
	if(argc <= 1)
	{
		fin=stdin;
	}
	if(fin == NULL)
	{
		fprintf(stderr,"reverse: cannot open file '%s'\n",argv[1]);
		exit(1);
	}
	char * filestr = readLines(fin);
	LLNode * nextNode = NULL;
	while(filestr!=NULL)
	{
		nextNode = addToLLFromEnd(filestr,nextNode);
		//printf("%s",filestr);
		filestr = readLines(fin);
	}
	fclose(fin);

	FILE * fout;
	if(argc==3)
	{
		if(strcmp(argv[1],argv[2])==0)
		{
			fprintf(stderr,"reverse: input and output file must differ\n");
			exit(1);
		}
		struct stat st1,st2;
		stat(argv[1],&st1);
		stat(argv[2],&st2);
		if(st1.st_ino == st2.st_ino)
		{
			fprintf(stderr,"reverse: input and output file must differ\n");
			exit(1);
		}
		fout = fopen(argv[2],"w+");
	}
	else
	{
		fout = stdout;
	}
	
	printReverseList(nextNode,fout);
	fclose(fout);
	return 0;
}
