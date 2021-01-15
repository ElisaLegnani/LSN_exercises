CC = g++
CFLAGS = -Wall -O3 --std=c++11

MolDyn_NVE.exe : MolDyn_NVE.o
	$(CC) MolDyn_NVE.o -o MolDyn_NVE.exe

MolDyn_NVE.o : MolDyn_NVE.cpp
	$(CC) -c MolDyn_NVE.cpp -o MolDyn_NVE.o $(CFLAGS)

clean :
	rm *.o old.0 old.final config.final

clean.sim :
	bash clean.sh
	rm *.o old.0 old.final config.final