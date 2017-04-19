file : main.o read.o write.o
		gcc -o file main.o read.o write.o
main.o : main.c
		gcc -c main.c
read.o : io.h read.c
		gcc -c read.c
write.o : io.h write.c
		gcc -c write.c

claen :
		rm -f file main.o read.o write.o

