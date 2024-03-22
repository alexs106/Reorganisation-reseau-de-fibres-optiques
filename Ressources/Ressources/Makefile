all : Chaine.o SVGwriter.o ChaineMain.o 
	gcc Chaine.o SVGwriter.o ChaineMain.o -o ChaineMain -lm

res : Chaine.o SVGwriter.o Reseau.o main2.o 
	gcc Chaine.o SVGwriter.o Reseau.o main2.o -o main2 -lm

Chaine.o: Chaine.c SVGwriter.h
	gcc -c Chaine.c -o Chaine.o -lm

Reseau.o: Reseau.c Chaine.h
	gcc -c Reseau.c -o Reseau.o

main2.o : main2.c Reseau.h Chaine.h
	gcc -c main2.c -o main2.o 

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
	rm -f main2
