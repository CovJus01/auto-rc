#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/debug_value.h>
#include <uORB/topics/test_motor.h>

#define DC_MOTOR 0
#define SERVO 1

extern "C" __EXPORT int experiment_2c_main(int argc, char *argv[]);
int experiment_2c_main(int argc, char *argv[])
{
	// Setup the variables
	test_motor_s test_motor;
	float motor_value = 0.1; // a number between 0 to 1
	float servo_value = 0.1;
	
	uORB::Publication<test_motor_s> test_motor_pub(ORB_ID(test_motor));
	uORB::Publication<debug_value_s> debug_value_pub(ORB_ID(debug_value));
	
	
	
	px4_sleep(2);
	debug_value_s debug_data;
	int debug_handle = orb_subscribe(ORB_ID(debug_value));
	orb_set_interval(debug_handle, 500);
	
	while(1)
	{

		orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);
		//Set the direction based on recieved index
		if(debug_data.ind == 0) {
			servo_value = 0.9;
		}
		else if(debug_data.ind == 1){
			servo_value = 0.5;
		}
		else if(debug_data.ind ==2){
			servo_value = 0.1;
		} 
		else {
			servo_value = 0.5;
		}
		
		//Set the motor speed based on percieved distance
		if(debug_data.value > 50.0f){
			motor_value = 0.9;
		}
		else if(debug_data.value >15.0f) {
			motor_value = 0.7;
		}
		else{
			motor_value = 0.5;
		}
		
		debug_value_pub.publish(debug_data);
		
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = DC_MOTOR;
		test_motor.value = (float)motor_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;
		test_motor_pub.publish(test_motor);

		
		test_motor.timestamp = hrt_absolute_time();
		test_motor.motor_number = SERVO;
		test_motor.value = (float)servo_value;
		test_motor.action = test_motor_s::ACTION_RUN;
		test_motor.driver_instance = 0;
		test_motor.timeout_ms = 0;
		test_motor_pub.publish(test_motor);
		px4_usleep(1000);
	}
	return 0;
}
