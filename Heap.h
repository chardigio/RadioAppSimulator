#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "Song.h"
#include "Time.h"

class Heap{
  public:
    Heap(int size);
    ~Heap();

    int add(Song* song, unsigned int elapsedTime);
    Song* play(Time*& time);
    void maxHeapify(unsigned int elapsedTime);
    void out(unsigned int elapsedTime);

  private:
    Song** data;
    int size;
    int first_null_index;

    void maxHeapify(int i, unsigned int elapsedTime);
};
