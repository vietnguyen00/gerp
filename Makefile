#
#  Viet Nguyen
#  Makefile
#  COMP15
#  Spring 2019
#  Project II: Gerp
#

CC = clang++
CFLAGS = -O2 -g3 -Wall -Wextra -std=c++11
DEPS = DirNode.h FSTree.h HashTable.h Entry.h  

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gerp: main.o HashTable.o DirNode.o FSTree.o
	$(CC) -o gerp main.o HashTable.o DirNode.o FSTree.o

testGerp: testGerp.o HashTable.o DirNode.o FSTree.o
	$(CC) -o testGerp testGerp.o HashTable.o DirNode.o FSTree.o

clean:
	rm -f *.o core* *~gerp
	rm -f *.o core* *~testGerp