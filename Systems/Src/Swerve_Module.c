#include "Swerve_Module.h"
#include <stdbool.h>
#include <user_math.h>

void Set_Module_Output(Swerve_Module_t *Swerve_Module, Module_State_t Desired_State);

/* Initialize physical swerve constants */
void Init_Swerve_Module(Swerve_Module_t *Swerve_Module, bool Azimuth_Encoder_Reversed, int Azimuth_CAN_ID)
{ // TODO add relevant constants
	Swerve_Module->Azimuth_Encoder_Reversed = Azimuth_Encoder_Reversed;
	Swerve_Module->Azimuth_CAN_ID = Azimuth_CAN_ID;
}

/* Optimize wheel angle so wheel doesn't have to rotate more than 90deg*/
Module_State_t Optimize_Module_Angle(Module_State_t Input_State, float Measured_Angle)
{
	Module_State_t optimized_module_state;
	float wheel_angle_delta = Input_State.angle - Measured_Angle;

	if (fabsf(wheel_angle_delta) > PI / 2)
	{ // if the delta is more than 90 degrees
		optimized_module_state.speed = -1 * Input_State.speed;
		optimized_module_state.angle = fmodf(Input_State.angle + PI, 2 * PI); // rotate the target by 180 degrees
	}

	return optimized_module_state;
}

/*Command motors to output calculated module state*/
void Set_Module_Output(Swerve_Module_t *Swerve_Module, Module_State_t Desired_State)
{
}