
void decode()
{
    char c;
    int i,k;
    while ((c=getbit(1,f1))!= EOF)
	{
        if (c) //char written
		{
            if ((c=getbit(8,f1))==EOF)
			break;
            fputc(c, f2);
        }
		else
		{
            if ((i=getbit(16,f1))==EOF)
			break;
            if ((c=getbit(8,f1))==EOF)
			break;
            for (k=0;k<i;k++)
			{
                fputc(c, f2);
            }
        }
    }
}












int main()
{
int i,j,m,k,l,end;
char st[50],c;
char b[50];
char p[20],q[20];
	i=0;

//decoding
printf("enter file name to be de-compressed:  ");
	gets(p);

fflush(stdin);
	printf("enter destination file name:  ");
	gets(q);

fflush(stdin);
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
	/*
here:
	while(i<sizeof(st))
	{
	    if ((c = fgetc(f1)) == EOF)
	    {
        end++;
		break;
	    }
        st[i] = c;
		i++;
	}
st[i]='\0';
l = strlen(st);
k=0;
for(i=0;i<l;i=i*1)
{
if(st[i]=='$')
{
m=st[i+1]-48;
printf("%d\n",m);
for(j=0;j<m;j++)
{
b[k+j]=st[i+2];
}
k=k+m;
i=i+3;
}
else
{

b[k]=st[i];
k++;
i++;
}
}
b[i]='\0';
printf("\n\n\tEncoded String is: ");
printf("%s",b);
fprintf(f2,"%s",b);
*/
decode();

_getch();
_fcloseall();
}
