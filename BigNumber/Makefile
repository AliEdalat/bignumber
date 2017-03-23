all: Bignum.o digit.o main.o
	g++ main.o Bignum.o digit.o
	./a.out
main.o: main.cpp
	g++ -c main.cpp
bignum.o: Bignum.cpp Bignum.h
	g++ -c Bignum.cpp
digit.o: digit.cpp digit.h
	g++ -c digit.cpp
