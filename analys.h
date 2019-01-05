#ifndef ANALYS_H

#define ANALYS_H



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
	IF,
	ELSE,
	THEN,
	//ELSEIF
	EGAL,
	ERRL

}typetoken;



typedef enum{

false=0, true=1}boolean;




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
boolean _condition();
boolean _oper();
boolean _if_stat();
boolean _if_insteaux();
boolean _inst();
boolean _liste_inst();
boolean _liste_inst_aux();
boolean _print();
boolean _affectation();
#endif
