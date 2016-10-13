letter [a-z,A-Z]
digit [0-9]
%%
{letter}({letter}|{digit}|_)*  printf("indentifier");
.* printf("Invalid");
%%
