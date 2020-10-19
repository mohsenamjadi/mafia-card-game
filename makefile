a.out: main.o functions.o
	g++   main.o functions.o
main.o: functions.h
	g++   -c main.cpp
functions.o: functions.cpp functions.h Room.h Player.h
	g++   -c functions.cpp
clean : 
	rm *.o a.out

