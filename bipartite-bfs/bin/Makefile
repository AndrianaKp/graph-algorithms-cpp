LEDALIB  = /usr/local/LEDA
LEDAINCL = /usr/local/LEDA/incl

compile:
	g++ -std=c++0x ../src/main.cpp ../src/bfs.cpp ../src/bipartite.cpp ../src/graphs.cpp ../src/experiments.cpp  -o main \
	-O3 -I $(LEDAINCL) -I ../incl \
	-L $(LEDALIB) -lleda -lX11 -lm

run:
	./main

clean:
	rm -f main
