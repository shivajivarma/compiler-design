digit [0-9]
%%
{digit}* printf("%s",yytext);
.* printf(" ");
%%
