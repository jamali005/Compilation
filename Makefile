lex : analys.h sc.l
	flex -i sc.l
	gcc -c lex.yy.c 


cfg : cfg.h tablesymb.h cfg.c
	gcc -c cfg.c

error : error.h analys.h error.c
	gcc -c error.c

tablesymb : cfg.h tablesymb.h tablesymb.c 
	gcc -c tablesymb.c





analyseur : cfg.h error.h analys.h tablesymb.h analys.c
	gcc -c analys.c

analyseurout :  lex cfg error tablesymb analys
	gcc -o spark cfg.o error.o tablesymb.o lex.yy.o analys.o

all : analyseurout 

clean :
	rm *.o
	rm *.yy.c


