#ifndef SWERVE_h
#define SWERVE_h

#include "Swerve_Module.h"

// PHYSICAL CONSTANTS
#define SWERVE_MAX_SPEED 2.0f          // m/s
#define SWERVE_MAX_ANGLUAR_SPEED 90.0f // deg/s
#define TRACK_WIDTH 0.23f              // m, measured wheel to wheel (side to side)
#define WHEEL_BASE 0.23f               // m, measured wheel to wheel (up and down)
#define Wheel_Diameter 0.25f
#define Azimuth_Gear_Ratio 1.0f
#define Drive_Gear_Ratio 16.8f

#define NUMBER_OF_MODULES 4

// PID Constants
#define Azimuth_kP 10000.0f // TODO proper units
#define Azimuth_kI 0.0f
#define Azimuth_kD 0.0f
#define Azimuth_Output_Max 18000.0f

typedef struct
{
    Swerve_Module_t modules[NUMBER_OF_MODULES];
} Swerve_t;

typedef struct
{
    float x, y, omega;
} Chassis_Speeds_t;

typedef struct
{
    Module_State_t states[NUMBER_OF_MODULES];
} Module_State_Array_t;

extern Swerve_t swerve;

extern void Init_Modules(void);
extern void Swerve_Processing(Swerve_t *swerve);

#endif