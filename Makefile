make:
	g++ src/main.cpp src/algorithms/utils.cpp src/algorithms/bfs.cpp src/algorithms/idfs.cpp src/algorithms/gbfs.cpp src/algorithms/astar.cpp src/algorithms/idastar.cpp -o main -O2 -std=c++11