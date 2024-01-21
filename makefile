
all: clean compile link

link:
	g++ -o bin/All bin/main.o bin/WareHouse.o bin/Parse.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Parse.o src/Parse.cpp
clean:
	rm -f bin/*
