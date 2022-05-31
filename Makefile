CC1=g++


all:
	$(CC1) luserial.cpp -o luserial
	$(CC1) -fopenmp luomp.cpp -o luomp
	$(CC1) -pthread luthread.cpp -o luthread


