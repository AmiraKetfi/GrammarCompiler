# GrammarCompiler
A C,Bison and Flex Compiler for Definer Grammar

#### Files Description :  
* Liste.h :
  * Contains Control routines.
  * Insertion Routines(Symboles Table and Quedruplets Table).
* flex.l : Contains the Introduction to the different Operatos and symboles.
* Bison.y : Contains the Grammar Structure.
* Test : 
  You will find an example of execution :
    * InputFile : input.txt
    * Output Files : TS.txt and Quadruplets.txt
#### How To Run And Execute : 
On your terminal Execute the following Commands :
``` > flex flex.l 
``` > bison -d bison.y 
``` > gcc lex.yy.c bison.tab.c -lfl -ly
