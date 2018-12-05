#include "analys.h"

#include<stdlib.h>

#include<stdio.h>

extern int yylex();

typetoken token;
boolean follow_token;

typetoken _lire_token(){
	if (follow_token){
		follow_token = false;
		return token;
	}
	else{
		return (typetoken) yylex();
	}
}





int main(int argc , char** argv ){

	token = _lire_token();
	
	
	if (_prog() == true){
		
		printf(" successful operation\n");
		
	}
	else {
		
		printf(" operation failed\n");
	}
	
	
	/*
	if (_decl()==true){
		printf("successful operation\n");
	}
	else {
		printf("operation failed\n");
	}
	*/
	
}



//TYPE = INTEGER|STRING|FLOAT|CHAR|BOOL|NATURAL|POSITIVE|IDF

boolean _type(){
	
	boolean result;
	
	if (token == IDF){
		result = true;
	}
	
	else if (token == INTEGER){
		result = true;
	}
	
	else if (token == STRING){
		result = true;
	}
	
	else if (token == FLOAT){
		result = true;
	}
	
	else if (token == CHAR){
		result = true;
	}
	
	else if (token == BOOL){
		result = true;
	}
	
	else if (token == NATURAL){
		result = true;
	}
	
	else if (token == POSITIVE){
		result = true;
	}
	
	else {
		result = false;
	}
	
	return result;
	
}

//CONST = DNUMBER|INUMBER|TRUE|FALSE 

boolean _const(){
	
	boolean result;
	
	if(token == DNUMBER){
		
		result=true;
	}
	
	else if(token == INUMBER){
		
		result=true;
	}
	
	else if(token == TRUE){
		
		result=true;
	}
	
	else if(token == FALSE){
		
		result=true;
	}
	
	else {
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
		result=false;
	}
	return result;
}
//DECL_AUX = := CONSTAUX | INST
//CONSTAUX = CONST|ARRAY
boolean _decl_aux(){
	boolean result;
	
	if (token == AFFECTATION){
		printf(" affectation(:=) detected \n");
		token = _lire_token();
		
		if (_constaux()==true){
			printf(" const detected\n");
			result = true;
			token = _lire_token();
			_decl_aux();
		
		}
		else {
			printf(" const NOT detected\n");
			result = false;
			}
	
	}
	else if (token==INST){
		printf(" fin_inst detected\n");
		result = true;
	}
	else{
		printf(" erreur_decl_aux detected\n");
		result = false;
	}
	
	return result;
}



//DECL = IDF : TYPE DECL_AUX|

boolean _decl(){
	
	boolean result = false ;
	
	if (token == IDF){
		printf(" IDF detected \n");
		token = _lire_token();
		
		if (token == GTYPE){
			printf(" GTYPE(:) detected \n");
			token = _lire_token();
			
			if (_type() == true){
				printf(" type detected \n");
				token = _lire_token();
				
				if (_decl_aux() == true){
					result = true;
				}
				
			}else {printf(" type NOT detected \n");}
				
		}else {printf(" GTYPE(:) NOT detected \n");}
		
	}else {printf(" IDF NOT detected \n");}
		
	return result;	
	
}

// LISTE_DECL = DECL LISTE_DECL_AUX 

boolean _liste_decl(){
	boolean result;
	if (_decl()){
		printf("___________________________________\n");
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



boolean _prog(){
	boolean result;
	
	if (_liste_decl()){
		token = _lire_token();
		if (token == BEG_IN){
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




//ARRAY_LIST: (LISTNUM)
//LISTNUM : NUM ListNUM_aux
//List_num_aux : virg num|eps


boolean _array(){
	boolean result;
	
	if(token == POPEN){
		token=_lire_token();
		if(_listenum()){
			if(token == PCLOSE){
				result = true ;
			}
			else{
				printf("error pclose\n");
				result = false;
			}
		}
		else{
			printf("error _listenum\n");
			result = true;
		}
	}
	else{
		printf("error popen\n");
		result = false;
	}
	return result;
}

boolean _listenum(){
	boolean result=true;
	
return result;
}


