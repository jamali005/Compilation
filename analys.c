#include "analys.h"
#include "tablesymb.h"
#include "cfg.h"
#include "error.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylex();

typetoken token;
boolean follow_token;


varvalueType varattribute;
typevalueType typeattribute;
tokenvalueType tokenattribute;
constvalueType constattribute;
stringvalueType stringattribute;

int localrangvar;


int rangvar;
boolean semanticerror = false;

/*
TYPE = INTEGER|STRING|FLOAT|CHAR|BOOL|NATURAL|POSITIVE|IDF|CONSTANT
CONST = DNUMBER|INUMBER|TRUE|FALSE
CONSTAUX = CONST|ARRAY
DECL_AUX = := CONSTAUX PVIRG | PVIRG
DECL = IDF : TYPE DECL_AUX|
LISTE_DECL = DECL LISTE_DECL_AUX 
LISTE_DECL_AUX = LISTE_DECL | EPS
PROG : LISTE_DECL begin LISTE_INST end
ARRAY_LIST: (LISTNUM)
LISTNUM : NUM ListNUM_aux
List_num_aux : virg num|eps
LISTNUM : NUM ListNUM_aux
List_num_aux : virg num listnumaux|eps
INSTR : for IDF inumber .. inumber loop LISTE_INST endLoop|put_line();
IFINSTAUX:END IF;|ELSE LIST_INST END IF ;
COND :IDF = ADDSUB
AFFECTATION :IDF := ADDSUB;
MULTDIV : AUX MULTDIVAUX
MULTDIVAUX : *  MULTDIV
		| /  MULTDIV
		| epsilon
ADDSUB : MULTDIV ADDSUBAUX
ADDSUBAUX : –  ADDSUB
           | +  ADDSUB
           | epsilon
AUX : inumber | dnumber
     | ( ADDSUB )
INST : if COND then LIST_INST IF_INSTAU|AFFECTATION|PRINT|for IDF inumber .. inumber loop LISTE_INST endLoop|put_line();
LIST_INST : INST LIST_INSTAUX 
LISTE_INSTAUX : LISTE_INST | epsilon*/

typetoken _lire_token(){
	if (follow_token){
		follow_token = false;
		return token;
	}
	else{
		return (typetoken) yylex();
	}
}





/*int main(int argc , char** argv ){

	token = _lire_token();
	
	
	if (_prog() == true){
		
		printf(" successful operation\n");
		
	}
	else {
		
		printf(" operation failed\n");
	}
	afficherTS();
	afficher_erreurs();
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	afficher_sx_erreurs();
	/*
	if (_decl()==true){
		printf("successful operation\n");
	}
	else {
		printf("operation failed\n");
	}
	
	
}
*/

int main(){
	token = _lire_token();
	if (_prog() == true) {
		if (debug) ("0 erreurs syntaxiques\n");

		if (nombre_sm_erreurs() == 0){
			 {if (semanticerror == true)  printf("BUGG 0 semantic error BUT semanticerror == true !!\n");}
			if (debug) printf("0 erreurs sémantiques\n");
			if (debug) afficherTS();

		}else{
			if (debug) afficherTS();
			printf("%d erreurs sémantiques\n", nombre_sm_erreurs());
			afficher_sm_erreurs();
		}
	}
	else {
		 printf("%d erreurs syntaxiques\n", nombre_sx_erreurs());
		if (nombre_sx_erreurs() == 0) creer_sx_erreur(NonCategorized, tokenattribute.line);
	         else{ printf("erreurs syntaxiques :\n");afficher_sx_erreurs();}
		
		//afficher_erreurs();  // toutes les erreurs syntaxiques ne sont pas catégorisées et stockées
		if (debug) afficherTS();
			
		//printf("%d erreurs sémantiques\n", nombre_sm_erreurs());
		//if (nombre_sm_erreurs()> 0) afficher_sm_erreurs();
	}
}

//TYPE = INTEGER|STRING|FLOAT|CHAR|BOOL|NATURAL|POSITIVE|IDF|CONSTANT

boolean _type(){
	
	boolean result;
	 
	if (token == INTEGER){
		typeattribute.typename = Integer;
		result = true;
	}
	
	else if (token == STRING){
		typeattribute.typename = String;
		result = true;
	}
	
	else if (token == FLOAT){
		typeattribute.typename = Float;
		result = true;
	}
	
	else if (token == CHAR){
		typeattribute.typename = Char;
		result = true;
	}
	
	else if (token == BOOL){
		typeattribute.typename = Bool;
		result = true;
	}
	
	else if (token == NATURAL){
		typeattribute.typename = Natural;
		result = true;
	}
	
	else if (token == POSITIVE){
		typeattribute.typename = Positive;
		result = true;
	}
	
	else if (token == CONSTANT){
		typeattribute.typename = Constant;
		result = true;
	}
	else {
		creer_sx_erreur(TypeExpected, tokenattribute.line);
		result = false;
	}
	
	return result;
	
}

//CONST = DNUMBER|INUMBER|TRUE|FALSE 

boolean _const(){
	
	boolean result;
	
	if(token == DNUMBER){
		constattribute.typename = Float;
		result=true;
	}
	
	else if(token == INUMBER){
		constattribute.typename = Integer;
		result=true;
	}
	
	else if(token == TRUE){
		constattribute.typename = Bool;
		result=true;
	}
	
	else if(token == FALSE){
		constattribute.typename = Bool;
		result=true;
	}
	
	else {
		creer_sx_erreur(ConstExpected, tokenattribute.line);
		result = false;
	}
	
	return result;
	
}
//CONSTAUX = CONST|ARRAY
boolean _constaux(){
	
	boolean result;
	if(_const()){
		result=true;
	}
	else if(_array()){
		result=true;
	}
	else{
		creer_sx_erreur(ConstExpected, tokenattribute.line);
		result=false;
	}
	return result;
}
//DECL_AUX = := CONSTAUX PVIRG | PVIRG
//CONSTAUX = CONST|ARRAY
boolean _decl_aux(){
	boolean result;
	
	if (token == AFFECTATION){
		//printf(" affectation(:=) detected \n");
		token = _lire_token();
		
		if (_constaux()==true){
			//printf(" const detected\n");
			token = _lire_token();
			if(token == PVIRG){
				varattribute.initialisation = true;
				result = true;
			}
			else{
				creer_sx_erreur(PvirgExpected, tokenattribute.line);
				if(debug)printf("error ;");
				result = false;
			}
		}
		else {
			creer_sx_erreur(ConstExpected, tokenattribute.line);
			if(debug)printf(" const NOT detected\n");
			result = false;
			}
	
	}
	else if (token==PVIRG){
		varattribute.initialisation = false;	
		//printf(" fin_PVIRG detected\n");
		result = true;
	}
	else{
		creer_sx_erreur(PvirgExpected, tokenattribute.line);
		//printf(" erreur_decl_aux detected\n");
		result = false;
	}
	
	return result;
}



//DECL = IDF : TYPE DECL_AUX|

boolean _decl(){
	
	boolean result = false ;
	
	if (token == IDF){
		//printf(" IDF detected \n");
		token = _lire_token();
		
		if (token == GTYPE){
			//printf(" GTYPE(:) detected \n");
			token = _lire_token();
			
			if (_type() == true){
				//printf(" type detected \n");
				token = _lire_token();
				
				if (_decl_aux() == true){
					//printf("#############################################################");
					if (inTS(varattribute.name, &rangvar) == true) {
						//printf(" variable already declared \n");
						semanticerror = true;
						creer_sm_erreur(AlreadyDeclared, varattribute.line, varattribute.name);
					}
					else{
						//printf(" nouvelle variable \n");
						varvalueType newvar;
						newvar.nbdecl = 1;
						newvar.name = (char *)malloc(sizeof(char)*strlen(varattribute.name)+1);
						strcpy(newvar.name, varattribute.name);
						if (debug) printf("VAR{%s}-->NEW{%s}",varattribute.name, newvar.name);
						newvar.line = varattribute.line;
						newvar.initialisation = varattribute.initialisation; // l'initialisation est marquée par decl_aux dans varattribute
						newvar.utilisation = false; //toute variable est par défaut non utilisee
						newvar.typevar = typeattribute.typename;
						switch(newvar.typevar){
							//printf(" dans le switch \n");
							case String : setsvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?stringattribute.value:"")); break;
							case Char : setsvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?stringattribute.value:"")); break;
							case Float : setdvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?constattribute.valinit:0.0)); break;
							case Integer : setdvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?constattribute.valinit:0)); break;
							case Natural : setdvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?constattribute.valinit:0)); break;
							case Constant : setdvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?constattribute.valinit:(0))); break;

							default : setdvalue(&(newvar.valinit) , ((varattribute.initialisation == true)?constattribute.valinit:0.0)); break;
						}
						ajouter_nouvelle_variable_a_TS(newvar);
					}
					
					// 6eme gestion erreur BadlyInitialised : l'IDF peut avoir été initialisé par une constante du mauvais type
					if (varattribute.initialisation == true){
						//printf("analyse the constant /n");
						if (constattribute.typename != typeattribute.typename){ //Int/Double|String, Double/Int|String, Double/Bool|String, Bool/Double|String, Int/Bool|String, Bool/Int|String, //String|Int/Double, String/Double|Int, String/Double|Bool, String/Bool|Double, String/Int|Bool, String/Bool|Int,
							if ( (typeattribute.typename != Float) || (constattribute.typename != Integer) ){  // ce n'est pas Double := Integer
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							//sinon (i.e Double := Int) alors il y a un casting implicit Double = (Double) Int ;-)
							else if ( (typeattribute.typename != Bool) || (constattribute.typename != Integer) ){  // ce n'est pas Bool := Integer
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							
							else if ( (typeattribute.typename != Integer) || (constattribute.typename != Bool) ){  // ce n'est pas Integer := bool
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							else if ( (typeattribute.typename != Float) || (constattribute.typename != Bool) ){  // ce n'est pas Double := bool
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							else if ( (typeattribute.typename != Bool) || (constattribute.typename != Float) ){  // ce n'est pas Bool := Double
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							else if ( (typeattribute.typename != String) || (constattribute.typename != Integer) ){  // ce n'est pas String := Integer
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							else if ( (typeattribute.typename != String) || (constattribute.typename != Bool) ){  // ce n'est pas String := Bool
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
							else if ( (typeattribute.typename != String) || (constattribute.typename != Float) ){  // ce n'est pas String := Bool
								semanticerror = true;
								creer_sm_erreur(BadlyInitialised, varattribute.line, varattribute.name);
							}
						}
					}
					//printf(" result = true \n");
					result = true;


				}
				
			}else {	creer_sx_erreur(TypeExpected, tokenattribute.line);result=false;;result=false;}
				
		}else {
			creer_sx_erreur(ToExpected, tokenattribute.line);result=false;}
		
	}else {
		//printf(" IDF NOT detected \n");
		creer_sx_erreur(IdfExpected, tokenattribute.line);
		result=false;
	}
		
	return result;	
	
}

// LISTE_DECL = DECL LISTE_DECL_AUX 

boolean _liste_decl(){
	boolean result;
	if (_decl()){
		//printf("___________________________________\n");
		token = _lire_token();
		if (_liste_decl_aux()){
			result = true;
		}
		else {
			result = false;
		}
	}
	else {
		result = false;
	}
	
	return result;
}


//LISTE_DECL_AUX = LISTE_DECL | EPS
boolean _liste_decl_aux(){
	boolean result;
	
	if (token==BEG_IN){
		follow_token = true;
		result = true;
	}
	else if (_liste_decl()){
		result = true;
	}
	else {
		result = false;
	}
	
	return result;
	
}

//PROG : LISTE_DECL begin LISTE_INST end
boolean _prog(){
	boolean result;
	
	if (_liste_decl()){
		token = _lire_token();
		if (token == BEG_IN){
			//printf(" BEGIN detected \n");
			token = _lire_token();
			if (_liste_inst()){
				token = _lire_token();
				if (token == END){
				//	printf(" END detected \n");
					token = _lire_token();
					if (token == PVIRG){
						//printf(" fin_inst detected \n");
						result = true;
					}
					else {creer_sx_erreur(PvirgExpected, tokenattribute.line);result = false;}
				}
				else {
					creer_sx_erreur(EndExpected, tokenattribute.line);
					result = false;
				}
			}
			else {result = false;}
		}
		else {
			creer_sx_erreur(BeginExpected, tokenattribute.line);
			result = false;
		}
	}
	else {
		result = false;
	}
	
	return result;
}


//ARRAY_LIST: (LISTNUM)
//LISTNUM : NUM ListNUM_aux
//List_num_aux : virg num|eps


boolean _array(){
	boolean result;
	
	if(token == POPEN){
		token=_lire_token();
		if(_listenum()){
			token=_lire_token();			
			if(token == PCLOSE){
				result = true ;
			}
			else{
				creer_sx_erreur(PcloseExpected, tokenattribute.line);
				if(debug)printf("error pclose\n");
				result = false;
			}
		}
		else{
			//printf("error _listenum\n");
			result = false;
		}
	}
	else{
		creer_sx_erreur(PopenExpected, tokenattribute.line);
		if(debug)printf("error popen\n");
		result = false;
	}
	return result;
}
//LISTNUM : NUM ListNUM_aux
//List_num_aux : virg num listnumaux|eps
boolean _listenum(){
	boolean result;
	if((token == DNUMBER) || (token == INUMBER)){
		token = _lire_token();
		if(_listnum_aux()){
			result = true;
		}
		else{
			creer_sx_erreur(VirgExpected, tokenattribute.line);
			result = false;
		}
	}
	else{
		creer_sx_erreur(inumberordnumberExpected, tokenattribute.line);
		if(debug)printf("error les num");
		result = false;
	}
		
return result;
}
//List_num_aux : virg num listnumaux|eps
boolean _listnum_aux(){
	boolean result;
	if(token == VIRG){
		token = _lire_token();
		if((token == DNUMBER) || (token == INUMBER)){
			token = _lire_token();
			if(_listnum_aux()){
				
				result = true;
			}
			else{
				result = false;
			}
		}
		else{
			creer_sx_erreur(inumberordnumberExpected, tokenattribute.line);
			result = false;
		}
	}
	else if(token == PCLOSE){
		follow_token = true;
		result = true;
	}
	else{
		result = false;
	}
return result;
}


//  INSTR : for IDF inumber .. inumber loop LISTE_INST endLoop|put_line();
boolean _instr(){

	boolean detectTirets = true;
	boolean result=false;
	//printf("dans instr");
	if (token == LOOPFOR){
		//printf(" FOR detected \n");
		token = _lire_token();
		
		if (token == IDF){
			boolean leftexpnotdeclaredsemanticerror = false;
			if (inTS(varattribute.name, &localrangvar) == false) {
					semanticerror = true ;
					leftexpnotdeclaredsemanticerror = true;
					creer_sm_erreur(NotDeclared, varattribute.line, varattribute.name);
			} else if (typevar(localrangvar) != Integer) {
					semanticerror = true ;
					// 2eme gestion erreur IncompatibleAssignType : l'affectation peut être mal typée
					creer_sm_erreur(IncompatibleForIndexType, varattribute.line, varattribute.name);
			} 
			//printf(" IDF detected \n");
			token = _lire_token();
			
			if (token == IN){
				//printf(" in detected \n");
				token = _lire_token();
				
				if (token == INUMBER){
					//printf(" INUMBER detected \n");
					token = _lire_token();
					
					if (token == BETWEEN){
						//printf(" .. detected \n");
						token = _lire_token();
						
						if (token == INUMBER){
						//	printf(" INUMBER detected \n");
							token = _lire_token();
							
							if (token == LOOP){
							//	printf(" loop detected \n");
								token = _lire_token();
								
								if (_liste_inst()){
									token = _lire_token();
									
									if (token == END){
							//			printf(" END detected \n");
										token = _lire_token();
										
										if (token == LOOP){
							//				printf(" Loop detected \n");
											token = _lire_token();
											
											if (token == PVIRG){
							//					printf(" fin_inst detected \n");
												result = true;
												
											}
											else {
												creer_sx_erreur(PvirgExpected, tokenattribute.line);
												result = false;
											}
										}
										else {
											creer_sx_erreur(EndforExpected, tokenattribute.line);
											result = false;
										}
									}
									else {
										creer_sx_erreur(EndforExpected, tokenattribute.line);	
										result = false;
									}
								}
								else {
									
									result = false;
								}
							}
							else {
								creer_sx_erreur(LoopExpected, tokenattribute.line);
								result = false;
							}
						}
						else {
							creer_sx_erreur(InumberExpected, tokenattribute.line);
							result = false;
						}
					}
					else {	
						creer_sx_erreur(ToExpected, tokenattribute.line);
						result = false;
					}
				}
				else {
					creer_sx_erreur(InumberExpected, tokenattribute.line);
					result = false;
				}
			}
			else {
				creer_sx_erreur(InExpected, tokenattribute.line);
				result = false;
			}
		}
		else {
			creer_sx_erreur(IdfExpected, tokenattribute.line);
			result = false;
		}
	}
	else if (token == PUTLINE){
	//	printf(" Put_Line detected \n");
		token = _lire_token();
		if (token == POPEN){
	//		printf(" ( detected \n");
			token = _lire_token();
			if (token == TIRETS){    // detection des tirets
	//			printf(" tirets detected \n");
				token = _lire_token();
				while(token != TIRETS){  // boucle pour ecrire n'importe quoi sauf ; et " (je vais la régler bientot, car il faut faire /" sdaa3 rass....)
					token = _lire_token();
					if (token == PVIRG){
						detectTirets = false;
						result = false;
						break; // arreter si on detecte ; avant ")
					}
				}
				if (detectTirets){ // condition pour savoir si on est sorti de while en detectant ; ou bien "
					token = _lire_token();
					if (token == PCLOSE){
						//printf(" ) detected \n");
						token = _lire_token();
						if (token == PVIRG){
						//	printf(" fin_inst detected \n");
							result = true;
						}
						else {
							creer_sx_erreur(PvirgExpected, tokenattribute.line);
							result = false;
						}
					}
					else {
						creer_sx_erreur(PcloseExpected, tokenattribute.line);
						result = false;
					}
				}
			}
			
		}
		else {
			creer_sx_erreur(PopenExpected, tokenattribute.line);
			result = false;
		}
	}
	
	else {
		result = false;
	}
	
	return result;
	
}	

//IFINSTAUX:END IF;|ELSE LIST_INST END IF ;
//COND :IDF = ADDSUB
boolean _condition(){
	varvalueType localvarattribute;
	boolean result ;
	token= _lire_token();
	boolean leftexpnotdeclaredsemanticerror = false;
	if(token==IDF){
		localvarattribute = varattribute;
		if (inTS(localvarattribute.name, &localrangvar) == false){
			semanticerror = true;		
			leftexpnotdeclaredsemanticerror = true;
			//(leftexpnotdeclaredsemanticerror == true) ==> semanticerror = true) (mais pas l'inverse)
			creer_sm_erreur(NotDeclared, localvarattribute.line, localvarattribute.name);
		}
		token=_lire_token();
		if(token==EGAL){
			token=_lire_token();
			if(_addsub()){
				result=true;
			}
		}
		else{
			creer_sx_erreur(EqeqExpected, tokenattribute.line);
			result = false;
		}
	}
	else{
		creer_sx_erreur(IdfExpected, tokenattribute.line);
		result = false;
	}
	return result;
}

//AFFECTATION :IDF := ADDSUB;
boolean _affectation(){
	boolean result ;
	if(token==IDF){
		token=_lire_token();
			if(token == AFFECTATION){
				token=_lire_token();
				if(_addsub()){
					token = _lire_token();
					if(token == PVIRG){
					//printf("PVIRG in affectation\n");
					result=true;
					}
					else{
						creer_sx_erreur(PvirgExpected, tokenattribute.line);
						result = false;
					}
				}
				else{
					//printf("error addsub affect\n");
					result=false;
				}
			}
			else{
				creer_sx_erreur(AffExpected, tokenattribute.line);
				result=false;
			}	
	}
	else{
		result = false;
	//	printf("error _affectation\n");
	}
	return result;
}

//MULTDIV : AUX MULTDIVAUX

boolean _multdiv(){
	boolean result = false;

	if(_aux()){
		if(_multdivaux()){
			result=true;
		}
		else{
			result = false;
	//		printf("error MULTDIVAUX");
		}
	}
	else{
		result = false;
	//	printf("error aux");
	}
	
	return result;
}




//MULTDIVAUX : *  MULTDIV
//		| /  MULTDIV
//		| epsilon
boolean _multdivaux(){
			boolean result = false;
			token = _lire_token();
			if (token == THEN|token == PVIRG|token == PLUS|token == MINUS
				){
				follow_token = true;
				result = true;
			}
			
			else if(token == DIV){
					token = _lire_token();
					if(_multdiv()){
						result = true;
					}
					else{
						result=false;
	//					printf("error MULTDIVAUX\n");
					}
			}
			else if(token == MULT){
					token = _lire_token();
					if(_multdiv()){
						result = true;
					}
					else{
						result=false;
	//					printf("error MULTDIVAUX\n");
					}
			}
			else{
				result = false;
			}

			return result;
}

//ADDSUB : MULTDIV ADDSUBAUX
boolean _addsub(){
	boolean result;

	if(_multdiv()){
		token = _lire_token();
		if(_addsubaux()){
			result=true;
		}
		else{
		result = false;
	//	printf("error ADDSUBAUX");
		}
	}
	else{
		result = false;
	//	printf("error multdiv");
	}
return result;
}
//ADDSUBAUX : –  ADDSUB
//           | +  ADDSUB
//           | epsilon



boolean _addsubaux(){
	boolean result = false;
	if(token == MINUS){
		token= _lire_token();
			if(_addsub()){
				result = true;
			}
			else{
				result=false;
	//			printf("error ADDSUB\n");
			}
	}
	else if(token == PLUS ){
			token= _lire_token();
			if(_addsub()){
				result = true;
			}
			else{
				result=false;
	//			printf("error ADDSUB\n");
			}
	}
	else if (token == THEN |token==PVIRG){
		follow_token = true;
		result = true;
	}
	else{
		result = false;
	}

	return result;
}
//AUX : inumber | dnumber
//     | ( ADDSUB )

boolean _aux(){
	boolean result;
	if(token == IDF){
// 7eme gestion erreur NotDeclared : l'IDF peut ne pas avoir été déclaré
		if (inTS(varattribute.name, &rangvar) == false) {
			semanticerror = true;
			creer_sm_erreur(NotDeclared, varattribute.line, varattribute.name);
		
		// 8eme gestion erreur IncompatibleOperationType : l'IDF peut avoir été déclaré d'un type non entier ni double
		}else if ( (typevar(rangvar) != Integer) && (typevar(rangvar) != Float)&& (typevar(rangvar) != Natural)&& (typevar(rangvar) != Positive) ) { // (si l'IDF est un Bool) ou string ou 
			semanticerror = true;
			creer_sm_erreur(IncompatibleOperationType, varattribute.line, varattribute.name);
		}else if (est_definie(rangvar) == false){
			semanticerror = true;
			creer_sm_erreur(NotInitialized, varattribute.line, varattribute.name);		
			// l'IDF est Int ou Double mais n'est pas définie (permet de ne pas bloquer la machinerie de l'analyseur sémantique) 
		}
		result = true;
	}
	else if(token == INUMBER){
		result = true;
	}
	else if(token == DNUMBER){
		result = true;
	}
	else if(token == POPEN){
		token = _lire_token();
		if(_addsub()){
			token = _lire_token();
			if(token ==PCLOSE){
				result= true;
			}
		}
	}
	else{
		result = false;
	}
	return result;
}
boolean _if_insteaux(){
	boolean result = false;
	if(token == END){
		token = _lire_token();
		if(token == IF){
			token = _lire_token();
			if(token == PVIRG){
				result = true;
			}
			else{
				creer_sx_erreur(PvirgExpected, tokenattribute.line);
				result = false;
			}
		}
		else{
			creer_sx_erreur(EndiforelseExpected, tokenattribute.line);
			result = false;
		}
	}
	else if(token == ELSE){
		token = _lire_token();
		if(_liste_inst()){
			token = _lire_token();
			if(token == END){
				token = _lire_token();
				if(token == IF){
					token = _lire_token();
					if(token == PVIRG){
						result = true;
					}
					else{
						creer_sx_erreur(PvirgExpected, tokenattribute.line);
						result = false;
					}
				}
				else{
					creer_sx_erreur(EndifExpected, tokenattribute.line);					
					result = false;
				}
			}
		}
	}
return result;

}

//INST : if COND then LIST_INST IF_INSTAU|AFFECTATION|PRINT|for IDF inumber .. inumber loop LISTE_INST endLoop|put_line();
boolean _inst(){
	boolean result = false;
//	token = _lire_token();
	if (token == IF) {
		if (_condition()) {
			//printf("cond");
			token = _lire_token();
			if (token == THEN) {
			//	printf("then");
				token = _lire_token();
				if (_liste_inst()) {
					token = _lire_token();
  					 if (_if_insteaux()) {
	    					result = true;
	    				}
	    				else{
	    	//				printf("error _if_insteaux()");
	    					result = false;
	    				}
	    			}
	    			else{
	    	//			printf("error _list_insteaux");
	    				result = false;
	    			}
	    		}
	    		else{
				creer_sx_erreur(ThenExpected, tokenattribute.line);
	    	//		printf("error THEN");
	    			result = false;
	    		}
	 	}
	    	else{
	    	//	printf(" error _condition");
	    		result = false;
	    	}
	}   
	else if(_instr()){
		result = true;
	}
	else if(_affectation()){
		result =true;	
	}

	else { creer_sx_erreur(InstructionExpected, tokenattribute.line);result =false;}
return result;

}

//LIST_INST : INST LIST_INSTAUX 

boolean _liste_inst(){
	boolean result = false;
	if(_inst()){
	//printf("- - - - - - - - - - - - - - - - - - - - - - - - \n");
		token = _lire_token();
		if(_liste_inst_aux()){
			result = true;
		}
		else{
			result = false;
		}
	}
	else{
		result =false;
	}
return result;
}

//LISTE_INSTAUX : LISTE_INST | epsilon
boolean _liste_inst_aux(){
	boolean result;
	
	if (token == END){
		
		follow_token = true;
		result = true;
	}
	else if (token == ELSE){
		follow_token = true;
		result = true;
	}
	
	else if (_liste_inst()){
		result = true;
	}
	
	else {
		result = false;
	}
	
	return result;
	
}



void set_idf_attributes(char *name, int line){
	varattribute.name = (char *)malloc(sizeof(char) * strlen(name)+1);
	strcpy(varattribute.name, name);
	varattribute.line = line;
}

void set_number_attributes(double value){
	constattribute.valinit = value;
}
void set_token_attributes(int line){
	tokenattribute.line = line;
}

