test_sisd: sisd.o service.o
	gcc -g -m32 service.o sisd.o -o test_sisd
service.o: service.c
	gcc -g -m32 -c -o service.o service.c -std=c99
sisd.o: sisd.s
	as -gdbb --32 -o sisd.o sisd.s

