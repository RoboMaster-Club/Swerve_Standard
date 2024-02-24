#include "Swerve_Module.h"
#include <stdbool.h>
#include <user_math.h>

void Set_Module_Output(Swerve_Module_t *swerve_module, Module_State_t desired_state);

/* Initialize physical swerve constants */
void Init_Swerve_Module(Swerve_Module_t *swerve_module, bool azimuth_encoder_reversed, int azimuth_can_id)
{ // TODO add relevant constants
	swerve_module->azimuth_encoder_reversed = azimuth_encoder_reversed;
	swerve_module->azimuth_can_id = azimuth_can_id;
}

/* Optimize wheel angle so wheel doesn't have to rotate more than 90deg*/
Module_State_t Optimize_Module_Angle(Module_State_t input_state, float measured_angle)
{
	Module_State_t optimized_module_state;
	float wheel_angle_delta = input_state.angle - measured_angle;

	if (fabsf(wheel_angle_delta) > PI / 2)
	{ // if the delta is more than 90 degrees
		optimized_module_state.speed = -1 * input_state.speed;
		optimized_module_state.angle = fmodf(input_state.angle + PI, 2 * PI); // rotate the target by 180 degrees
	}

	return optimized_module_state;
}

/*Command motors to output calculated module state*/
void Set_Module_Output(Swerve_Module_t *swerve_module, Module_State_t desired_state)
{
	// TODO
}