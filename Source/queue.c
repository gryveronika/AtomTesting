#include "queue.h"



void addUpQueue(Elevator* elev){
  for(int order=HARDWARE_ORDER_UP; order<=HARDWARE_ORDER_INSIDE; order++) {
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
      if (hardware_read_order(floor,order)==1){
              elev->upQueue[floor]=1;
              hardware_command_order_light(floor, order, 1);
        }
      }
    }
  return;
}



void addDownQueue(Elevator* elev) {
  for(int order=HARDWARE_ORDER_INSIDE; order<=HARDWARE_ORDER_DOWN; order++) {
    for (int floor = 0; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
      if (hardware_read_order(floor,order)==1){
              elev->downQueue[floor]=1;
              hardware_command_order_light(floor, order, 1);
        }
      }
    }
  return;
}

int checkIfQueueEmpty(int queue[]){
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
    if (queue[i] == 1) {
      return 0;
    }
  }
  return 1;
}
