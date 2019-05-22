# Sesión 12. Semana 20 de Mayo
pruebaSecuencial: pruebaDispersion.c dispersion.o
	gcc -g pruebaDispersion.c dispersion.o -o pruebaDispersion

dispersion.o: dispersion.c dispersion.h
	gcc -g -c dispersion.c 
clean:
	rm *.o
