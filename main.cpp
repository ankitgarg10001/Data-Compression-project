#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#include<cstdlib>
#include "lzss.h"
#include "bwt.h"
#include "rle.h"
#include "fmfe.h"




int main()
{

char choice;
int i,a;
char p[20],q[20];
while(1)
{
    system("cls");
    fflush(stdin);
printf("Enter ur choice: \n1. Use lzss\n2. Use Burrows Wheeler Transform\n3. Use Run Length Encoding\n4. Use Move to front Encoding\n5. See Ratios Off all\n6. deflate\n \n7. Exit ");
scanf("%c",&choice);
fflush(stdin);
switch( choice)
{
case '1':

			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);
			printf("enter your choice(1->encode,0->decode):  ");
			scanf("%d",&i);
			mainlzss(p,q,i);
            _getch();
			break;
case '2':

			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);
			printf("enter your choice(1->encode,0->decode):  ");
			scanf("%d",&i);
			mainbwt(p,q,i);
            _getch();

			break;
case '3':

			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);
			printf("enter your choice(1->encode,0->decode):  ");
			scanf("%d",&i);
			mainrle(p,q,i);
            _getch();
			break;
case '4':

			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);
			printf("enter your choice(1->encode,0->decode):  ");
			scanf("%d",&i);
			mainmtf(p,q,i);
            _getch();
			break;


case '5':
			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);

			a=mainlzss(p,q,3);
			printf("\nLZSS(%d%%): ",a);
			for(i=1;i<a/2;i++)
			printf("|");
			a=mainbwt(p,q,3);
			printf("\nBWT (%d%%): ",a);
			for(i=1;i<a/2;i++)
			printf("|");
			a=mainrle(p,q,3);
			printf("\nRLE (%d%%): ",a);
			for(i=1;i<a/2;i++)
			printf("|");
			a=mainmtf(p,q,3);
			printf("\nMTF (%d%%): ",a);
			for(i=1;i<a/2;i++)
			printf("|");


			_getch();

			break;

case '6':

			printf("enter file name to be compressed /decompressed:  ");
			gets(p);

			fflush(stdin);
			printf("enter compressed/decompressed file name:  ");
			gets(q);
			printf("enter your choice(1->encode,0->decode):  ");
			scanf("%d",&i);
			if(i==1)
			{
			    mainbwt(p,"z",i);
                mainrle("z",q,i);
			}
			if(i==0)
			{
			    mainrle(p,"z",i);
			    mainbwt("z",q,i);
			}


            _getch();

			break;

case '7':
			return 0;


}
}
}
