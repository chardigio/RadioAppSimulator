#include "Song.h"

Song::Song(std::string title, std::string artist, std::string duration, unsigned int lastPlayed){
  this->title = title;
  this->artist = artist;
  this->duration = Time::parseTime(duration);
  this->last_played = lastPlayed;
  this->likeability = 0;
}

void Song::play(unsigned int elapsedTime){
  this->last_played = elapsedTime;
}

void Song::like(){
  this->likeability < 0 ? this->likeability = 1 : this->likeability++;
}

void Song::dislike(){
  this->likeability > 0 ? this->likeability = -1 : this->likeability--;
}

int Song::getKey(unsigned int elapsedTime){
  return (elapsedTime - this->last_played) + (100 * this->likeability);
}

std::string Song::getTitle(){
  return this->title;
}

unsigned int Song::getDuration(){
  return this->duration;
}

void Song::setLastPlayed(unsigned int lastPlayed){
  this->last_played = lastPlayed;
}

std::string Song::prettyCurrentSong(){
  return this->title + " by " + this->artist;
}

void Song::out(unsigned int elapsedTime){
  if (elapsedTime < -1){
    std::cout << "    " << this->title << " - " <<
      this->artist << " (" <<
      this->duration << "s)\n    Last played at elapsed_time: " <<
      this->last_played << "\n    Likes: " <<
      this->likeability << "\n    Key: " <<
      this->getKey(elapsedTime) << std::endl;
  }else{
    std::cout << "    " << this->title << " - " <<
      this->artist << " (" <<
      this->duration << "s)\n    Last played at elapsed_time: " <<
      this->last_played << "\n    Likes: " <<
      this->likeability << std::endl;
  }
}
