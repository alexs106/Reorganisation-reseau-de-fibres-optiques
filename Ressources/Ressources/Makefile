all : Chaine.o SVGwriter.o ChaineMain.o 
	gcc Chaine.o SVGwriter.o ChaineMain.o -o ChaineMain -lm

res : Chaine.o SVGwriter.o Reseau.o main2.o 
	gcc Chaine.o SVGwriter.o Reseau.o main2.o -o main2 -lm

hachage : Chaine.o SVGwriter.o Reseau.o Hachage.o mainH.o
	gcc Chaine.o SVGwriter.o Reseau.o Hachage.o mainH.o -o mainH -lm

Chaine.o: Chaine.c SVGwriter.h
	gcc -c Chaine.c -o Chaine.o -lm

Reseau.o: Reseau.c Chaine.h
	gcc -c Reseau.c -o Reseau.o

Hachage.o: Hachage.c Reseau.h Chaine.h
	gcc -c Hachage.c -o Hachage.o

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h 
	gcc -c ChaineMain.c -o ChaineMain.o -lm

main2.o : main2.c Reseau.h Chaine.h
	gcc -c main2.c -o main2.o 

mainH.o : mainH.c Hachage.h Reseau.h Chaine.h 
	gcc -c mainH.c -o mainH.o 

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c -o SVGwriter.o

clean :
	rm -f *.o
	rm -f *.html
	rm -f main
	rm -f ChaineMain
	rm -f Chaine
	rm -f test
	rm -f main2
	rm -f mainH 
