#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define MAX_BUF 512

enum bool {false,true};

/* 
sort the passed lines using bubblesort algorithm.
Accepts numeric or not numeric values.
*/
void bubbleSort(char **v,int dim,enum bool numeric){
	int i=0;
	enum bool order=false;
	while(dim>1 && !order)
	{
		order=true;
		for(i=0;i<dim-1;i++)
			if((!numeric && strcmp(v[i],v[i+1])>0) || (numeric && atoi(v[i])>atoi(v[i+1])))
			{
				char tmp[255];
				strcpy(tmp,v[i]); 
				v[i]=malloc(sizeof(char)*(strlen(v[i+1])));

				strcpy(v[i],v[i+1]);
				v[i+1]=malloc(sizeof(char)*strlen(tmp));
				strcpy(v[i+1],tmp);

				order=false;
			}
		dim--;
	}
}

//Removes the duplicate from the file and returns the new dimension (in line) of the text
int unique(char **v,int dim)
{
	dim--;
	for(int i=0;i<dim;i++)
	{
		for(int j=i+1;j<dim;)
		{
			if(strcmp(v[j],v[i])==0)
			{
				for(int k=j;k<dim;k++)
				{
					v[k]=malloc(sizeof(char)*strlen(v[k+1]));
					strcpy(v[k],v[k+1]);
				}
				dim--;
			}
			else
				j++;
		}
	}
	return dim++;
}


//Reverse the lines of the text
 void reverse(char **v,int dim)
 {

	/* Function to reverse arr[] from start to end*/
	int start=0;
	dim--;
	int end=dim; 
	char temp[MAX_BUF];
	while (start < end) 
	{       
		strcpy(temp,v[start]); 
		v[start] = malloc(sizeof(char) * strlen(v[end])); 
		strcpy(v[start],v[end]); 
		v[end] = malloc(sizeof(char) * strlen(temp)); 
		strcpy( v[end],temp); 
		start++; 
		end--; 
	}  
}

int main(int argc, char *argv[])
{
	int input=0;
	int first_file=0;
	int fd=0;
	int dim=0;

	enum bool numeric=true;
	enum bool c=false, u=false, o=false,r=false,n=false;
	
	char dest[MAX_BUF];
	char tmp[255];
	char *text[255];

	//input no option first
	if(argc<=1)
	{
		while((read(0, tmp, sizeof(tmp)) > 0))
		{
			text[dim]=malloc(sizeof(char)*strlen(tmp));
			strcpy(text[dim],tmp);
			dim++;
		}
		
		numeric=false;
		bubbleSort(text,dim,numeric);
		for(int i=0;i<dim;i++)
		{
			printf(1,"%s",text[i],strlen(text[i]));}
			free(text);
			exit();
		}

		for(int i=1;i<argc;i++)
		{
			fd=0;

			if(argv[i][0]=='-')
			{
			if(argv[i][1]=='c')
			{
				c=true;
			}
			else if(argv[i][1]=='u')
			{
				u=true;
			}
			else if(argv[i][1]=='o')
			{
				o=true;
			}
			else if(argv[i][1]=='r')
			{
				r=true;
			}
			else if(argv[i][1]=='n')
			{
				n=true;
			}
			else
			{
				printf(2, "sort: invalid option %s", argv[i]);
				exit();
			}

			// input case
			if(i==argc-1 || (o==true && i+1==argc-1 && argv[i+1][0]!='-'))
			{
				input=1;
				fd=0;
			}
		}
			else
			{
			//identify destination filename
			if(o==true && first_file==0)
			{
				strcpy(dest,argv[i]);
				first_file=1;
			}
			else
			{
				//create buffer
				fd=open(argv[i],0);
				if(fd<0)
				{
					printf(2,"sort: No such file or directory");
					close(fd);
					exit();
				}

				int readed = read(fd, tmp, sizeof(tmp));
				close(fd);
				int n1=0;
				char row[255];

				for(int i=0;i<readed;i++)
				{
					if(tmp[i]!='\n')
					{
						row[n1]=tmp[i];
						n1++;
					}
					else
					{   
						row[n1]=0;
						text[dim]=malloc(sizeof(char)*n1);
						strcpy(text[dim],row);
						dim++;
						n1=0;
					}
				}
			}
		}
	}

	if(input==1)
	{
		while((read(0, tmp, sizeof(tmp)) > 0))
		{
			text[dim]=malloc(sizeof(char)*strlen(tmp));
			strcpy(text[dim],tmp);
			dim++;
		}
	}
	close(fd);

	if(c==true)
	{
		for(int i=0;i<dim-1;i++)
		{
			if(strcmp(text[i],text[i+1])<0)
			{
				printf(1,"Sort: out of order %s\n",text[i]);
				free(text);
				exit();
			}
			free(text);		
		}
		exit();
	}
	
	if(u==true)
	{
		dim=unique(text,dim);
	}

	if(n==true)
	{
		numeric=true;
		bubbleSort(text,dim,numeric);
	}
	else
	{
		numeric=false;
		bubbleSort(text,dim,numeric);
	}

	if(r==true)
	{
		reverse(text,dim);
	}

	if(o==true)
	{
		unlink(dest);
		int outfile=open(dest, O_RDWR | O_CREATE);
		for(int i=0;i<dim;i++)
		{
			write(outfile,text[i],strlen(text[i]));
			write(outfile,"\n",1);}
			free(text);
			exit();
		}
	if(input==0)
	{
		for(int i=0;i<dim;i++)
		printf(1,"%s\n",text[i]);
	}
	else 
	{
		for(int i=0;i<dim;i++)
		{
			printf(1,"%s",text[i]);
		}
	}
	close(fd);
	free(text);
	exit();
}
