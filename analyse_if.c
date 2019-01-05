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

	//token = _lire_token();
	
	
	if (_inst() == true){
		
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



//TYPE = INTEGER|STRING|FLOAT|CHAR|BOOL|NATURAL|POSITIVE|IDF|CONSTANT

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
	
	else if (token == CONSTANT){
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
//DECL_AUX = := CONSTAUX PVIRG | PVIRG
//CONSTAUX = CONST|ARRAY
boolean _decl_aux(){
	boolean result;
	
	if (token == AFFECTATION){
		printf(" affectation(:=) detected \n");
		token = _lire_token();
		
		if (_constaux()==true){
			printf(" const detected\n");
			token = _lire_token();
			if(token == PVIRG){
				result = true;
			}
			else{
				printf("error ;");
				result = false;
			}
		}
		else {
			printf(" const NOT detected\n");
			result = false;
			}
	
	}
	else if (token==PVIRG){
		printf(" fin_PVIRG detected\n");
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
		
	}
	else if(_inst()){					//implementation de if_statement
		result = true;
	}
	else {printf(" IDF NOT detected \n");}
		
	return result;	
	
}

// LISTE_DECL = DECL LISTE_DECL_AUX 

boolean _liste_decl(){
	boolean result;
	if (_decl()){
		printf("jjh___________________________________\n");
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
			token=_lire_token();			
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
			result = false;
		}
	}
	else{
		printf("error popen\n");
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
			printf("error f l virg");
			result = false;
		}
	}
	else{
		printf("error f nmari");
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
				printf("erro hvcbsnxkr\n");
				result = false;
			}
		}
		else{
			printf("error f nemra li mor l virg");
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




/*
//OPER :
//COND :IDF = OPER
//(IF_STAT : if COND then LIST_INST IF_INSTAU) 
//INST : (IF_STAT)if COND then LIST_INST IF_INSTAU 
		|AFFECTATION|PRINT
//LIST_INST : INST LIST_INSTAUX 
//LIST_INSTAUX : LIST_INST | EPS
//IFINSTAUX:END IF;|ELSE LIST_INST END IF ;
*/
//boolean _condition();
//boolean _instement();
//boolean _else_instement();
//boolean _else_statement();
//boolean oper();
//boolean _inst();
//boolean if_insteaux();
//boolean inst();
//boolean _liste_inst();

//IFINSTAUX:END IF;|ELSE LIST_INST END IF ;
//COND :IDF = OPER
boolean _condition(){
	boolean result = true;
	token= _lire_token();
	if(token==IDF){
		//token=_lire_token();
		//if(token==EGAL){
			//if(_oper()){
				result=true;
			//}
		//}
	}
	else{
		result = false;
	}
	return result;
}


//OPER :

boolean _oper(){
	boolean result = true;
	return result;
}

boolean _print(){
	boolean result = true;
	return result;
}


boolean _affectation(){
	boolean result = true;
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
				printf("rak nssiti ;");
				result = false;
			}
		}
		else{
			printf("error if lool");
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
						printf("rak nssiti ;");
						result = false;
					}
				}
				else{
					printf("error if lilili");
					result = false;
				}
			}
		}
	}
return result;

}

//INST : if COND then LIST_INST IF_INSTAU|AFFECTATION|PRINT
boolean _inst(){
	boolean result = false;
	token = _lire_token();
	if (token == IF) {
		if (_condition()) {
			token = _lire_token();
			if (token == THEN) {
				if (_liste_inst()) {
  					 if (_if_insteaux()) {
	    				result = true;
	    			}
	    			else{
	    				printf("error _if_insteaux()");
	    				result = false;
	    			}
	    		}
	    		else{
	    			printf("error _list_insteaux");
	    			result = false;
	    		}
	    	}
	    	else{
	    		printf("error THEN");
	    		result = false;
	    	}
	    }
	    else{
	    	printf(" error _condition");
	    	result = false;
	    }
	}   
	//else if(_affectation()){
	//	result = true;
	//}
	//else if(_print()){
		//result = true;
	//}
	else if(token == IDF){
		result = true;
	}
	else{
		result = false;
	}

return result;

}

//LIST_INST : INST LIST_INSTAUX 

boolean _liste_inst(){
	boolean result = false;
	if(_inst()){
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


