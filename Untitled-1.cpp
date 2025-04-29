#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/led_control.h>
#include <uORB/topics/debug_value.h>
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
int hello_world_main(int argc, char *argv[])
{
px4_sleep(2);
debug_value_s debug_data;
int debug_handle = orb_subscribe(ORB_ID(debug_value));
orb_set_interval(debug_handle, 500);
led_control_s led_control;
uORB::Publication<led_control_s> led_control_pub(ORB_ID(led_control));
while(1)
{
orb_copy(ORB_ID(debug_value), debug_handle, &debug_data);
led_control.timestamp = hrt_absolute_time();
led_control.color = led_control_s::COLOR_GREEN;
led_control.priority = led_control_s::MAX_PRIORITY;
led_control.led_mask = 0xff;
if(debug_data.ind == 1)
led_control.mode = led_control_s::MODE_ON;
else
led_control.mode = led_control_s::MODE_OFF;
led_control_pub.publish(led_control);
px4_usleep(500000);
}
return 0
}