#ifndef _Time_H_
#define _Time_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

class Time{
  private:
    unsigned int init_time; // seconds since 00:00:00
    unsigned int elapsed_time; // seconds since init_time

  public:
    Time(std::string time_string);

    void elapse(unsigned int elapsed_time);
    void elapse(std::string time_string);
    unsigned int getElapsedTime();
    std::string prettyCurrentTime();

    static unsigned int parseTime(std::string time_string){
      unsigned int hours = 0;
      unsigned int minutes = 0;
      unsigned int seconds = 0;

      switch (time_string.length()){
        case 8:
          hours   += 10 * (time_string[0] - '0');
          hours   += time_string[1] - '0';
          minutes += 10 * (time_string[3] - '0');
          minutes += time_string[4] - '0';
          seconds += 10 * (time_string[6] - '0');
          seconds += time_string[7] - '0';
          break;
        case 7:
          hours   += time_string[0] - '0';
          minutes += 10 * (time_string[2] - '0');
          minutes += time_string[3] - '0';
          seconds += 10 * (time_string[5] - '0');
          seconds += time_string[6] - '0';
          break;
        case 5:
          minutes += 10 * (time_string[0] - '0');
          minutes += time_string[1] - '0';
          seconds += 10 * (time_string[3] - '0');
          seconds += time_string[4] - '0';
          break;
        case 4:
          minutes += time_string[0] - '0';
          seconds += 10 * (time_string[2] - '0');
          seconds += time_string[3] - '0';
          break;
        default:
          std::cout << "Cannot parse string." << std::endl;
      }

      return 3600*hours + 60*minutes + seconds;
    }
};

#endif
