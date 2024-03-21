all : Chaine.o SVGwriter.o ChaineMain.o 
	gcc Chaine.o SVGwriter.o ChaineMain.o -o ChaineMain -lm

Chaine.o: Chaine.c SVGwriter.h
	gcc -c Chaine.c -o Chaine.o -lm

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc -c SVGwriter.c -o SVGwriter.o

ChaineMain.o: ChaineMain.c Chaine.h SVGwriter.h 
	gcc -c ChaineMain.c -o ChaineMain.o -lm

clean :
	rm -f *.o
	rm -f main
	rm -f ChaineMain
	rm -f Chaine
	rm -f test
