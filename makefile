make : project2.exe
	./project2.exe

project2.exe : main.o
	g++ main.o -o project2.exe
	
main.o : main.cpp
	g++ -Wall -c main.cpp
	
clean : 
	rm *.o project2.exe