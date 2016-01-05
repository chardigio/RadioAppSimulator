#include "Time.h"

Time::Time(std::string time_string){
  this->init_time = parseTime(time_string);
  this->elapsed_time = 0;
}

void Time::elapse(unsigned int time){
  this->elapsed_time += time;
}

void Time::elapse(std::string time_string){
  this->elapsed_time += parseTime(time_string);
}

unsigned int Time::getElapsedTime(){
  return this->elapsed_time;
}

std::string Time::prettyCurrentTime(){
  int SECS_IN_DAY = 86400;
  int SECS_IN_HOUR = 3600;
  int SECS_IN_MIN = 60;
  int MINS_IN_HOUR = 60;

  unsigned int hours = 0;
  unsigned int minutes = 0;
  unsigned int seconds = 0;
  unsigned int days = 1;

  bool am = (this->init_time / SECS_IN_HOUR) < 12;

  seconds = this->init_time % SECS_IN_MIN + this->elapsed_time % SECS_IN_MIN;
  if (seconds >= SECS_IN_MIN){
    seconds -= SECS_IN_MIN;
    minutes++;
  }

  minutes += (this->init_time / MINS_IN_HOUR) % MINS_IN_HOUR +
          (this->elapsed_time / MINS_IN_HOUR) % MINS_IN_HOUR;
  if (minutes >= MINS_IN_HOUR){
    minutes -= MINS_IN_HOUR;
    hours++;
  }

  hours += (this->init_time / SECS_IN_HOUR) +
        (this->elapsed_time / SECS_IN_HOUR) % 24;

  am = (hours / 12) % 2 == 0;

  hours %= 12;
  if (hours == 0) hours = 12;

  days += (this->init_time + this->elapsed_time) / SECS_IN_DAY;

  std::string am_string;
  std::string minute_string;
  std::string second_string;

  if (am) am_string = "am";
  else am_string = "pm";

  if (minutes < 10) minute_string = "0" + std::to_string(minutes);
  else minute_string = std::to_string(minutes);

  if (seconds < 10) second_string = "0" + std::to_string(seconds);
  else second_string = std::to_string(seconds);

  std::string pretty_current_time = "[Day " + std::to_string(days) + ": " +
    std::to_string(hours) + ":" +
    minute_string + ":" +
    second_string +
    am_string + "]";

  return pretty_current_time;
}
