#include "utilities.h"

void delay_s(int seconds) {
  unsigned int delayTime = time(0) + seconds;
  while (time(0) < delayTime);
}

int currentFloor(){
  for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
    if(hardware_read_floor_sensor(floor)==1){
      return floor;
    }
  }
  return -1;
}
