#include "error.h"
#include "analys.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define NBERRMAX 100

static int NBERRORS = 0;

// invariant : NBERRORS == NBERRSX + NBERRSM

static int NBERRSM = 0;
static int NBERRSX = 0;

static error * ERRORS[NBERRMAX*3];

void afficher_sm_erreur(SemanticErrorType et, int line, char* name){
 
  printf("ligne %d : %s ", line,  name);
  switch (et){
  case NotDeclared: printf("variable non declaree\n"); break;
  case NotInitialized: printf("variable non initialisee\n"); break;
  case IncompatibleOperationType:  printf("incompatible avec l'operation\n"); break;
  case BadlyInitialised:  printf("variable mal initialisee\n"); break;
  case AlreadyDeclared:  printf("variable deja declaree\n"); break;
  case IncompatibleForIndexType:  printf("type incompatible for index\n"); break;
  }
}
void creer_sm_erreur(SemanticErrorType et, int line, char* name){
  smerror * e = (smerror*) malloc (sizeof (smerror) );

  if (name != NULL){
	  e->name = (char *) malloc (strlen(name));
	  strcpy(e->name, name);
  }

  e->line = line;
  e->smerrort = et;

  ERRORS[NBERRORS] = (error*) malloc (sizeof (error) );

  ERRORS[NBERRORS]->errortype=SemanticError;      
  ERRORS[NBERRORS]->errorattribute.smerr= e   ;

  NBERRORS++;
  NBERRSM++;
}

void creer_sx_erreur(SyntacticErrorType et, int line){
    sxerror * e = (sxerror*) malloc (sizeof (sxerror) );
    e->line = line;
    e->sxerrort = et;

    
    ERRORS[NBERRORS] = (error*) malloc (sizeof (error) );
    ERRORS[NBERRORS]->errortype=SyntacticError;      
    ERRORS[NBERRORS]->errorattribute.sxerr= e;

    NBERRORS++;
    NBERRSX++; // on dénombre le nombres des erreurs syntaxiques
}


void afficher_sx_erreur(SyntacticErrorType et, int line){
  printf("ligne %d : ", line);
  switch (et){
	case IdfExpected : printf("idf attendu\n"); break;
 	case BeginExpected : printf("begin attendu\n"); break;
	case ThenExpected : printf("Then attendu\n"); break;
	case LoopExpected : printf("loop attendu\n"); break;
	case InumberExpected : printf("entier attendu\n"); break;
 	case ToExpected : printf(" ':' attendu\n"); break;
	case InExpected : printf("IN attendu\n"); break;
	case PvirgExpected : printf("; attendu\n"); break;
	case EndforExpected : printf("end for attendu\n"); break;
	case PcloseExpected : printf(") attendu\n"); break;
	case EqeqExpected : printf("= attendu\n"); break;
	case EndifExpected : printf("end if attendu\n"); break;
	case TypeExpected : printf("type attendu\n"); break;
	case ConstExpected : printf("constante attendu\n"); break;
	case InstructionExpected : printf("instruction attendu\n"); break;
	case EndExpected : printf("end attendu\n"); break;
	case EndiforelseExpected : printf("Endiforelse attendu\n"); break;
	case VirgExpected : printf(", attendu\n"); break;
	case inumberordnumberExpected : printf("numero attendu\n"); break;
	case AffExpected :printf(":= attendu\n"); break;

  }
}

void afficher_sx_erreurs(){
   int i;
   for (i=0; i<NBERRORS; i++){
	switch (ERRORS[ i ]->errortype){
	case	SyntacticError: afficher_sx_erreur(ERRORS[i]->errorattribute.sxerr->sxerrort, ERRORS[i]->errorattribute.sxerr->line); break;
	}
   }
}
void afficher_sm_erreurs(){
   int i;
   for (i=0; i<NBERRORS; i++){
	switch (ERRORS[ i ]->errortype){
	case	SemanticError :     afficher_sm_erreur(ERRORS[i]->errorattribute.smerr->smerrort, ERRORS[i]->errorattribute.smerr->line, ERRORS[i]->errorattribute.smerr->name);break;
	}
   }
}

int nombre_sx_erreurs(){
 return NBERRSX;
}
int nombre_sm_erreurs(){
	return  NBERRSM;
}


void afficher_erreurs(){
	int i;
	for (i=0; i<NBERRORS; i++){
		switch (ERRORS[ i ]->errortype){
		case	SemanticError :     afficher_sm_erreur(ERRORS[i]->errorattribute.smerr->smerrort, ERRORS[i]->errorattribute.smerr->line, ERRORS[i]->errorattribute.smerr->name);break;
		case	SyntacticError: afficher_sx_erreur(ERRORS[i]->errorattribute.sxerr->sxerrort, ERRORS[i]->errorattribute.sxerr->line); break;
	}
}
}

