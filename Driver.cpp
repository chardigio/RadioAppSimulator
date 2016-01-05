#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Time.h"
#include "Song.h"
#include "Hash.h"
#include "Heap.h"

#define DEBUG false

int run(std::string filename, Time*& time, Hash*& hash, Heap*& heap, Song*& playing);
int parseLine(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing);
void init(std::string line, Time*& time, Hash*& hash, Heap*& heap);
void rest(std::string line, Time*& time);
void add(std::string line, Time*& time, Hash*& hash, Heap*& heap);
void play(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing);
void like(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing);
void dislike(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing);

int main(){
	Time* time;
	Hash* hash;
	Heap* heap;
	Song* playing;

	std::string line;
	std::string filename;

	while (getline(std::cin, line)){
		if (line.substr(0, 3) == "RUN"){
			filename = line.substr(4, line.length()-4);
			if (DEBUG){
				std::cout << "\nINPUT: '" << line << "'" << std::endl;
				std::cout << "TIME: " << "NULL" << std::endl;
				std::cout << "-----SONGS-----" << std::endl;
				std::cout << "--HASH--" << std::endl;
				std::cout << "NULL" << std::endl;
				std::cout << "--HEAP--" << std::endl;
				std::cout << "NULL" << std::endl;
				std::cout << "--CLOSE SONGS--\n" << std::endl;
			}
			if (run(filename, time, hash, heap, playing)) break;
		}else{
			if (parseLine(line, time, hash, heap, playing)) break;
			if (DEBUG){
				std::cout << "\nINPUT: '" << line << "'" << std::endl;
				std::cout << "TIME: " << time->prettyCurrentTime() << std::endl;
				std::cout << "-----SONGS-----" << std::endl;
				std::cout << "--HASH--" << std::endl;
				hash->out();
				std::cout << "--HEAP--" << std::endl;
				heap->out(time->getElapsedTime());
				std::cout << "--CLOSE SONGS--\n" << std::endl;
			}
		}
	}

	delete hash;
	delete heap;
	delete time;

	return 0;
}

int run(std::string filename, Time*& time, Hash*& hash, Heap*& heap, Song*& playing){
	std::ifstream file(filename);
	std::string line;
	if (file){
		while (getline(file, line)){
			if (parseLine(line, time, hash, heap, playing)) return 1;
			if (DEBUG){
				std::cout << "\nINPUT: '" << line << "'" << std::endl;
				std::cout << "TIME: " << time->prettyCurrentTime() << std::endl;
				std::cout << "-----SONGS-----" << std::endl;
				std::cout << "--HASH--" << std::endl;
				hash->out();
				std::cout << "--HEAP--" << std::endl;
				heap->out(time->getElapsedTime());
				std::cout << "--CLOSE SONGS--\n" << std::endl;
			}
		}
		file.close();
	}

	return 0;
}

int parseLine(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing){
	if (!line.length()) return 1;

	switch(line[0]){
		case 'I': init(line, time, hash, heap); break;
		case 'R': rest(line, time); break;
		case 'A': add(line, time, hash, heap); break;
		case 'P': play(line, time, hash, heap, playing); break;
		case 'L': like(line, time, hash, heap, playing); break;
		case 'D': dislike(line, time, hash, heap, playing); break;
		default : return 1;
	}

	return 0;
}

void init(std::string line, Time*& time, Hash*& hash, Heap*& heap){
	time = new Time(line.substr(5, 8));

	int size = atoi(line.substr(14, line.length()-14).c_str());
	hash = new Hash(size);
	heap = new Heap(size);
}

void rest(std::string line, Time*& time){
	time->elapse(line.substr(5, line.length()-5));
}

void add(std::string line, Time*& time, Hash*& hash, Heap*& heap){
	int comma1, comma2;

	for (comma1 = 0; line[comma1] != ','; comma1++);
	for (comma2 = comma1+1; line[comma2] != ','; comma2++);

	std::string title = line.substr(4, comma1-4);
	std::string artist = line.substr(comma1+2, comma2-comma1-2);
	std::string duration = line.substr(comma2+2, line.length()-comma2-2);

	Song* song = new Song(title, artist, duration, time->getElapsedTime());

	if (hash->add(song)) delete song;
	else heap->add(song, time->getElapsedTime());
}

void play(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing){
	for (int i = 0; i < atoi(line.substr(5, line.length()-1).c_str()); i++)
		playing = heap->play(time);
}

void like(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing){
	if (line.length() == 4) playing->like();
	else hash->find(line.substr(5, line.length()-1))->like();

	heap->maxHeapify(time->getElapsedTime());
}

void dislike(std::string line, Time*& time, Hash*& hash, Heap*& heap, Song*& playing){
	if (line.length() == 7) playing->dislike();
	else hash->find(line.substr(8, line.length()-1))->dislike();

	heap->maxHeapify(time->getElapsedTime());
}
