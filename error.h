#ifndef ERROR_H
#define ERROR_H

// Types ncessaires  la gestion des erreurs


typedef enum {IdfExpected=0,
	       BeginExpected=1,
		LoopExpected=2,
		InumberExpected=3,
		ToExpected=4, 
		InExpected=5,
	        PvirgExpected=6,
		EndforExpected=7,
		ThenExpected=8,
		PcloseExpected=9,
		EqeqExpected=10,
		PopenExpected=11,
		EndifExpected=12,
	        EndiforelseExpected=13,
		TypeExpected=14,
		ConstExpected=15,
		AddorsubExpected=16,
		MultordivExpected=17,
		TrueorFalseExpected=18,
		//MultordivorplusorminusorpvirgorpcloseExpected,
		inumberordnumberExpected=19,
		InstructionExpected=20,
		EndExpected=21,
		VirgExpected=22,
	       	NonCategorized=29,
		AffExpected=30
		} SyntacticErrorType;

typedef enum {NotDeclared=30,
	      AlreadyDeclared=31,
	      NotInitialized=32,
	      BadlyInitialised=33,
	      //IncompatibleAssignType=34,
	     //IncompatibleCompType=35,
	      IncompatibleOperationType=36,
	      IncompatibleForIndexType=37
	      
//	      IncompatibleForSwitch=38,
//	      MultipleValueForSwitch=39,
//	      DivisionbyZero=40
} SemanticErrorType;
typedef enum {SyntacticError=41 , SemanticError=42} ErrorType;

typedef struct {
  char *name;
  int line;
  SemanticErrorType smerrort;
} smerror;

typedef struct {
  int line;
  SyntacticErrorType sxerrort;
} sxerror;


typedef union{
	sxerror * sxerr ;
	smerror * smerr ;
} errorAttribute;

typedef struct{
ErrorType errortype;
errorAttribute errorattribute;
} error ;

extern void creer_sx_erreur(SyntacticErrorType et, int line);

extern void afficher_sx_erreur(SyntacticErrorType et, int line);

extern int nombre_sx_erreurs();

extern void creer_sm_erreur(SemanticErrorType et, int line, char * name);

//extern void creer_sm_erreur_instruction(SemanticErrorType et, int line, char* name);
extern void creer_sm_erreur_declaration(SemanticErrorType et, int line, char* name);

extern void afficher_sm_erreur(SemanticErrorType et, int line, char* name);

extern int nombre_sm_erreurs();

extern void afficher_sx_erreurs();
extern void afficher_sm_erreurs();
extern void afficher_erreurs();

#endif

