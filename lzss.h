#define EI 11   //optimal
#define EJ  4   //optimal
#define N (1 << EI) //buffr 2048
#define F ((1 << EJ) + 1)  //lookahead buffr 17

int bb = 0, bm = 128;   //bb=to write bm=masking bit currently looking
unsigned long codecount = 0, textcount = 0; //count of initial n final data size
unsigned char buffr[N * 2]; // size of buffer n for now and n for further use
FILE *inlzss, *outlzss;


void chk(FILE *q1) //chk if bit ready to b writtn
{
    if ((bm >>= 1) == 0)
	{
        if (fputc(bb, q1) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
        bb = 0;
		bm = 128;
		codecount++;
    }
}

void endleft(FILE *q2)
{
    if (bm != 128) {
        if (fputc(bb, q2) == EOF)
		{
			printf("Output error\n");
			exit(1);
		}
        codecount++;
    }
}

void output1(int c,FILE *q3)
{
    int mask;

	bb |= bm;//write 1 at bm(mask) position of byte bb
	chk(q3);
    mask = 256; //for ascii values till 128 for 8 bit nos
    while (mask >>= 1) {
        if (c & mask) //chk 1 or 0 at bit pos of mask
		{
		bb |= bm;//write 1 at bm(mask) position of byte bb
		chk(q3);
		}
		else
		chk(q3);
    }
}

void output2(int x, int y) //1 bit for 0,11 for pos in lookahead and 4 for size to be searched
{
    int mask;
    chk(outlzss); //0 to make decode part recognize encoding
    mask = N; //mask=2048 as x can be max n-f= 2031 so it writes 11 bits
    while (mask >>= 1)
	{
        if (x & mask)
		{
		bb |= bm;//write 1 at bm(mask) position of byte bb
		chk(outlzss);
		}
		else
		chk(outlzss);
    }

    mask = (1 << EJ); //y can be max 16 as its lookahead buffer size and thus max match limit so it writes 4 bits
    while (mask >>= 1)
	{
        if (y & mask)
		{
		bb |= bm;//write 1 at bm(mask) position of byte bb
		chk(outlzss);
		}
		else
		chk(outlzss);
    }
}

void encodelzss(void)
{
    int i, j, k, x, y, r, s, buffrend, c;

    for(i=0;i<N-F;i++)
	buffr[i] = ' ';//initialize search buffer

    for(i=N-F;i<N*2;i++)
	{
        if ((c = fgetc(inlzss)) == EOF)
		break;
        buffr[i] = c;  //load buffr
		textcount++;//increase orignal txt countr
    }
    buffrend=i; //at 2N pos
	r = N - F; //start of lookahead buffr
	s = 0; //start of search buffr

	//---------------------initializatn done till here
    while (r < buffrend)
	{
		if(F<=buffrend-r)
		k=F;
		else
		k=buffrend-r;

        x = 0;  //default values
		y = 1;
		c = buffr[r]; //1st byte to search
        for (i = r - 1; i >= s; i--) // linear search in search buffer backwords for longest string
            if (buffr[i] == c)
			{
                for (j = 1; j < k; j++) //search till end of buffer(ie all N bytes)
                    if (buffr[i + j] != buffr[r + j])
					break;
                if (j > y)
				{
                    x = i;
					y = j;
                }
            }
        if (y <= 1)
		output1(c,outlzss);
        else
		output2(x % N, y - 2);

        r += y; //increment by match size
		s += y;
        if(r>=N*2-F) //if r is getting greater than buffer(2N)
		{
            for(i=0;i<N;i++)
			buffr[i] = buffr[i + N];
            buffrend -= N;
			r -= N;
			s -= N;
            while (buffrend < N * 2)
			{
                if ((c = fgetc(inlzss)) == EOF) break;
                buffr[buffrend++]=c;
				textcount++;
            }
        }
    }
    endleft(outlzss);//write left bites at end of all encoding
    }

int getbit(int n,FILE *inlzss) //get n bits
{
    int i, x=0;
    static int wrd, mask = 0;
	/*since it is static we dont need to bother about leftout bits if we dont return whole int at once*/

    for(i=0;i<n;i++)
	{
        if (mask == 0)
		{
            if ((wrd = fgetc(inlzss)) == EOF)
			return EOF;
            mask = 128;
        }
        x <<= 1;
        if (wrd & mask)
		x++;
        mask >>= 1;
    }
    return x;
}

void decodelzss(void)
{
    int i,j,k,r,c;

    for(i=0;i<N-F;i++)
	buffr[i] = ' '; //initialize

    r=N-F;

    while ((c=getbit(1,inlzss))!= EOF)
	{
        if (c) //char written
		{
            if ((c=getbit(8,inlzss))==EOF)
			break;
            fputc(c, outlzss);
            buffr[r++] = c;
			r %=N;
        }
		else
		{
            if ((i=getbit(EI,inlzss))==EOF)
			break;
            if ((j=getbit(EJ,inlzss))==EOF)
			break;
            for (k=0;k<=j+1;k++)
			{
                c=buffr[(i + k)%N];
                fputc(c, outlzss);
                buffr[r++] = c;
				r %=N;
            }
        }
    }
}


int mainlzss(char p[20],char q[20],int i)
{

bb = 0;
bm = 128;   //bb=to write bm=masking bit currently looking
codecount = 0;
textcount = 0; //count of initial n final data size



	if ((inlzss  = fopen(p, "rb")) == NULL)
	{
		printf("File doesent exist\n");
		exit(1);
	}

	if ((outlzss = fopen(q, "wb")) == NULL)
	{
		printf("Output file can't be made..\n");
		exit(1);
	}
if(i==1)
	{
	encodelzss();
	printf("Orignal text:  %ld bytes\n", textcount);
    printf("Encoded text:  %ld bytes (%ld %%)\n",codecount, ((codecount * 100) / textcount));
	_fcloseall();
	return 0;
}

else if(i==0)
{
	decodelzss();
	_fcloseall();
	return 0;
}
else if(i==3)
{

	encodelzss();
	_fcloseall();
	return ((codecount * 100) / textcount);

}


}

