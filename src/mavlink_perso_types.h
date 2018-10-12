#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <mavlink.h>


//!!!!!!!!!!!!!!!!!TO FINSIH!!!!!!!!!!!!!!!!!!!!!!!!
typedef struct vehicle {
	mavlink_heartbeat_t heartbeat;
	mavlink_sys_status_t sys_status;
	mavlink_system_time_t system_time;
	mavlink_gps_raw_int_t gps_raw_int;
	mavlink_raw_imu_t raw_imu;
	mavlink_scaled_pressure_t scaled_pressure;
	mavlink_attitude_t attitude;
	
	
	mavlink_statustext_t statustext;
	
} Vehicle;