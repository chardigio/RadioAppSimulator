#include "Heap.h"

Heap::Heap(int size){
	this->first_null_index = 0;
	this->size = size;
	this->data = new Song*[size];

	for (int i=0; i<size; i++) this->data[i] = nullptr;
}

int Heap::add(Song* song, unsigned int elapsedTime){
	if (this->first_null_index >= this->size) return 1;

	this->data[this->first_null_index] = song;
	this->first_null_index++;

	this->maxHeapify(elapsedTime);

	return 0;
}

Song* Heap::play(Time*& time){
	Song* playing = this->data[0];

	std::cout << time->prettyCurrentTime() << " " << playing->prettyCurrentSong() << std::endl;

	time->elapse(this->data[0]->getDuration());
	this->data[0]->setLastPlayed(time->getElapsedTime());

	this->maxHeapify(time->getElapsedTime());

	return playing;
}

void Heap::maxHeapify(unsigned int elapsedTime){
	for (int i=(this->first_null_index-1)/2; i >= 0; i--)
		this->maxHeapify(i, elapsedTime);
}

void Heap::maxHeapify(int i, unsigned int elapsedTime){
	int n = this->first_null_index;
	int l = 2*i+1;
	int r = 2*i+2;
	int largest = 0;

	if (l < n && this->data[l]->getKey(elapsedTime) > this->data[i]->getKey(elapsedTime))
		largest = l;
	else
		largest = i;

	if (r < n && this->data[r]->getKey(elapsedTime) > this->data[largest]->getKey(elapsedTime))
		largest = r;

	if (largest != i){
		Song* tmp = this->data[i];
		this->data[i] = this->data[largest];
		this->data[largest] = tmp;

		this->maxHeapify(largest, elapsedTime);
	}
}

void Heap::out(unsigned int elapsedTime){
	for (int i = 0; i < this->size; i++){
		if (this->data[i]){
			std::cout << "[" << i << "] SONG:" << std::endl;
			this->data[i]->out(elapsedTime);
		}else{
			//std::cout << "[" << i << "] NULL" << std::endl;
		}
	}
}

Heap::~Heap(){
	for (int i=0; i<this->size; i++) delete this->data[i];

	delete[] this->data;
}
