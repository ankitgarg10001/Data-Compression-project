#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<fcntl.h>
#include <stdlib.h>


char str[5000],c;
int len,j,end=0,temp1;
FILE *f1,*f2;


void outcode(int x, char y) //1 bit for 0,11 for pos in lookahead and 4 for size to be searched
{
    int mask;
    chk(f2); //0 to make decode part recognize encoding
    mask = 65536;
    while (mask >>= 1)
	{
        if (x & mask)
		{
		bb |= bm;//write 1 at bm(mask) position of byte bb
		chk(f2);
		}
		else
		chk(f2);
    }

    mask = 256; //y can be max 16 as its lookahead buffer size and thus max match limit so it writes 4 bits
    while (mask >>= 1)
	{
        if (y & mask)
		{
		bb |= bm;//write 1 at bm(mask) position of byte bb
		chk(f2);
		}
		else
		chk(f2);
    }
}

void encoderle()
{

char end=0;
int i;
while(!end)
{
    i=0;

	while(i<sizeof(str))
	{
	    if ((c = fgetc(f1)) == EOF)
	    {
	        end++;
		break;
	    }
        str[i] = c;
        textcount++;
		i++;
	}
	str[i]='\0';
len =i;


for(i=0;i< len;i=i++)
{
c=str[i];
j = 1;
while(str[i+j]==c)
{
    j++;
}
if(j<4)
{
    for(temp1=0;temp1<j;temp1++)
    {
        output1(c,f2);

    }
    i=i+temp1-1;
    continue;

}
else
{
    outcode(j,c);
    i=i+j-1;
    continue;
}

}
}
endleft(f2);

}

void decoderle()
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








int mainrle(char p[20],char q[20],int i)
{


bb = 0;
bm = 128;   //bb=to write bm=masking bit currently looking
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
	encoderle();
	printf("Orignal text:  %ld bytes\n", textcount);
    printf("Encoded text:  %ld bytes (%ld %%)\n",codecount, ((codecount * 100) / textcount));
	_fcloseall();
	return 0;
}

else if(i==0)
{
	decoderle();
	_fcloseall();
	return 0;
}

else if(i==3)
{

	encoderle();
	_fcloseall();
	return ((codecount * 100) / textcount);

}

}
