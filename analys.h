#ifndef ANALYS_H

#define ANALYS_H



typedef enum{
	INST,
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
	LOOPFOR,
	IN,
	BETWEEN,
	LOOP,
	PUTLINE,
	POPEN,
	PCLOSED

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
boolean _liste_inst();
boolean _liste_inst_aux();
boolean _instr();

#endif
