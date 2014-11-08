#define EI 11   //optimal
#define EJ  4   //optimal
#define N (1 << EI) //buffr 2048
#define F ((1 << EJ) + 1)  //lookahead buffr 17 temp[2*N][2*N+1],l[N * 2]; // size of buffer n for now and n for further use

char temp[2*N][2*N+1],l[N * 2]; // size of buffer n for now and n for further use
FILE *inbwt, *outbwt;
int empty,pos;


int init()
{
char c;
int i;
    for(i=0;i<(N*2)-1;i++)
	{
        if ((c = fgetc(inbwt)) == EOF)
        {
        empty++;//encode till !empty

		break;
        }
        buffr[i] = (int)c;//load buffr
		textcount++;//increase orignal txt countr
    }
    return i;
}


void bubbl(int n)
 {
 int i = 0;
 int j = 0;
char t1[2*N+1];

 for ( i = 1 ; i < n+1 ; i++ )
	{
		for ( j = 0 ; j < n - i ; j++ )
		{
		    if(strcmp(temp[j], temp[j+1]) > 0)
        {
            strcpy(t1,temp[j]);
            strcpy(temp[j],temp[j+1]);
            strcpy(temp[j+1],t1);
        }

	}
	}


}

void encodebwt()
{
    int size,k,i,j,p;
    while(!empty)
    {

    pos=0;
    k=init();//k is size of temp and buffr
    //radixsort(temp,k);
    for(j=0;j<k;j++)
    {
        temp[0][j]=buffr[j];
    }
    temp[0][k]=0;
    for(j=1;j<k;j++)
    {
            for(i=0;i<k;i++)
        {

            temp[j][i]=temp[j-1][(i+1)%(k)];
        }
        temp[j][k]=j;
    }
    bubbl(k);
    }
    for(i=0;i<k;i++)
    {

        buffr[i]=temp[i][k-1];
        if(temp[i][k]==0)
        {
            pos=i;
        }
    }

    if (fputc((pos>>8), outbwt) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
		codecount++;
    if (fputc((pos& 255), outbwt) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
		codecount++;

    for(int i=0;i<k;i++)
    {
        if (fputc(buffr[i], outbwt) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
		codecount++;
    }}



void decodebwt()
{
int x,i,k;
char c;
c = fgetc(inbwt);
x=c;
x<<=8;
c = fgetc(inbwt);
x|=c;
empty=0;
while(!empty)
{

for(i=0;i<2*N;i++)
	{
	if ((c = fgetc(inbwt)) == EOF)
		{
		    empty++;
		    break;
		}
        buffr[i] =c;
        temp[i][0]=c;  //load buffr
		temp[i][1]=i;
	}
k=i;
bubbl(k);
for(i=0;i<k;i++)
{
    temp[i][0]=buffr[x];
    x=(int)temp[x][1];

}
for(i=0;i<k;i++)
if (fputc(temp[(i+1)%k][0],outbwt) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
}
printf("\n\nDECODING DONE");


}

int mainbwt(char p[20],char q[20],int i)
{



bb = 0;
bm = 128;   //bb=to write bm=masking bit currently looking
codecount = 0;
textcount = 0; //count of initial n final data size




	if ((inbwt  = fopen(p, "rb")) == NULL)
	{
		printf("File doesent exist\n");
		exit(1);
	}

	if ((outbwt = fopen(q, "wb")) == NULL)
	{
		printf("Output file can't be made..\n");
		exit(1);
	}
if(i==1)
	{
	encodebwt();

printf("Orignal text:  %ld bytes\n", textcount);
printf("Encoded text:  %ld bytes (%ld %%)\n",codecount, ((codecount * 100) / textcount));
_fcloseall();
return 0;
}

else if(i==0)
{

	decodebwt();
	_fcloseall();
	return 0;
}
else if(i==3)
{

	encodebwt();
	_fcloseall();
	return ((codecount * 100) / textcount);

}
_fcloseall();
}






