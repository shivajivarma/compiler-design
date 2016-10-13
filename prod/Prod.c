#include<stdio.h>

FILE *filePtr;
char line[50];
int i,j;

struct production
{
         char leftSymbol;
         char rightSymbols[20];
}p[20];

main()
{
   filePtr=fopen("prod.txt","r");

   for(i=0;fscanf(filePtr,"%s",line)==1;i++)
   {
           p[i].leftSymbol=line[0];

           for(j=2;line[j]!='\0';j++)
           p[i].rightSymbols[j-2]=line[j];

           p[i].rightSymbols[j-2]='\0';

           printf("%c-->%s\n",p[i].leftSymbol,p[i].rightSymbols);
   }
   getch();
}
