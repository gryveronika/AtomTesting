#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevatorInit.h"
#include "stateMachine.h"
#include "utilities.h"
#include "queue.h"
#include "Elevator.h"



int main(void){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    initElevator();
    if (!hardware_read_floor_sensor(0)) {
      fprintf(stderr, "Unable to initialize elevator floor");
      exit(2);
    }
    Elevator elev;
    // Move to initialize?
    elev.currState = IDLE_STATE;
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
      elev.upQueue[i] = 0;
      elev.downQueue[i] = 0;
    }
    (elev.pos).above = 0;
    (elev.pos).floor = 0;
    elev.nextFloor = 0;
    elev.currentDir = 'U';
    //ha hardware_number_of_floors her i steden for?



    while (1) {
        switch (elev.currState) {
          case IDLE_STATE:
          {
            printf("idle\n");
            commandIdleState(&elev);
            eventHandler(&elev);
            addDownQueue(&elev);
            addUpQueue(&elev);
          }
          break;

          case STOP_STATE:
          {
            printf("stop\n");
            commandStopState(&elev);
            eventHandler(&elev);
            if (elev.nextState != STOP_STATE) {
              hardware_command_stop_light(0);
              countDown(3, &elev);
            }
          }
          break;

          case MOVEUP_STATE:
          {
            // Check up order queue
            printf("up %d \n", elev.nextFloor);
            eventHandler(&elev);
            addDownQueue(&elev);
            addUpQueue(&elev);
            commandUpState(&elev);
          }
          break;

          case MOVEDOWN_STATE:
          {
            // Check down order queue
            printf("down %d \n", elev.nextFloor);
            eventHandler(&elev);
            addDownQueue(&elev);
            addUpQueue(&elev);
            commandDownState(&elev);
          }
          break;
        }

        elev.currState = elev.nextState;
    }
}
