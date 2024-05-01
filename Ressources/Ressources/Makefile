CC = gcc
CFLAGS = -Wall -g -lm

CHAINE = Chaine.c ChaineMain.c SVGwriter.c 
OBJS_C = ${CHAINE:.c=.o}

RESEAU = Chaine.c SVGwriter.c Reseau.c main2.c
OBJS_R = ${RESEAU:.c=.o}

HACHAGE = Chaine.c SVGwriter.c Reseau.c Hachage.c mainH.c
OBJS_H = ${HACHAGE:.c=.o}

ARBREQ = Chaine.c SVGwriter.c Reseau.c ArbreQuat.c mainAQ.c
OBJS_A = ${ARBREQ:.c=.o}

RTR = Chaine.c SVGwriter.c Reseau.c ArbreQuat.c  Hachage.c ReconstitueReseau.c
OBJS_RTR = ${RTR:.c=.o}

TDC = Chaine.c SVGwriter.c Reseau.c ArbreQuat.c  Hachage.c temps_de_calcul.c
OBJS_TDC = ${TDC:.c=.o}

GRAPHE = Graphe.c SVGwriter.c Reseau.c Chaine.c mainG.c Struct_File.c ArbreQuat.c Hachage.c
OBJS_G = ${GRAPHE:.c=.o}

all : chaine res hachage arbrequat

chaine: ${OBJS_C}
	${CC} -o chaine ${CFLAGS} ${OBJS_C}

res: ${OBJS_R}
	${CC} -o res ${CFLAGS} ${OBJS_R}

hachage: ${OBJS_H}
	${CC} -o hachage ${CFLAGS} ${OBJS_H}

arbrequat: ${OBJS_A}
	${CC} -o arbrequat ${CFLAGS} ${OBJS_A}

ReconstitueReseau: ${OBJS_RTR}
	${CC} -o ReconstitueReseau ${CFLAGS} ${OBJS_RTR}

temps_de_calcul: ${TDC:.c=.o}
	${CC} -o temps_de_calcul ${CFLAGS} ${OBJS_TDC}

graphe: ${GRAPHE:.c=.o}
	${CC} -o graphe ${CFLAGS} ${OBJS_G}


.c.o:
	${CC} -c ${CFLAGS} $<


clean :
	rm -f *.o
	rm -f *.html
	rm -f ChaineMain
	rm -f hachage
	rm -f res
	rm -f chaine
	rm -f arbrequat
	rm -f main2
	rm -f mainH 
	rm -f mainAQ
	rm -f ReconstitueReseau
	rm -f temps_de_calcul
	rm -f graphe 

