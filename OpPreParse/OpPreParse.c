#include<stdio.h>
#include<string.h>

FILE *fp;
char prodFile[]="test.txt";
char relFile[]="table.txt";
int numProductions,numTerminals,top=0,terTop=0,ip=0;
int relationTable[' '][' '];
char stack[' ']="$";
char inputBuffer[' '];
char string[' '];
char handle[' '],handTopTer;

char term[' '];

struct
{
    char left;
    char right[' '];
}prod[' '];



void readProductions()
{
  int i,j;
  char line[30];

  fp=fopen(prodFile,"r");
  for(i=0;fscanf(fp,"%s",line)==1;i++)
  {
        prod[i].left=line[0];
          for(j=2;line[j]!='\0';j++)
            prod[i].right[j-2]=line[j];
        prod[i].right[j-2]='\0';
  }

   numProductions=i;

   printf("Productions::\n");
   for(i=0;i<numProductions;i++){
    printf("%c>",prod[i].left);
    printf("%s\n",prod[i].right);
   }
}


int validateNonTer(char z)
{
        int i;
        for(i=0;i<numProductions;i++)
        {
                if(z==prod[i].left) {return 1;}
        }
        return 0;
}


void findTerminals()
{
        int i,j;
        numTerminals=0;
        for(i=0;i<numProductions;i++)
                for(j=0;prod[i].right[j]!='\0';j++)
                        if(!validateNonTer(prod[i].right[j])) {term[numTerminals]=prod[i].right[j];numTerminals++;}


        printf("\nTerminals::\n");
        for(i=0;i<numTerminals;i++)
        printf("%c\n",term[i]);
}


void readRelationTable()
 {
  int i,j,k=0;
  fp=fopen(relFile,"r");


  for(i=0;i<=numTerminals;i++)
   for(j=0;j<=numTerminals;j++)
   {
      fscanf(fp,"%d",&relationTable[i][j]);
    }


    printf(" ");
    for(i=0;i<=numTerminals;i++)
          if(i==numTerminals)  printf(" $");
          else printf("%2c ",term[i]);
    for(i=0;i<=numTerminals;i++)
    {
     if(numTerminals==i) printf("\n$");
     else printf("\n%c",term[i]);
     for(j=0;j<=numTerminals;j++)
                          printf("%2d ",relationTable[i][j]);
     }
}

int searchProd(char z[50])
{
        int i;
        for(i=0;i<numProductions;i++)
                if(strcmp(z,prod[i].right)==0) return i;
        return -1;
}

int pos(char z)
{
        int i;
  for(i=0;i<numTerminals;i++)
          if(term[i]==z) {return i;}
  if(z=='$') return i;
  else return -1;
}

void push(char z)
{
     top++;
     stack[top]=z;
     if(pos(stack[top]) != -1) terTop=top;
     printf("push::%c\n",z);
}
void terToprec()
{
     terTop--;
     while(pos(stack[terTop])== -1) terTop--;
}
char pop()
{
   if(pos(stack[top])!= -1) {terToprec();handTopTer=stack[top];}
   char temp=stack[top];
   printf("pop::%c\n",temp);
   top--;
   return temp;
}

void reverse(char *r)
{
        int len=strlen(r),i;
     for(i=0;i<len/2;i++)
     {
             char temp=r[i];
             r[i]=r[len-1-i];
             r[len-1-i]=temp;
        }
}

int Parse()
{
     int i;
     char a,b;
     printf("\n\nEnter string::");
     scanf("%s",string);
     for(i=0;string[i]!='\0';i++)
     inputBuffer[i]=string[i];
     inputBuffer[i]='$';
     while(1)
     {
           if(stack[terTop]=='$' && inputBuffer[ip]=='$') return 1;
           else {a=stack[terTop];
                  b=inputBuffer[ip];

                   printf("-----------------------------------------------\na::%c  b::%c\n",a,b);
                        if(relationTable[pos(a)][pos(b)]== 1 || relationTable[pos(a)][pos(b)]==0)
                        {push(b);ip++;}

                        else if(relationTable[pos(a)][pos(b)]==2)
                        {
                                int k=0;
                                handle[k]=pop();
                                if(pos(handle[k])== -1) {k++;handle[k]=pop();}
                                k++;
                                while(relationTable[pos(stack[terTop])][pos(handTopTer)] != 1)
                                        {handle[k]=pop();k++;}
                                        while(terTop!=top) {handle[k]=pop();k++;}
                                        handle[k]='\0';
                                reverse(handle);
                                printf("Handle  %s\n",handle);
                                if(searchProd(handle)!=-1) push(prod[searchProd(handle)].left);
                                else return 0;
                        }
                        else return 0;
                  }
     }
}

int main()
{
     readProductions();
     findTerminals();
     readRelationTable();
     if(Parse()) printf("Accepted");
                 else printf("InValid");
                 
     getch();
}
