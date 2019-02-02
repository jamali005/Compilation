#include "tablesymb.h"
//#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define debug false

#define NBS 100
static varvalueType TS[NBS];  

static int NBVAR = 0;

void incrementer_nombre_declarations(int rangvar){
 TS[rangvar].nbdecl++; 
}  

void ajouter_nouvelle_variable_a_TS(varvalueType newvar){
	if (debug) printf("ajouter_nouvelle_variable_a_TS()");
	//printf("T1\n");
	  TS[NBVAR].nbdecl = newvar.nbdecl;
	//printf("T2\n");
	  TS[NBVAR].name = (char *)malloc((strlen(newvar.name)+1)*sizeof(char));
	//printf("T3\n");
	  strcpy(TS[NBVAR].name,newvar.name);
	//printf("T4\n");
	  TS[NBVAR].line = newvar.line;
	//printf("T5\n");
	  TS[NBVAR].initialisation = newvar.initialisation;
	//printf("T6\n");
	  TS[NBVAR].typevar = newvar.typevar;
	//printf("T7\n");
	  TS[NBVAR].valinit = newvar.valinit;
	//printf("T8\n");
/*

	if (debug) {
		switch( TS[NBVAR].typevar ){
			case String : printf("variable %d = %s, de type %s, initialisee a %s et declaree %d fois\n",
				NBVAR,
				TS[NBVAR].name,
				"string",
				svalue(TS[NBVAR].valinit),
				TS[NBVAR].nbdecl);  
				break;
			default : printf("variable %d = %s, de type %s, initialisee a %s et declaree %d fois\n",
				NBVAR,
				TS[NBVAR].name,
				TS[NBVAR].typevar==Integer?"integer":(TS[NBVAR].typevar==Double?"double":"bool"),
				(TS[NBVAR].typevar==Bool?(dvalue(TS[NBVAR].valinit)==true?"true":"false"):strcat(myitoa(dvalue(TS[NBVAR].valinit)),"...")),
				TS[NBVAR].nbdecl);
				break;  //a reffaaaaaaaaire 
		}
   	}*/
	  //  incrementer_nombre_variables incrementer_nombre_variables
	  NBVAR++;
	/*if (debug) printf("out ajouter_nouvelle_variable_a_TS()");*/
}





void afficherTS(){
  int i=0;
  for (i=0; i<NBVAR; i++) {
    //printf("%f-->",    TS[i].valinit);
    switch( TS[i].typevar ){
	case String : printf("variable %d = %s, de type %s, initialisee a %s et declaree %d fois\n",
			i,
			TS[i].name,
			"string",
			svalue(TS[i].valinit),
			TS[i].nbdecl);  
			break;
	default : printf("variable %d = %s, de type %s, initialisee a %s et declaree %d fois\n",
			i,
			TS[i].name,
			TS[i].typevar==Integer?"int":(TS[i].typevar==Float?"Float":(TS[i].typevar==Natural?"Natural":(TS[i].typevar==Char?"caractere":"bool"))),
			(TS[i].typevar==Bool?(dvalue(TS[i].valinit)==true?"true":"false"):strcat(myitoa(dvalue(TS[i].valinit)),"...")),
			TS[i].nbdecl);
			break;  //refaire
   }
 }

// "..." means float value non showed itoa
// itoa ==> ftoa valinit est flottante !!
}


boolean inTS(char * varname, int * rangvar){
//printf("enter inTS(%s)\n", varname);
  int i =0;
  
  char * lowervname = lowercase(varname);

  while ((i < NBVAR) && (strcmp(TS[i].name,lowervname) != 0)) i++;
  
//printf("out inTS\n");
  if (i == NBVAR) return false;
  else { *rangvar = i; return true;}
}
/*
void incrementer_nombre_declarations(int rangvar){
 TS[rangvar].nbdecl++; 
}  */
char* name(int rang){
  return TS[rang].name;
}


Type typevar(int rang){
  return TS[rang].typevar;
}

// prdicat vrifiant si une variable est dfinie (ex. par une initialisation, une affectation, for)
boolean est_definie(int rang){
	return   TS[rang].initialisation;
}
// prdicat vrifiant si une variable est utilisee dans le code ou pas par une instruction
boolean est_utilisee(int rang){
	return   TS[rang].utilisation;
}


// setter servant au prdicat est_definie
void definir(int rang){ // peut tre appele soit  l'initilisation ou  l'affectation
	TS[rang].initialisation = true;
}
int nombre_variables(){
	return NBVAR;
}

Element value(char *idf){
  //afficherTS(); 
  //printf("value( %s )==",idf);
  //return 0.0; 
  
  int rangvar; // = (int*) malloc(sizeof(int));
  boolean ilyest= inTS(idf, &rangvar);
  if (debug){
    if (ilyest != true) printf("bug(%s) n'est pas dans la TS\n",idf);
    else{
      printf("RANG == %d", rangvar);
      printf("( %s ) == %s", idf, name(rangvar));
      switch(typevar(rangvar)){
	case String :       printf(" est dans la TS de valeur = %s\n", svalue(valinit(rangvar))); break;
	default : printf(" est dans la TS de valeur = %f\n", dvalue(valinit(rangvar))); break;
      }
      afficherTS();
    }
  }
  return valinit(rangvar);

  // je ne comprends pas pourquoi les instructions suivantes donne un segmentation fault alors que quivalentes ?
  // int *rangvar;
  // inTS(idf, rangvar);
  // return (double) (valinit(*rangvar));
}

Element valinit(int rang){
  return TS[rang].valinit;
}

void set_dvalinit(int rang, double d){

  setdvalue(&(TS[rang].valinit), d) ;

  TS[rang].initialisation = true;

}

void set_svalinit(int rang, char *s){

  setsvalue(&(TS[rang].valinit), s);

  TS[rang].initialisation = true;

}


/* myitoa: convert n to characters in s */
char * myitoa(int n){
	int i = 0;
	char s[100];
	char * result;
	do { /* generate digits in reverse order */
		s[i++] = n % 10 + '0'; /* get next digit */
		} while ((n /= 10) > 0); /* delete it */
	s[i] = '\0';
	reverse(s);
	result = (char *) malloc(strlen(s) + 1);
	strcpy(result, s);
	return result;
}


/* reverse: reverse string s in place */

void reverse(char s[]){
	int i, j;
	char c;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char * lowercase(char * s){

	int length = strlen( s );
	
	char * result = (char *)malloc ((length+1)*sizeof(char));

	int i;

	for (i = 0; i < length; i++) result[i] = tolower(s[i]);

	result[ length ] = '\0';

	return result;
}

