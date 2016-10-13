#include<stdio.h>

FILE *filePtr;
char line[50];
int numNonTer;
int numOfProd;
int numOfTer;
int parseTable[20][20];

struct leftInfo
{
        char leftSymbol;
        int numOfProd;
        int startingIndex;
}l[20];

struct rightInfo
{
         char rightSymbols[20];
}r[20];


void rightLeftInfo()
{
        int i,j,k=0;
   filePtr=fopen("prod.txt","r");

   printf("\nRight Info table\n");
   for(i=0;fscanf(filePtr,"%s",line)==1;i++)
   {
        if(i==0) {
                l[k].leftSymbol=line[0];
                l[k].numOfProd=1;
                l[k].startingIndex=i;
                }
        else{
                if(l[k].leftSymbol == line[0]) l[k].numOfProd++;
                else{ k++;
                        l[k].leftSymbol=line[0];
                        l[k].numOfProd=1;
                        l[k].startingIndex=i;
                }
        }


           for(j=2;line[j]!='\0';j++)
           r[i].rightSymbols[j-2]=line[j];

           r[i].rightSymbols[j-2]='\0';

           printf("%s\n",r[i].rightSymbols);
   }
   numNonTer=k+1;
   numOfProd=i;


        printf("\n\nLeft Info Table\n");
     for(i=0;i<numNonTer;i++)
           printf("%c  %d  %d\n",l[i].leftSymbol,l[i].numOfProd,l[i].startingIndex);
}

void parsingTableRead()
{
        int i,j,k,temp,TempParser[50],n=0;
        char buffer[20];

        filePtr=fopen("table.txt","r");
        while(1)
        {

                if(fscanf(filePtr,"%d",&temp) == 1) {TempParser[n]=temp;n++;}
                else break;
        }

        numOfTer=(n+1)/numNonTer;
        k=0;
        for(i=0;i<numNonTer;i++)
                for(j=0;j<numOfTer;j++)
                        {parseTable[i][j]=TempParser[k];k++;}

        for(i=0;i<numNonTer;i++)
        {
                printf("\n");
        for(j=0;j<numOfTer;j++)
                printf("%2d ",parseTable[i][j]);
        }

        printf("\n\n");
}

main()
{
        rightLeftInfo();
        parsingTableRead();
        getch();
}
