#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "queue.h"

/**
* @brief State types used in state machine
*/
typedef enum {
  IDLE_STATE,
  STOP_STATE,
  MOVEUP_STATE,
  MOVEDOWN_STATE,
} elevatorState;

typedef struct {
  int floor;
  int above;
} Position;


typedef struct {
  Position pos;
  char currentDir;
  char prevDir;
  clock_t timer;

  int upQueue[4];
  int downQueue[4];

  int nextFloor;

  elevatorState currState;
  elevatorState nextState;
} Elevator;

/**
* @brief Handles events that changes the next state
* @param[in] a pointer to the current state.
*/
void eventHandler(Elevator* elev);



/**
* @brief Checks if the statemachine should switch into either the MOVEUP_STATE or MOVEDOWN_STATE
* @param[in] the last known floor the elevator was at
* @param[in] the direction the elevator is moving
*/
int getNextFloor(Elevator* elev);
int isAtFloor(Elevator* elev);
void arrivalProcedure(Elevator* elev);
char getNextDirection(Elevator* elev);

void setFloorSensor();

#endif
