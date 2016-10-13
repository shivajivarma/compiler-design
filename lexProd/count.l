%{
int lines=0,characters=0,words=0;
%}
%%
\n  {lines++;characters++;}
[^ \n\t]+ {words++;characters=characters+yyleng;}
. {characters++;}
%%
int main()
{
yylex();
printf("lines::%d characters::%d words::%d",lines,characters,words);
return 0;
}

