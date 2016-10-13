#include<stdio.h>
#include<ctype.h>
#include<string.h>

FILE *fptr;
char fileName[]="table.txt";
char buffer[42],ch,
     keyword[' '][' ']={"int","char","if","then","else","for","while"};
int NumberOfKeywords=8,fwdPtr=41,lexbegin=0,count=20,i,state=0,ERROR=100;


int FirstRead(char *buffer,FILE *fptr){ return (int) fread(buffer,sizeof(char),20,fptr); }

int SecondRead(char *buffer,FILE *fptr){ return (int) fread(buffer+21,sizeof(char),20,fptr); }

void pushBack(){fwdPtr--;}

void keywordCheck(int lexbegin,int fwdPtr)
{
     char identifier[20];
     int i,j=0;
     for(i=lexbegin;i!=fwdPtr;i=(i+1)%41)
      if(buffer[i]!=EOF)  {identifier[j]=buffer[i];j++;}
     identifier[j]='\0';

   for(i=0;i<NumberOfKeywords;i++)
           if(strcmp(identifier,keyword[i])==0) {printf(" %s ",keyword[i]);break;}
   if(i==NumberOfKeywords)
    printf("<id,%s>",identifier);
}

void main()
{

 buffer[20]=buffer[41]=EOF;
 fptr=fopen(fileName,"r");

 while(1)
 {
   ch=buffer[fwdPtr];

   if(ch==EOF && fwdPtr==41)
        {
        count=FirstRead(buffer,fptr);
        if(count!=20) buffer[count-1]=EOF;
        fwdPtr=0;
        }
   else if(ch==EOF && fwdPtr==20)
        {
        count=SecondRead(buffer,fptr);
        if(count!=20) buffer[count+20]=EOF;
        fwdPtr=21;
        }

   else
   {
        switch(state)
        {
                        case 0: lexbegin=fwdPtr;
                                if(ch==' '||ch=='\n'||ch=='\t') break;
                                else if(isalpha(ch)) state=1;
                                else if(isdigit(ch)) state=3;
                                else if(ch=='/') state=5;
                                else if(ch=='<') state=8;
                                else if(ch=='>') state=9;
                                else if(ch=='=') state=10;
                                else if(ch=='!') state=11;
                                else {
                                        state=ERROR;
                                        pushBack();
                                     }
                                break;
                                
                        case 1:if(isalnum(ch)||ch=='_') state=1;
                                else {
                                      keywordCheck(lexbegin,fwdPtr);
                                      pushBack();
                                      state=0;
                                     }
                                break;
                                
                        case 3:if(isdigit(ch)) state=3;
                                else{
                                       printf("<constant>");
                                       pushBack();
                                       state=0;
                                        
                                }
                                break;
                                
                        case 5:if(ch=='*') state=6;
                                else{
                                        state=ERROR;
                                        pushBack();
                                        pushBack();
                                        }
                                break;
                                
                        case 6:if(ch=='*') state=7;
                                           break;
                                           
                        case 7:if(ch=='/') state=0;
                             else state=6;
                             break;
                             
                        case 8:if(ch=='=') printf("<= ");
                             else { printf("< ");pushBack();}
                             state=0;
                             break;
                             
                        case 9:if(ch=='=') printf(">= ");
                             else { printf("> ");pushBack();}
                             state=0;
                             break;
                             
                        case 10:if(ch=='=') printf("== ");
                             else { printf("= ");pushBack();}
                             state=0;
                             break;
                             
                        case 11:if(ch=='=') {printf("!= ");state=0;}
                             else { state=ERROR;pushBack();pushBack();}
                             break;
                                  
                        case 100:printf("[%c]",ch); state=0;

        }
        if(ch==EOF) return;
       fwdPtr++;
   }
}
}
