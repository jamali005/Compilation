#ifndef ANALYS_H

#define ANALYS_H
#include"cfg.h"


typedef enum{
	
	COMMENTARY,
	PACKAGE,
	WITH,
	USE,
	PROCEDURE,
	IS,
	BEG_IN,
	END,
	INTEGER,
	STRING,
	FLOAT,
	CHAR,
	BOOL,
	NATURAL,
	POSITIVE,
	TRUE,
	FALSE,
	IDF,
	AFFECTATION,
	GTYPE,
	DNUMBER,
	INUMBER,
	POPEN,
	PCLOSE,
	VIRG,
	CONSTANT,
	PVIRG,
	LOOPFOR,
	IN,
	BETWEEN,
	LOOP,
	PUTLINE,
	IF,
	ELSE,
	THEN,
	//ELSEIF
	EGAL,
	TIRETS,
	PLUS,
	MINUS,
	MULT,
	DIV,CARA,
	ERRL

}typetoken;

/*

typedef enum{

false=0, true=1}boolean;

*/


typetoken _lire_token();
boolean _type();
boolean _const();
boolean _decl_aux();
boolean _decl();
boolean _liste_decl();
boolean _liste_decl_aux();
boolean _prog();
boolean _constaux();
boolean _array();
boolean _listenum();
boolean _listnum_aux();
boolean _liste_inst();
boolean _liste_inst_aux();
boolean _instr();
boolean _condition();
boolean _instement();
boolean _else_instement();
boolean _else_statement();
boolean oper();
boolean _inst();
boolean if_insteaux();
boolean inst();
boolean _liste_inst();
boolean _addsub();
boolean _multdivaux();
boolean _multdiv();
boolean _aux();
boolean _addsubaux();
boolean _affectation();

void set_idf_attributes(char *name, int line);
void set_number_attributes(double value);
void set_string_attributes(char * s);
void set_token_attributes(int line);



#endif
