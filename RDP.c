#include<stdio.h>
#include<string.h>

char string[' '];
int len;
int pos=0;

int E();
int Eplus();
int T();
int Tplus();
int F();
int main()
{
  printf("Enter the string:: ");
        scanf("%s",&string);
   len=strlen(string);
  if(E()==0) printf("\nNot Accepted");
  else if(pos<len) {printf("\nNot Accepted");}
  else printf("\nAccepted");

getch();
 return 0;
}

int E()
{
  if(T()==0) return 0;
  if(Eplus()==0) return 0;
  return 1;
}

int Eplus()
{
 if(string[pos]=='+')
        { pos++;
                if(T()==0) return 0;
                if(Eplus()==0) return 0;
        }
 return 1;
}

int T()
{
 if(F()==0) return 0;
  if(Tplus()==0) return 0;
 return 1;
}

int Tplus()
{
 if(string[pos]=='*')
        { pos++;
                if(F()==0) return 0;
                if(Tplus()==0) return 0;
        }

 return 1;
}

int F()
{
  if(string[pos]=='('){
                         pos++;
                        if(E()==0) return 0;
                        if(string[pos]==')') pos++;
                                else return 0;
                       }
  else if(string[pos]=='i'){
                       pos++;}
  else {return 0;}

 return 1;
}
