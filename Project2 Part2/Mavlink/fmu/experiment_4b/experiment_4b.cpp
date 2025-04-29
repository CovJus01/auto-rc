#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/log.h>
#include <drivers/drv_hrt.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/debug_value.h>



extern "C" __EXPORT int experiment_4b_main(int argc, char *argv[]);
int experiment_4b_main(int argc, char *argv[])
{
	printf("The Application starts!");
	int counter = 0;
	debug_value_s debug_data;
	uORB::Publication<debug_value_s> debug_value_pub(ORB_ID(debug_value));

	while (1) {
		debug_data.timestamp = hrt_absolute_time();
		debug_data.value = counter / 2.0f;
		debug_data.ind = counter;
		debug_value_pub.publish(debug_data);
		counter++;
		px4_sleep(1);
	}
	return 0;
}
