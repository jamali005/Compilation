#ifndef CFG_H
#define CFG_H

#define debug false
typedef enum {false=0, true=1} boolean;

typedef enum {DBL, STR} elementType;

typedef enum {Integer, Bool,Float,Char,Natural,Positive,Constant, String} Type;

typedef union{
	char * svalue;
	double dvalue;
} elementValue;


typedef struct Elt {
	elementType etype;
	elementValue evalue;
} Element;


typedef struct {
  int line;  //TOKEN.line
} tokenvalueType;


typedef struct {
  Type typename;    // TYPE.typename
} typevalueType;


typedef struct {
  Type typename;    // CONST_IB.typename
  double valinit;      // CONST_IB.valinit
} constvalueType;


typedef struct {
	char *value;
} stringvalueType;



typedef struct {
  char *name;      
  int  nbdecl;     
  Type typevar;    
  boolean initialisation; // attribut ncessaire  l'analyseur smantique 
  Element valinit;
  boolean utilisation;      
  int line; 
} varvalueType;

extern double dvalue(Element e);

// pr-requis : e.etype == STR;
extern char * svalue(Element e);

extern void setdvalue(Element *e, double d);

extern void setsvalue(Element *e, char * s);

#endif


