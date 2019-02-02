#ifndef TABLE_SYMB_H
#define TABLE_SYMB_H

#include "cfg.h"


// constructeur d'une nouvelle variable
extern void ajouter_nouvelle_variable_a_TS(varvalueType newvar);

// select *
extern void afficherTS();

// prdicat de recherche
extern boolean inTS(char * varname, int* rangvar);  

extern void incrementer_nombre_declarations(int rangvar);

extern char* name(int rang);
extern Type typevar(int rang);
extern boolean est_definie(int rang);
extern boolean est_utilisee(int rang);

extern void definir(int rang);

extern int nombre_variables();

extern char * lowercase(char * s);

/* myitoa: convert n to characters in s */
extern char * myitoa(int);

/* reverse: reverse string s in place */
extern void reverse(char s[]);


extern Element value(char *idf);

extern Element valinit(int rang);

extern void set_svalinit(int rang, char *s);

extern void set_dvalinit(int rang, double s);

extern boolean est_definie(int rang);
#endif
