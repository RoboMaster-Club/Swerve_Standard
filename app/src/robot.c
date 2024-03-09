#include "robot.h"

#include "robot_tasks.h"
#include "chassis_task.h"

void Robot_Init() {
    // Initialize all hardware
    Chassis_Init();
    // Initialize all tasks
    Robot_Tasks_Start();
}
 