all:
	g++ -g -c *.cpp -I./
	gcc *.o -ljansson -lprogbase -lprogbase-cpp -lssl
	gnome-terminal --tab -e "/bin/bash -c 'valgrind --leak-check=yes ./a.out; exec /bin/bash -i'"
	rm *.o