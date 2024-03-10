#include "robot.h"
#include "robot_tasks.h"

void Robot_Init() {
    // Initialize all hardware
    
    // Initialize all tasks
    Robot_Tasks_Start();
}

void Robot_Ctrl_Loop() {
    // Control loop for the robot
    Chassis_Ctrl_Loop();
}