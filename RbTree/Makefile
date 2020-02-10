main.exe: main.o rb_tree.o
	g++ -g -o main main.o rb_tree.o

main.o: rb_tree.h rb_tree.cpp main.cpp
	g++ -g -c main.cpp
	
rb_tree.o: rb_tree.h rb_tree.cpp
	g++ -g -c rb_tree.cpp
