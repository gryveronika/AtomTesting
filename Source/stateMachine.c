#include "stateMachine.h"
#include "Elevator.h"

void commandUpState(Elevator* elev) {
  hardware_command_door_open(0);
  hardware_command_movement(HARDWARE_MOVEMENT_UP);
  elev->pos.floor = currentFloor();   //hva når den returnerer -1  (sjekk kommentar i commandDown)
  elev->pos.above = 1;                //
  int correctFloor = isAtFloor(elev); // is at floor returnerer 1 hvis man er på riktig etasje
  setFloorSensor();   //slår på etasjeindikator lys bare:)
  if (correctFloor) {
    arrivalProcedure(elev); //utfører arrivalProcedure hvis riktig etasje
  }
}

void commandDownState(Elevator* elev) {
  hardware_command_door_open(0);
  hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
  elev->pos.floor = currentFloor() - 1;   //blir dette riktig, ikke hvis man bruker pos.floor til noe annet?
  elev->pos.above = 1;                    //passe på at hvis currentFloor()!=-1, kun at settes floor.
  setFloorSensor();
  int correctFloor = isAtFloor(elev);
  if (correctFloor) {
    arrivalProcedure(elev);
  }
}


void commandStopState(Elevator* elev) {
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  hardware_command_stop_light(1);
  if (elev->pos.above == 0) {
    hardware_command_door_open(1);
  }
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
    elev->upQueue[i] = 0;
    elev->downQueue[i] = 0;
    hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
  }

}

void commandIdleState(Elevator* elev) {
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  hardware_command_door_open(0);
}


/*
int checkMovState(char dir, Elevator* elev) {
  if (dir == 'U') {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
      if ((elev->pos.floor < i) && elev->upQueue[i]) {
        return 1;
      }
      else if ((elev->pos.floor<i)&& elev->downQueue[i]){
        return 1;
      }
    }
    return 0;
  }

  if (dir == 'D') {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
      if ((elev->pos.floor > i) && elev->downQueue[i]) {
        return 1;
      }
      else if ((elev->pos.floor>i)&& elev->upQueue[i]){
        return 1;
      }
    }
    return 0;
  }
  return 0;
}
*/

/*
void commandUpState(Elevator* elev) {
  while (hardware_read_obstruction_signal()) {
    hardware_command_door_open(1);
    delay_s(3);
  }
  hardware_command_door_open(0);
  hardware_command_movement(HARDWARE_MOVEMENT_UP);
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
    elev->pos.above = 1;
    if (hardware_read_floor_sensor(i)) {
      elev->pos.floor = i;
      elev->pos.above = 0;
      hardware_command_floor_indicator_on(i);
        if (elev->upQueue[i]) {
          hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
          hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
          hardware_command_door_open(1);
          delay_s(3);
          elev->upQueue[i] = 0;
        }
        else if (elev->downQueue[i]){
          hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
          hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
          hardware_command_movement(HARDWARE_MOVEMENT_STOP);
          hardware_command_door_open(1);
          delay_s(3);
          elev->downQueue[i] = 0;
        }
    }
  }
}
*/
/*
void commandDownState(Elevator* elev) {
  if (hardware_read_obstruction_signal()) {
    hardware_command_door_open(1);
    //timer_reset(&elev);
  }
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
      for (int i = 3; i >= 0; i--) {
        elev->pos.above = 1;
        if (hardware_read_floor_sensor(i)) {
          elev->pos.floor = i;
          elev->pos.above = 0;
          hardware_command_floor_indicator_on(i);
            if (elev->downQueue[i]) {
              hardware_command_order_light(i, HARDWARE_ORDER_DOWN, 0);
              hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
              hardware_command_movement(HARDWARE_MOVEMENT_STOP);
              hardware_command_door_open(1);
              elev->downQueue[i] = 0;
            }

            else if (elev->upQueue[i]){
              hardware_command_order_light(i, HARDWARE_ORDER_UP, 0);
              hardware_command_order_light(i, HARDWARE_ORDER_INSIDE, 0);
              hardware_command_movement(HARDWARE_MOVEMENT_STOP);
              hardware_command_door_open(1);
              delay_s(3);
              elev->upQueue[i] = 0;
            }
            elev->pos.floor = i;
          }
        }
      }
*/

/*
void timer_reset(Elevator* elev) {
  elev->timer = clock();
}

int timer_isExpired(Elevator* elev) {
  long double timeDiff = (long double) (clock() - elev->timer) /(CLOCKS_PER_SEC);
  if (timeDiff >= 3) {
    return 1;
  }
  return 0;
}
*/

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int paEtasje(){
  for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
    if (hardware_read_floor_sensor(i)){
      return 1;
    }
  }
  return 0;
}
//timer?
//returns 1 when countdown is done, without any interrupts


int countDown(int sec, Elevator* elev){     //burde funke nå!!!(:
  unsigned int startCount=time(0);
  unsigned int endCount=time(0);
  while((endCount-startCount)<=sec){

    while(hardware_read_stop_signal()){
      if (currentFloor()!=-1){          //endra her
        hardware_command_door_open(1);
      }
      startCount=time(0);
    }
    while(hardware_read_obstruction_signal()){
      if (currentFloor()!=-1){
        hardware_command_door_open(1);
        startCount=time(0);
        addDownQueue(elev);
        addUpQueue(elev);
        }
      }
 endCount=time(0);
 addDownQueue(elev);
 addUpQueue(elev);
}
hardware_command_door_open(0);
return 1;
}
