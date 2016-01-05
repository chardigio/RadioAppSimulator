#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Song.h"

class Hash{
	public:
		Hash(int size);
		~Hash();

		int add(Song* song);
		Song* find(std::string title);
		void out();

	private:
		Song** data;
		int size;
		int first_null_index;

		int getHashIndex(std::string title);
		int tryToInsert(Song* song, int index, int tries);
		Song* tryToFind(int index, std::string title);
};
