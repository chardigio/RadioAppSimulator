#
# Specifiy the target
all:	Hello

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
Hello:	Driver.o Song.o Time.o Hash.o Heap.o
	g++ -std=c++11	-g Song.o Heap.o Hash.o Time.o Driver.o -o Driver

# Specify how the object files should be created from source files
Driver.o:	Driver.cpp
	g++ -std=c++11 -g -c Driver.cpp

Song.o:	Song.cpp
	g++ -std=c++11 -g -c Song.cpp

Time.o:	Time.cpp
	g++ -std=c++11 -g -c Time.cpp

Hash.o:	Hash.cpp
	g++ -std=c++11 -g -c Hash.cpp

Heap.o:	Heap.cpp
	g++ -std=c++11 -g -c Heap.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o Driver
