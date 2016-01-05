#ifndef _Song_H_
#define _Song_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Time.h"

class Song{
  public:
    Song(std::string title, std::string artist, std::string duration, unsigned int lastPlayed);

    void play(unsigned int elapsedTime);
    void like();
    void dislike();
    int getKey(unsigned int elapsedTime);
    std::string getTitle();
    unsigned int getDuration();
    void setLastPlayed(unsigned int lastPlayed);
    std::string prettyCurrentSong();
    void out(unsigned int elapsedTime);

  private:
    unsigned int last_played; //seconds since init time
    int likeability;
    unsigned int duration;
    std::string title;
    std::string artist;
};

#endif
