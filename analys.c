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



boolean _decl_aux(){
	boolean result;
	
	if (token == AFFECTATION){
		printf(" affectation(:=) detected \n");
		token = _lire_token();
		
		if (_const()==true){
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


