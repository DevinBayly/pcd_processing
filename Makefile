all: pts_reader.o main.o
	g++ -std=c++20 -O3 -o main main.o pts_reader.o

main.o: main.cpp
	g++ -std=c++20 -O3 -c main.cpp -o main.o

assoc.o: assoc.cpp
	g++ -std=c++20 -O3 -c assoc.cpp -o assoc.o



pts_reader.o: pts_reader.cpp
	g++ -std=c++20 -O3 -c pts_reader.cpp -o pts_reader.o

clean: 
	rm *.o