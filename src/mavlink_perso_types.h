#ifndef _MAVLINK_PERSO_TYPES_H_
#define _MAVLINK_PERSO_TYPES_H_

#include <stdlib.h>
#include <fcntl.h>
#include "./include/ardupilotmega/mavlink.h"

/**
 * @brief      mavlink enumeration
 *
 */
typedef enum MAV_ENUM
{
	ENUM_MAV_CMD_ACK=0,
	ENUM_MAV_CMD,
	ENUM_MAV_PARAM_TYPE
} MAV_ENUM;


/**
 * @brief      Contains all informations of the vehicle
 *
 */
typedef struct vehicle {
	mavlink_system_t system_ids;
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

#endif