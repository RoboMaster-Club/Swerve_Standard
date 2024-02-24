#ifndef SWERVE_MODULE_h
#define SWERVE_MODULE_h

#include "pid.h"
#include "stdbool.h"
#include "dji_motor.h"

typedef struct
{
    float speed; // m/s
    float angle; // deg
} Module_State_t;

typedef struct
{
    bool azimuth_encoder_reversed;
    float azimuth_zero_encoder_offset;
    uint16_t azimuth_can_id;
    PID_t azimuth_pid;
    DJI_Motor_t azimuth_motor;

    uint16_t drive_can_id;
    PID_t drive_pid;
    DJI_Motor_t drive_motor;

    Module_State_t module_state;
} Swerve_Module_t;

extern void Init_Swerve_Module(Swerve_Module_t *swerve_module, bool azimuth_encoder_reversed, int azimuth_can_id);
extern void Set_Module_Output(Swerve_Module_t *swerve_module, Module_State_t desired_state);

#endif