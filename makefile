all: main.o linkedList.o conversion.o errorCheck.o firstIteration.o macro.o opData.o secondIteration.o
	gcc -ansi -Wall -g main.o conversion.o errorCheck.o firstIteration.o macro.o linkedList.o opData.o secondIteration.o -o all

opData.o: opData.c
	gcc -c -Wall -ansi -pedantic opData.c -o opData.o

linkedList.o: linkedList.c
	gcc -c -Wall -ansi -pedantic linkedList.c -o linkedList.o

conversion.o: conversion.c conversion.h
	gcc -c -Wall -ansi -pedantic conversion.c -o conversion.o

macro.o: macro.c macro.h
	gcc -c -Wall -ansi -pedantic macro.c -o macro.o

errorCheck.o: errorCheck.c errorCheck.h
	gcc -c -Wall -ansi -pedantic errorCheck.c -o errorCheck.o

firstIteration.o: firstIteration.c firstIteration.h
	gcc -c -Wall -ansi -pedantic firstIteration.c -o firstIteration.o

secondIteration.o: secondIteration.c secondIteration.h
	gcc -c -Wall -ansi -pedantic secondIteration.c -o secondIteration.o

main.o: main.c main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

clean:
	rm *.o
