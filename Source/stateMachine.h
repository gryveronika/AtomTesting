/** @file
*   @brief Functionality for the statemachine implemented in main
*/
#ifndef STATEMACH_H
#define STATEMACH_H

#include "hardware.h"
#include "utilities.h"
#include "Elevator.h"
#include "queue.h"


/**
* @brief Changes hardware states to the stop state
*
*/
void commandStopState(Elevator* elev);

/**
* @brief Changes hardware states to the idle state
*
*/
void commandIdleState(Elevator* elev);


/**
* @brief Changes hardware states to the up state
*
*/
void commandUpState(Elevator* elev);

/**
* @brief Changes hardware states to the down state
*
*/
void commandDownState(Elevator* elev);





/*
void timer_reset(Elevator* elev);

int timer_isExpired(Elevator* elev);
*/

int countDown(int sec, Elevator* elev);

int paEtasje();


#endif
