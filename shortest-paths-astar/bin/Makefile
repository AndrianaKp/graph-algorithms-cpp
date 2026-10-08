LEDALIB = '/usr/local/LEDA'
LEDAINCL = '/usr/local/LEDA/incl'
INCL = '../incl'

compile: main.o dijkstra-sp.o a_star.o graph_generator.o experiments.o bonus.o
	g++ -O3 -Wall -std=c++0x -o dijkstra_a_star main.o dijkstra-sp.o a_star.o graph_generator.o experiments.o bonus.o -lleda -L$(LEDALIB) -fno-strict-aliasing

dijkstra-sp.o: ../src/dijkstra-sp.cpp ../incl/dijkstra-sp.hpp ../incl/graph.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/dijkstra-sp.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing

a_star.o: ../src/a_star.cpp ../incl/a_star.hpp ../incl/graph.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/a_star.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing

graph_generator.o: ../src/graph_generator.cpp ../incl/graph_generator.hpp ../incl/graph.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/graph_generator.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing

main.o: ../src/main.cpp ../incl/dijkstra-sp.hpp ../incl/a_star.hpp ../incl/graph_generator.hpp ../incl/graph.hpp ../incl/experiments.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/main.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing

run:
	./dijkstra_a_star

clean:
	rm -rf *.o dijkstra_a_star

experiments.o: ../src/experiments.cpp ../incl/experiments.hpp ../incl/graph.hpp ../incl/dijkstra-sp.hpp ../incl/a_star.hpp ../incl/graph_generator.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/experiments.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing

bonus.o: ../src/bonus.cpp ../incl/bonus.hpp ../incl/graph.hpp
	g++ -O3 -Wall -std=c++0x -c ../src/bonus.cpp -I $(INCL) -I $(LEDAINCL) -fno-strict-aliasing
