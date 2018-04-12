#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************LISTE*********************/
//Structure of an element
struct liste
{
   char nom_entite[20];
   char type_entite[20];
   char nature_entite[20];
    int ligne;
   struct liste *suiv;
};
typedef struct liste liste;

/*********************************************/

/**************LES QUADRUPLETS*****************/

//STRUCTURE DU QUADRUPLET
struct quadruplet
{
char op1[20]; 
char op2[20];
char operateur[20];
char temp[20];
int numTemp;
struct quadruplet *suiv;
};
typedef struct quadruplet quadruplet;

//STRUCTURE DE LA PILE
//
typedef struct QuadElement 
{ 
quadruplet quad;
char *type;
struct QuadElement *suiv; 
} QPile;
//extern quadruplet *qtete;
//FONCTION INITIALISATION DU QUADRUPLET
quadruplet *InitQuad()
{
quadruplet *tete;
tete=malloc(sizeof(quadruplet));
tete->suiv=NULL;
tete->numTemp=0;
//snprintf(tete->operateur, sizeof(tete->operateur), "");
  //snprintf(tete->op1, sizeof(tete->op1), "" );
 // snprintf(tete->op2, sizeof(tete->op2), "");
  //snprintf(tete->temp,sizeof(tete->temp),"");
return tete;
}


//INSERER UN QUADRUPLET
void InsererQuad(quadruplet **tete,char *operateur, char *operande1, char *operande2, int i)
{
 if(*tete==NULL) *tete=InitQuad();
 quadruplet *T=*tete,*P=NULL;
 char resultat[10];
 //char *temp;
  P=malloc(sizeof(quadruplet));
  snprintf(P->operateur, sizeof(P->operateur)+1, "%s",operateur);
  snprintf(P->op1, sizeof(P->op1+1), "%s",operande1 );
  snprintf(P->op2, sizeof(P->op2)+1, "%s",operande2);
  //Evaluation(operateur,operande1,operande2,resultat);
  P->numTemp=i;
  //sprintf(resultat,"T%d",P->temp);
  //snprintf(P->temp, sizeof(P->temp)+1,"%s",resultat);
  sprintf(P->temp,"T%d",P->numTemp);
  //if(tete==NULL) tete=P; 
  //else{
  while(T->suiv!=NULL){T=T->suiv;}
  T->suiv=P;//}
  //return P->numTemp;
}


//FONCTION INITIALISATION DE LA PILE
QPile *InitPile (QPile *sommet) 
{ 	
sommet = NULL; 
return sommet; 
} 
//FONCTION EMPILER
//
QPile * Empiler (QPile *sommet, quadruplet quad,char type[]) 
{ 
QPile *nouveau; 
nouveau = (QPile *) malloc(sizeof (QPile)); 
if (nouveau == NULL) 
printf("Erreur d'allocation de memoire -- pile pleine\n"); 
else 
{ 
nouveau->quad = quad; 
nouveau->type = type;
nouveau->suiv = sommet; 
sommet = nouveau; 
} 
        return sommet; 
}
//FONCTION DEPILER
QPile * Depiler (QPile *sommet, quadruplet *quad, char *type[]) 
{ 
QPile *elmt;
int i=PileVide(sommet);
if (i==1) 
 exit(1); 
else 
{ 
elmt = sommet; 
*quad = elmt->quad; 
*type = elmt->type;
sommet = elmt->suiv; 
} 
return sommet; 
}
//FONCTION PILEVIDE
int PileVide (QPile *sommet) 
{ 
if(sommet == NULL)
	return 1;
else return 0;
}
//FONCTION QUI EVALUE UNE EXPRESSION ARITHMETIQUE
/*void Evaluation(char operateur,char *operande1, char *operande2, char resultat[])
{
	int opr1,opr2;

	VerifierNombre(operande1,&opr1); VerifierNombre(operande2,opr2);
	//VerifierOperater(operateur);
	switch(operateur){

		case '-': *resultat = (char)(opr1-opr2);   break;
		case '+': *resultat = (char)(opr1+opr2); break;
		case '*': *resultat = (char)(opr1*opr2); break;
		case '/': *resultat = (char) (opr1/opr2); break;
	}

}
 //FONCTION QUI TRANSFORME L'IDF EN ENTIER/FLOAT
void VerifierNombre(char *ch, int *Nb) 
{ 
   char type; 
   int i = 0; 
   *Nb = 0; 
   while (ch[i] != '\0') 
   { 
       if ((ch[i] >= '0') && (ch[i] <= '9')) 
          *Nb = *Nb * 10 + ch[i] - '0'; 
       else if ( ch[i] == '-') 
            { 
                 *Nb = (*Nb) * -1;  
            }  
                 
       i++; 
   } 
}*/ 
// FONCTION QUI VERIFIE L'OPERATEUR EST UN OPERATEUR
/*int VerifierOperateur(char *ch) 
{ 
   if (strlen(ch)==1) 
      if ((ch[0] == '+') || (ch[0] == '-') || (ch[0
] == '*') || (ch[0] =='/')) 
         return 1; 
      else 
         return 0; 
   return 0; 
}*/ 

//FONCTION QUI AFFICHE LES QUADRUPLETS
//
void AfficheQuad(quadruplet *tete){
if(tete==NULL) printf("non quadruplet\n");
else{
quadruplet *P; P=tete; P=P->suiv;
printf("\n                    /********Quadruplet*********/\n");
printf("\t_____________________________________________________\n");
printf("\t|   Operateur |  Operande1  | Operande2  |  Temp    |\n");
printf("\t____________________________________________________|\n");
while(P!=NULL)
{printf("\t|%11s  |%11s   |%11s |%8s |\n",P->operateur,P->op1,P->op2,P->temp);
 P=P->suiv;}
}

}

//FONCTION QUI ECRIT LES QUADRUPLETS DANS UN FICHIER 
 void Ecrire_QUAD(quadruplet *tete){
	
	FILE *fichier=NULL;
	fichier= fopen("Quadruplets.txt","w+");

	if(fichier !=NULL)
	{
	quadruplet *P; P=tete; P=P->suiv;
	fprintf(fichier,"\n                    /********Quadruplet*********/\n");
	fprintf(fichier,"\t_____________________________________________________\n");
	fprintf(fichier,"\t|   Operateur |  Operande1  | Operande2  |  Temp    |\n");
	fprintf(fichier,"\t____________________________________________________|\n");

	while(P!=NULL)
	{	fprintf(fichier,"\t|%11s  |%11s   |%11s |%8s |\n",P->operateur,P->op1,P->op2,P->temp);
 	        P=P->suiv;
	}
	fclose(fichier);
	}
	else{
		printf("ERROR: impossible d'ouvrir le fichier\n");
	}
 }


quadruplet *qtete;
extern quadruplet *qtete;
extern int i=0;
//qtete=InitQuad();
//extern qtete;

/**************************************************/

extern liste *tete;

/***************TABLE DES SYMBOLES ET ROUTINES********************/
//FONCTION RECHERCHE
int Recherche(liste *tete, char entite[])
{
liste *P=tete;
while(P!=NULL) {
if(strcmp(entite,P->nom_entite)==0){return P->ligne; }
P=P->suiv;     }
return -1;}


//FONCTION DOUBLE DECLARATION
void Double_Declaration(liste *tete, char entite[], int ligne)
{
liste *P=tete;  int i=-1;
while(P!=NULL & i==-1) {
if(strcmp(entite,P->nom_entite)==0){i=P->ligne;}
P=P->suiv;     }
if(i!=-1)
{
if(i==ligne){printf("Erreur double declaration %s dans la meme ligne ==> %d\n",entite,ligne);}
if(i!=ligne){printf("Erreur double declaration %s lignes differentes ==> %d Et %d\n",entite,ligne,i);}
}}


//FONCTION AFFECTAION CONSTANTE 
void Affectation_Const(liste *tete, char entite[], int ligne)
{
liste *P=tete; int i=0;
if(NDec(tete,entite,ligne)==0)
{
while(P!=NULL) {
if(strcmp(entite,P->nom_entite)==0 && strcmp(P->type_entite,"Constante")==0 )
{i=-1;}
P=P->suiv;  }
if(i==-1){printf("Erreur affectation a constante: %s ligne ==> %d\n",entite,ligne);}
}
}
//FONCTION QUI RECUPERE LE TYPE 

/*void RecupType(liste *tete, char entite[], char type[])
{
	liste *P=tete; int i=0;
	while(P!=NULL)
		{
			if(stcmp(entite,P->nom_entite)==0
		P=P->suiv;			type = entite->type_entite;
		}
}*/

//FONCTION INCOMPATIBILITÉ DES TYPES

void TypeIcomp(liste *tete , char entite[], int ligne)
{
	liste *P=tete; int i=0; 
	liste *Q=P->suiv;
	while(P->suiv!=NULL && i!=-1) {
		if(strcmp(entite,P->nom_entite)==0){ 
		if(strcmp(P->type_entite,Q->type_entite)<0) i=-1;
		}
		P=P->suiv; Q=Q->suiv;
	}
if(i==-1){printf("Erreur type icompatible lors de l'affectation : ligne====>%d\n",entite,ligne);}	
}

//FONCTION NON DECLARATION

int NDec(liste *tete, char entite[],int ligne)
{
liste *P=tete; int i=-1;
while(P!=NULL) {
if(strcmp(entite,P->nom_entite)==0){i=0;}
P=P->suiv;     }
if(i==-1) printf("%s non declaré a la ligne %d\n",entite,ligne); return i;}

//FONCTION INSERTION
void Inserer(liste *tete,char entite[], char code1[], char code2[], int ligne)
{
if (Recherche(tete,entite)==-1)
{ liste *T=tete,*P=NULL;
  P=malloc(sizeof(liste));
  snprintf(P->nom_entite, sizeof(P->nom_entite), "%s",entite);
  snprintf(P->type_entite, sizeof(P->type_entite), "%s",code1 );
  snprintf(P->nature_entite, sizeof(P->nature_entite), "%s",code2);
  P->ligne=ligne;
  P->suiv=NULL;
  while(T->suiv!=NULL){T=T->suiv;}
  T->suiv=P;
}
}

//Fonction initialisation de la tete
liste *Init()
{liste *tete;
tete=malloc(sizeof(liste));
snprintf(tete->nom_entite,sizeof(tete->nom_entite), "%s", " ");
snprintf(tete->type_entite, sizeof(tete->type_entite), "%s", " ");
snprintf(tete->nature_entite, sizeof(tete->nature_entite), "%s", " ");
tete->suiv=NULL;
return tete;

}


//FONCTION QUI AFFICHE LA LISTE
void Affichage(liste *tete)
{liste *P; P=tete; P=P->suiv;
printf("\n                  /********Table des symboles*********/\n");
printf("\t___________________________________________________________________\n");
printf("\t|   NomEntite    |  NatureEntite    |  TypeEntite  |   Ligne Entite\n");
printf("\t___________________________________________________________________\n");

while(P!=NULL)
{printf("\t|%15s |%15s   |%12s  |%12d\n",P->nom_entite,P->type_entite,P->nature_entite,P->ligne);
 P=P->suiv;}}

 //FONCTION QUI ECRIT LA TS DANS UN FICHIER 
 
 void Ecrire_TS(liste *tete){
	
	 FILE *fichier=NULL;
	fichier= fopen("TS.txt","w+");

	if(fichier !=NULL)
	{
		liste *P; P=tete; P=P->suiv;
	fprintf(fichier,"\n                  /********Table des symboles*********/\n");
	fprintf(fichier,"\t___________________________________________________________________\n");
	fprintf(fichier,"\t|   NomEntite    |  NatureEntite    |  TypeEntite  |   Ligne Entite\n");
	fprintf(fichier,"\t___________________________________________________________________\n");

	while(P!=NULL)
	{	fprintf(fichier,"\t|%15s |%15s   |%12s  |%12d\n",P->nom_entite,P->type_entite,P->nature_entite,P->ligne);
 	P=P->suiv;
		//fclose(fichier);
	}
	fclose(fichier);
	}
	else{
		printf("ERROR: impossible d'ouvrir le fichier\n");
	}
 }

 liste *tete;	

