#ifndef SWERVE_MODULE_h
#define SWERVE_MODULE_h

#include "pid.h"
#include <stdbool.h>
#include "dji_motor.h"

typedef struct
{
    float speed; // m/s
    float angle; // deg
} Module_State_t;

typedef struct
{
    bool Azimuth_Encoder_Reversed;
    int Azimuth_CAN_ID;
    float Azimuth_Encoder_Zero_Offset;

    uint16_t Drive_CAN_ID;
    PID_t Azimuth_PID;
    DJI_Motor_t Azimuth_Motor;

    PID_t Drive_PID;
    DJI_Motor_t Drive_Motor;

    Module_State_t Module_State;
} Swerve_Module_t;

extern void Init_Swerve_Module(Swerve_Module_t *Swerve_Module, bool Azimuth_Encoder_Reversed, int Azimuth_CAN_ID);
extern void Set_Module_Output(Swerve_Module_t *Swerve_Module, Module_State_t Desired_State);

#endif