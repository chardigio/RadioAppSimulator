#include "Hash.h"

Hash::Hash(int size){
	this->first_null_index = 0;
	this->size = size;
	this->data = new Song*[size];

	for (int i=0; i<size; i++) this->data[i] = nullptr;
}

int Hash::add(Song* song){
	return this->tryToInsert(song, this->getHashIndex(song->getTitle()), 0);
}

int Hash::getHashIndex(std::string title){
	int sum = 0;
	for (char& c: title)
		sum += c;

	return sum % this->size;
}

int Hash::tryToInsert(Song* song, int index, int tries){
	if (++tries >= this->size-1) return 1;

	if (this->data[index] == nullptr){
		this->data[index] = song;
		return 0;
	}else{
		return this->tryToInsert(song, index+1, tries);
	}
}

Song* Hash::find(std::string title){
	return tryToFind(this->getHashIndex(title), title);
}

Song* Hash::tryToFind(int index, std::string title){
	if (this->data[index]->getTitle() != title)
		return tryToFind(index+1, title);
	else
		return this->data[index];
}

void Hash::out(){
	for (int i = 0; i < this->size; i++){
		if (this->data[i]){
			std::cout << "[" << i << "] SONG:" << std::endl;
			this->data[i]->out(-1);
		}else{
			//std::cout << "[" << i << "] NULL" << std::endl;
		}
	}
}

Hash::~Hash(){
	delete[] this->data;
}
