%{
#include <stdio.h>
#include <string.h>
#include "bison.tab.h"
extern YYSTYPE yylval;
int colonne=1,ligne=1;
%}

%option yylineno

idf [a-zA-Z]+[0-9a-zA-Z_]*
entier [0-9]+
reel [0-9]+"."[0-9]+
comment [/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]      
nline [\n]+
space [\t]+ 

%%

"//".*  { } 
"_" {colonne +=yyleng;return Tiret;}
"," {colonne +=yyleng;return V;}
":" {colonne +=yyleng;return PP;}
";" {colonne +=yyleng;return VP;}
"=" {colonne += yyleng;return affect;}
"+" {colonne += yyleng;return addition;}
"-" {colonne += yyleng;return soustraction;}
"/" {colonne += yyleng;return division;}
"*" {colonne += yyleng;return multiplication;}
"Uint" {colonne += yyleng;return Uint;}
"Ufloat" {colonne += yyleng;return Ufloat;}
"CHECK" {colonne += yyleng;return CHECK;}
"ENDCHECK" {colonne += yyleng;return ENDCHECK;}
"REPEAT" {colonne += yyleng;return REPEAT;}
"ENDREPEAT" {colonne += yyleng;return ENDREPEAT;}
"define" {colonne += yyleng;return define;}
"(" {colonne += yyleng;return PO;}
")" {colonne += yyleng;return PF;}
"{" {colonne += yyleng;return AO;}
"}" {colonne += yyleng;return AF;}
">" {colonne += yyleng;return Sup;}
"<" {colonne += yyleng;return Inf;}
">=" {colonne += yyleng;return SupEg;}
"<=" {colonne += yyleng;return InfEg;}
"==" {colonne += yyleng;return Egal;}
"!=" {colonne += yyleng;return Diff;}
"&" {colonne += yyleng;return AND;}
"|" {colonne += yyleng;return OR;}
"!" {colonne += yyleng;return Negation;} 
" " { }
{comment} { }


{idf}    {
      	  yylval.stringValue=strdup(yytext);
          if(yyleng<=8) {return (idf);}
          else {printf("\nErreur: ligne :%d colonne :%d Identificateur trop grand\n",ligne,colonne);} 
         }

{entier} {
          yylval.intValue=atoi(yytext);
          if(atoi(yytext)<32767) {return (entier);}
          else {printf("\nErreur: ligne :%d colonne :%d Entier trop grand\n",ligne,colonne);} 
         }
{reel}   {
          yylval.floatValue=atof(yytext);
          if(atof(yytext)<32767) {return (reel);}
          else {printf("\nErreur: ligne :%d colonne :%d Réel trop grand\n",ligne,colonne);}
         }

{nline} {colonne=0; ligne++; }
{space} {colonne += yyleng;}
. {printf("\n\t %s : Erreur ligne :%d colonne :%d PAs d'entité lexicale correspondante\n",yytext,ligne,colonne);}

%%
 
int yywrap(){return 1;}
