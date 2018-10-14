#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <mavlink.h>


typedef struct vehicle {
	mavlink_heartbeat_t heartbeat;
	mavlink_sys_status_t sys_status;
	mavlink_system_time_t system_time;
	mavlink_gps_raw_int_t gps_raw_int;
	mavlink_raw_imu_t raw_imu;
	mavlink_scaled_pressure_t scaled_pressure;
	mavlink_attitude_t attitude;
	mavlink_global_position_int_t global_position_int;
	mavlink_rc_channels_raw_t rc_channels_raw;
	mavlink_servo_output_raw_t servo_output_raw;
	mavlink_mission_current_t mission_current;
	mavlink_nav_controller_output_t nav_controller_output;
	mavlink_vfr_hud_t vfr_hud;
	mavlink_radio_status_t radio_status;
	mavlink_scaled_imu2_t scaled_imu2;
	mavlink_power_status_t power_status;
	mavlink_scaled_imu3_t scaled_imu3;
	mavlink_terrain_request_t terrain_request;
	mavlink_terrain_report_t terrain_report;
	mavlink_scaled_pressure2_t scaled_pressure2;
	mavlink_named_value_int_t named_value_int;
	mavlink_statustext_t statustext;
	
} Vehicle;