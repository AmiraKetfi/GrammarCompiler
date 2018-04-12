%{
#include <stdio.h>
#include <string.h>
#include "liste.h"
int yylex();
int yyerror();
extern FILE *yyin;
extern yytext;
extern int yylineno;
%}

%error-verbose
%union
{   int intValue;
    float floatValue;
    char *stringValue;
    struct s { char *val; int type;}s;
}

/*TOKENS*/
%token idf mot entier reel nline sep Uint Ufloat
%token CHECK ENDCHECK REPEAT ENDREPEAT define
%token affect PO PF AO AF VP V PP Diff Tiret
%type <stringValue> idf
%type <intValue> entier
%type <floatValue> reel
%type <s> VARTYPE
%type <s> Expression_AR
%type <s> Expression_AR2
%type <s>  Expression_COM
%type <s> Expression_LOG
%type <s> COMP
%type <s> CONDITION
%type <s> COLOGIC
%type <s> Instructions
%type <s> Affectation
%type <s> Boucle
%type <s> Initialisation
%left  OR
%left  AND
%left  Negation
%left  Sup Inf SupEg InfEg Egal Diff
%left  addition soustraction 
%left  multiplication division 
 
%start PROGRAMME

%%

/*GRAMMAIRE*/
  PROGRAMME:   idf AO  PARTIE_DECLARATION AO Instructions AF AF ;

  
/*PARTIE DECLARATION*/
  PARTIE_DECLARATION: A C|D C;
  A: define DecConstante VP ;
  C:  | PARTIE_DECLARATION ;
  D: DecVariable VP;
  B1:  |SuiteVarE;
  B2:  |SuiteVarR;
  DecConstante: Uint idf affect entier {  Double_Declaration(tete,$2,yylineno) ; Inserer(tete,$2,"Constante","Entier",yylineno);} 
              | Ufloat idf affect reel {  Double_Declaration(tete,$2,yylineno) ; Inserer(tete,$2,"Constante","Réel",yylineno);} ;

  DecVariable : Uint idf B1 { Double_Declaration(tete,$2,yylineno) ;Inserer(tete,$2,"Identifiant","Entier",yylineno);} 
              | Ufloat idf B2 {Double_Declaration(tete,$2,yylineno) ; Inserer(tete,$2,"Identifiant","Réel",yylineno);} ;
  SuiteVarE: V idf B1 { Double_Declaration(tete,$2,yylineno) ; Inserer(tete,$2,"Identifiant","Entier",yylineno);} ;
  SuiteVarR: V idf B2 { Double_Declaration(tete,$2,yylineno) ; Inserer(tete,$2,"Identifiant","Réel",yylineno);} ;
/*PARTIE INSTRUCTIONS*/
  Instructions : Affectation F {$$.val=strdup($1.val);} | CONDITION F2 {$$.val=strdup($1.val);}| Boucle F2 {$$.val=strdup($1.val);};
  F: VP | VP Instructions;
  F2:   |  Instructions;
  /*Affectation*/
  Affectation : idf affect Expression_AR   {Affectation_Const(tete,$1,yylineno);TypeIcomp(tete,$1,yylineno); InsererQuad(&qtete,"=",$3.val,$1,i);char p[10]; sprintf(p,"T%d",i);$$.val=strdup(p);i++;};
  //Expression 
Expression_AR:Expression_AR2 addition Expression_AR {char p[10]; sprintf(p,"T%d",i);InsererQuad(&qtete,"+",$1.val,$3.val,i);$$.val=strdup(p);i++;if(verifierType($1.type,$3.type,ligne)==0){$$.type=$1.type;}}
|Expression_AR2 soustraction Expression_AR {char p[10]; sprintf(p,"T%d",i);InsererQuad(&qtete,"-",$1.val,$3.val,i);$$.val=strdup(p);i++;if(verifierType($1.type,$3.type,ligne)==0){$$.type=$1.type;}}|Expression_AR2 {$$.val=$1.val;};

Expression_AR2:VARTYPE multiplication Expression_AR2  {char p[10]; sprintf(p,"T%d",i);InsererQuad(&qtete,"*",$1.val,$3.val,i);$$.val=strdup(p);i++;if(verifierType($1.type,$3.type,ligne)==0){$$.type=$1.type;}}|VARTYPE division Expression_AR2 {char p[10]; sprintf(p,"T%d",i);InsererQuad(&qtete,"/",$1.val,$3.val,i);$$.val=strdup(p);i++;if(verifierType($1.type,$3.type,ligne)==0){$$.type=$1.type;}}|VARTYPE {$$.val=$1.val;};

VARTYPE : entier{char p[10]; sprintf(p,"%d",$1);$$.val=strdup(p);}|idf{$$.val=strdup($1);}|reel{char p[10]; sprintf(p,"%f",$1);$$.val=strdup(p);};

/*Expression Comparaison*/
  Expression_COM: Expression_AR COMP Expression_AR {InsererQuad(&qtete,"-",$3.val,$1.val,i);char p[10]; sprintf(p,"T%d",i);i++;InsererQuad(&qtete,$2.val," ",p,i);$$.val=strdup(p);i++;} ;
  COMP : Sup{$$.val=strdup("BMZ");}|Inf{$$.val=strdup("BPZ");}|SupEg{$$.val=strdup("BM");}|InfEg{$$.val=strdup("BP");}|Egal{$$.val=strdup("BNZ");}|Diff{$$.val=strdup("BZ");};
  /*Expression Logique*/
  Expression_LOG: Expression_COM{$$.val=strdup($1.val);}|Negation PO Expression_COM PF{$$.val=strdup($3.val);} | PO Expression_COM PF COLOGIC PO Expression_LOG PF {$$.val=strdup($2.val); if($6.val=="&"){InsererQuad(&qtete,"BMZ","Fin",$$.val,i); char p[10]; sprintf(p,"T%d",i);$$.val=strdup(p);i++; $$.val=strdup($6.val);} else{$$.val=strdup($6.val);}} ;
  COLOGIC: AND{$$.val=strdup("&");}|OR{$$.val=strdup("|");};
  /*Condition*/
  CONDITION : CHECK PO Expression_LOG PF PP Instructions ENDCHECK {InsererQuad(&qtete,"BR","ENDCHECK",$3.val,i);char p[10]; sprintf(p,"T%d",i); $$.val=strdup(p);i++; $$.val=strdup($6.val);};
  /*Boucle*/ 
  Boucle: REPEAT PP Initialisation PP PO Expression_LOG PF PP Affectation PP Instructions ENDREPEAT{char p[10]; $$.val=strdup($3.val);i++;$$.val=strdup($6.val);i++;$$.val=strdup($11.val);i++;$$.val=strdup($9.val);i++; sprintf(p,"T%d",i); InsererQuad(&qtete,"BR",$3.val,p,i);$$.val=strdup(p);i++;};
  /*Initialisation*/ 
  Initialisation : idf affect VARTYPE{InsererQuad(&qtete,"=",$3.val,$1,i);char p[10]; sprintf(p,"T%d",i);$$.val=strdup(p);i++;};

%%

int yyerror(char *s)  { printf("Error at line: %d ==>%s",yylineno,s);}

int main()
{
tete = Init();
yyin = fopen("input.txt","r");
yyparse();
//Affichage(tete);
//AfficheQuad(qtete);
//printf("%s\n",qtete->temp);
Ecrire_QUAD(qtete);
Ecrire_TS(tete);
return 0;
 } 


