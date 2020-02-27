#include "Elevator.h"

void eventHandler(Elevator* elev) {   //finner ut hva det neste som skal skje er
  getNextFloor(elev);         //fordi verdiene til elev-variablene endres?
  getNextDirection(elev);   //hvorfor kalles disse uten at verdien lagres?

  if (hardware_read_stop_signal()) {
    elev->nextState = STOP_STATE;
  }
  else if (checkIfQueueEmpty(elev->upQueue) && checkIfQueueEmpty(elev->downQueue)) {
    elev->nextState = IDLE_STATE;
  }
  // NEED TO CHECK IF MOVEUP OR MOVEDOWN STATE
  else if (elev->currentDir == 'U') {
    elev->nextState = MOVEUP_STATE;
  }
  else if (elev->currentDir == 'D') {
    elev->nextState = MOVEDOWN_STATE;
  }

}

char getNextDirection(Elevator* elev) {
  elev->prevDir = elev->currentDir;

  if (elev->nextFloor > elev->pos.floor) {
    elev->currentDir = 'U';
    return 'U';
  }
  else if (elev->nextFloor < elev->pos.floor) {
    elev->currentDir = 'D';
    return 'D';
  }

  return 'I';
}

int getNextFloor(Elevator* elev) {   //setter nextFloor til i
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {   //husk at det kan være ting i upqueue som gjør at vi må bevege oss nedover
    if (elev->upQueue[i] == 1 && elev->pos.floor < i && elev->currentDir == 'U' && elev->pos.floor != -1) {
      elev->nextFloor = i;
      return i;
    }
  }

  for (int i = HARDWARE_NUMBER_OF_FLOORS - 1; i <= 0; i--) {
    if (elev->downQueue[i] == 1 && elev->pos.floor > i && elev->currentDir == 'D' && elev->pos.floor != -1) {
      elev->nextFloor = i;
      return i;
    }
  }
  return -1;
}

int isAtFloor(Elevator* elev) {
  if (elev->nextFloor == elev->pos.floor) {
    return 1;
  }
  return 0;
}


void arrivalProcedure(Elevator* elev) {
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  hardware_command_door_open(1);
  hardware_command_order_light(elev->pos.floor, HARDWARE_ORDER_UP, 0);
  hardware_command_order_light(elev->pos.floor, HARDWARE_ORDER_DOWN, 0);
  hardware_command_order_light(elev->pos.floor, HARDWARE_ORDER_INSIDE, 0);

  elev->upQueue[elev->pos.floor] = 0;
  elev->downQueue[elev->pos.floor] = 0;

  elev->pos.floor = elev->nextFloor;    //unødvendig?? eller kanskje ikke..
  elev->pos.above = 0;

  countDown(3, elev);
}

void setFloorSensor() {  //light
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
    if (hardware_read_floor_sensor(i)) {
      hardware_command_floor_indicator_on(i);
    }
  }
}
