#include "cfg.h"
#include "tablesymb.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define debug false




// pré-requis : e.etype == DBL;
double dvalue(Element e){
	return e.evalue.dvalue;
}

// pré-requis : e.etype == STR;
char * svalue(Element e){
	return e.evalue.svalue;
}

void setdvalue(Element *e, double d){
	e->evalue.dvalue = d;
	e->etype = DBL;
}

void setsvalue(Element *e, char * s){
	if (debug) printf("setsvalue()\n");
	if ((debug) && (s == NULL)) printf("s NULL!!!!!!!\n"); 
	e->evalue.svalue = (char *)malloc((strlen(s)+1)*sizeof(char));
	strcpy(e->evalue.svalue, s);
	e->etype = STR;
	if (debug) printf("out of setsvalue()\n");
}

