#include<stdio.h>
#include<conio.h>
#include<string.h>
FILE *f5;
char encfmfe()
{

int i,j,k,l,m,n,temp,done=0;
char b[100];
char a[100];
char c[100];
char str[5000];

while(!done)
{
i=0;
while(i<5000)
	{
		if((str[i]=fgetc(f1))==EOF)
		{
			done++;
			break;
		}
		textcount++;
		i++;
	}
	str[i]='\0';

	l = i;

i=0;
	f5 = fopen( "string.txt", "r" );

	while(!feof(f5))
	{
		fscanf(f5,"%c",&a[i]);

		i++;
	}
a[i]='\0';

m=strlen(a);
strcpy(c,a);
for(i=0;i<l;i++)
{
  for(j=0;j<m;j++)
   {
     if(str[i]==a[j])
      {	temp=a[j];
	b[i]=c[j];
	codecount++;
	for(k=j;k>0;k--)
	{
	a[k]=a[k-1];
	}
	a[0]=temp;
      }
   }
}
fprintf(f2,"%s",b);
}


}

void decfmfe()
{

int i,j,k,l,m,n,temp,done=0;
char b[100];
char a[100];
char c[100];
char str[5000];
while(!done)
{
i=0;

while(i<5000)
	{
		if((str[i]=fgetc(f1))==EOF)
		{
			done++;
			break;
		}
		textcount++;
		i++;
	}
	str[i]='\0';


l = strlen(str);
i=0;
	f5 = fopen( "string.txt", "r" );

	while(!feof(f5))
	{
		fscanf(f5,"%c",&a[i]);

		i++;
	}
	a[i]='\0';

//printf("\n Enter the string: ");
//scanf("%s",a);
m=strlen(a);
strcpy(c,a);
for(i=0;i<l;i++)
{
  for(j=0;j<m;j++)
   {
     if(str[i]==c[j])
      {	temp=a[j];
	b[i]=a[j];
	for(k=j;k>0;k--)
	{
	a[k]=a[k-1];
	}
	a[0]=temp;
      }
   }
}
fprintf(f2,"%s",b);
}

}


int mainmtf(char p[20],char q[20],int i)
{
codecount = 0;
textcount = 0; //count of initial n final data size



	if ((f1  = fopen(p, "rb")) == NULL)
	{
		printf("File doesent exist\n");
		exit(1);
	}

	if ((f2 = fopen(q, "wb")) == NULL)
	{
		printf("Output file can't be made..\n");
		exit(1);
	}
if(i==1)
	{
	encfmfe();
	printf("Orignal text:  %ld bytes\n", textcount);
    printf("Encoded text:  %ld bytes (%ld %%)\n",codecount, ((codecount * 100) / textcount));
	_fcloseall();
	return 0;
}

else if(i==0)
{
	decfmfe();
	_fcloseall();
	return 0;
}
else if(i==3)
{

	encfmfe();
	_fcloseall();
	return ((codecount * 100) / textcount);

}

}
