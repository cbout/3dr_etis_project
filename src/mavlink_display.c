#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <mavlink.h>
#include "mavlink_perso_types.h"


/**
* Display an information from the vehicle with the id
*
*
*/
void mavlink_display_info_vehicle_by_id(int id, Vehicle vehicle){
	

	switch (id) {

		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			mavlink_heartbeat_t heartbeat = vehicle.heartbeat;
			printf("HEARTBEAT :\nCustom_mode : %d, Type : %d, Autopilot : %d, Base_mode : %d, System_status : %d, Mavlink_version : %d\n", heartbeat.custom_mode, heartbeat.type, heartbeat.autopilot, heartbeat.base_mode, heartbeat.system_status, heartbeat.mavlink_version);
			break;
		}

		case MAVLINK_MSG_ID_SYS_STATUS:
		{
			mavlink_sys_status_t sys_status = vehicle.sys_status;
			printf("SYS_STATUS :\n Onboard_control_sensors_present : %d, Onboard_control_sensors_enabled : %d, Onboard_control_sensors_health : %d, Load : %d, Voltage_battery : %d, Current_battery : %d, Drop_rate_comm : %d, Errors_comm : %d, Errors_count1 : %d, Errors_count2 : %d, Errors_count3 : %d, Errors_count4 : %d, Battery_remaining : %d\n", sys_status.onboard_control_sensors_present, sys_status.onboard_control_sensors_enabled, sys_status.onboard_control_sensors_health, sys_status.load, sys_status.voltage_battery, sys_status.current_battery, sys_status.drop_rate_comm, sys_status.errors_comm, sys_status.errors_count1, sys_status.errors_count2, sys_status.errors_count3, sys_status.errors_count4, sys_status.battery_remaining);
			break;
		}

		case MAVLINK_MSG_ID_SYSTEM_TIME:
		{
			mavlink_system_time_t system_time = vehicle.system_time;
			printf("SYSTEM_TIME :\nTime_unix_usec : %llu, Time_boot_ms : %d\n", system_time.time_unix_usec, system_time.time_boot_ms);
			break;
		}

		case MAVLINK_MSG_ID_GPS_RAW_INT:
		{
			mavlink_gps_raw_int_t gps_raw_int = vehicle.gps_raw_int;
			printf("GPS_RAW_INT :\nTime_usec : %llu, Lat : %d, Lon : %d, Alt : %d, Eph : %d, Epv : %d, Vel : %d, Cog : %d, Fix_type : %d, Satellites_visible : %d\n", gps_raw_int.time_usec, gps_raw_int.lat, gps_raw_int.lon, gps_raw_int.alt, gps_raw_int.eph, gps_raw_int.epv, gps_raw_int.vel, gps_raw_int.cog, gps_raw_int.fix_type, gps_raw_int.satellites_visible);
			break;
		}

		case MAVLINK_MSG_ID_RAW_IMU:
		{
			mavlink_raw_imu_t raw_imu = vehicle.raw_imu;
			printf("RAW_IMU :\nTime_usec : %llu, Xacc : %d, Yacc : %d, Zacc : %d, Xgyro : %d, Ygyro : %d, Zgyro : %d, Xmag : %d, Ymag : %d, Zmag : %d\n", raw_imu.time_usec, raw_imu.xacc, raw_imu.yacc, raw_imu.zacc, raw_imu.xgyro, raw_imu.ygyro, raw_imu.zgyro, raw_imu.xmag, raw_imu.ymag, raw_imu.zmag);
			break;
		}

		case MAVLINK_MSG_ID_SCALED_PRESSURE:
		{
			mavlink_scaled_pressure_t scaled_pressure = vehicle.scaled_pressure;
			printf("SCALED_PRESSURE :\nTime_boot_ms : %d, Press_abs : %f, Press_diff : %f, Temperature : %d\n", scaled_pressure.time_boot_ms, scaled_pressure.press_abs, scaled_pressure.press_diff, scaled_pressure.temperature);
			break;
		}

		case MAVLINK_MSG_ID_ATTITUDE:
		{
			mavlink_attitude_t attitude = vehicle.attitude;
			printf("ATTITUDE :\nTime_boot_ms : %d, Roll : %f, Pitch : %f, Yaw : %f, Rollspeed : %f, Pitchspeed : %f, Yawspeed : %f\n", attitude.time_boot_ms, attitude.roll, attitude.pitch, attitude.yaw, attitude.rollspeed, attitude.pitchspeed,  attitude.yawspeed);
			break;
		}

		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
		{
			mavlink_global_position_int_t global_position_int = vehicle.global_position_int;
			printf("GLOBAL_POSITION_INT :\nTime_boot_ms : %d, Lat : %d, Lon : %d, Alt : %d, Relative_alt : %d, Vx : %d, Vy : %d, Vz : %d, Hdg : %d\n", global_position_int.time_boot_ms, global_position_int.lat, global_position_int.lon, global_position_int.alt, global_position_int.relative_alt, global_position_int.vx, global_position_int.vy, global_position_int.vz, global_position_int.hdg);
			break;
		}

		case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
		{
			mavlink_rc_channels_raw_t rc_channels_raw = vehicle.rc_channels_raw;
			printf("RC_CHANNELS_RAW :\nTime_boot_ms : %d, Chan1_raw : %d, Chan2_raw : %d, Chan3_raw : %d, Chan4_raw : %d, Chan5_raw : %d, Chan6_raw : %d, Chan7_raw : %d, Chan8_raw : %d, Port : %d, Rssi : %d\n", rc_channels_raw.time_boot_ms, rc_channels_raw.chan1_raw, rc_channels_raw.chan2_raw, rc_channels_raw.chan3_raw, rc_channels_raw.chan4_raw, rc_channels_raw.chan5_raw, rc_channels_raw.chan6_raw, rc_channels_raw.chan7_raw, rc_channels_raw.chan8_raw, rc_channels_raw.port, rc_channels_raw.rssi);
			break;
		}

		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
		{
			mavlink_servo_output_raw_t servo_output_raw = vehicle.servo_output_raw;
			printf("SERVO_OUTPUT_RAW :\nTime_usec : %d, Servo1_raw : %d, Servo2_raw : %d, Servo3_raw : %d, Servo4_raw : %d, Servo5_raw : %d, Servo6_raw : %d, Servo7_raw : %d, Servo8_raw : %d, Port : %d\n", servo_output_raw.time_usec, servo_output_raw.servo1_raw, servo_output_raw.servo2_raw, servo_output_raw.servo3_raw, servo_output_raw.servo4_raw, servo_output_raw.servo5_raw, servo_output_raw.servo6_raw, servo_output_raw.servo7_raw, servo_output_raw.servo8_raw, servo_output_raw.port);
			break;
		}

		case MAVLINK_MSG_ID_MISSION_CURRENT:
		{
			mavlink_mission_current_t mission_current = vehicle.mission_current;
			printf("MISSION_CURRENT :\nSeq : %d\n", mission_current.seq);
			break;
		}

		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
		{
			mavlink_nav_controller_output_t nav_controller_output = vehicle.nav_controller_output;
			printf("NAV_CONTROLLER_OUTPUT :\nNav_roll : %f, Nav_pitch : %f, Alt_error : %f, Aspd_error : %f, Xtrack_error : %f, Nav_bearing : %d, Target_bearing : %d, Wp_dist : %d\n", nav_controller_output.nav_roll, nav_controller_output.nav_pitch, nav_controller_output.alt_error, nav_controller_output.aspd_error, nav_controller_output.xtrack_error,  nav_controller_output.nav_bearing, nav_controller_output.target_bearing, nav_controller_output.wp_dist);
			break;
		}

		case MAVLINK_MSG_ID_VFR_HUD:
		{
			mavlink_vfr_hud_t vfr_hud = vehicle.vfr_hud;
			printf("VFR_HUD :\nAirspeed : %f, Groundspeed : %f, Alt : %f, Climb : %f, Heading : %d, Throttle : %d\n", vfr_hud.airspeed, vfr_hud.groundspeed, vfr_hud.alt, vfr_hud.climb, vfr_hud.heading, vfr_hud.throttle);
			break;
		}

		case MAVLINK_MSG_ID_RADIO_STATUS:
		{
			mavlink_radio_status_t radio_status = vehicle.radio_status;
			printf("RADIO_STATUS :\nRxerrors : %d, Fixed : %d, Rssi : %d, Remrssi : %d, Txbuf : %d, Noise : %d, Remnoise : %d\n", radio_status.rxerrors, radio_status.fixed, radio_status.rssi, radio_status.remrssi, radio_status.txbuf,  radio_status.noise,  radio_status.remnoise);
			break;
		}

		case MAVLINK_MSG_ID_SCALED_IMU2:
		{
			mavlink_scaled_imu2_t scaled_imu2 = vehicle.scaled_imu2;
			printf("SCALED_IMU2 :\nTime_boot_ms : %d, Xacc : %d, Yacc : %d, Zacc : %d, Xgyro : %d, Ygyro : %d, Zgyro : %d, Xmag : %d, Ymag : %d, Zmag : %d\n", scaled_imu2.time_boot_ms, scaled_imu2.xacc, scaled_imu2.yacc, scaled_imu2.zacc, scaled_imu2.xgyro, scaled_imu2.ygyro, scaled_imu2.zgyro, scaled_imu2.xmag, scaled_imu2.ymag, scaled_imu2.zmag);
			break;
		}

		case MAVLINK_MSG_ID_POWER_STATUS:
		{
			mavlink_power_status_t power_status = vehicle.power_status;
			printf("POWER_STATUS :\nVcc : %d, Vservo : %d, Flags : %d\n", power_status.Vcc, power_status.Vservo, power_status.flags);
			break;
		}

		case MAVLINK_MSG_ID_SCALED_IMU3:
		{
			mavlink_scaled_imu3_t scaled_imu3 = vehicle.scaled_imu3;
			printf("SCALED_IMU3 :\nTime_boot_ms : %d, Xacc : %d, Yacc : %d, Zacc : %d, Xgyro : %d, Ygyro : %d, Zgyro : %d, Xmag : %d, Ymag : %d, Zmag : %d\n", scaled_imu3.time_boot_ms, scaled_imu3.xacc, scaled_imu3.yacc, scaled_imu3.zacc, scaled_imu3.xgyro, scaled_imu3.ygyro, scaled_imu3.zgyro, scaled_imu3.xmag, scaled_imu3.ymag, scaled_imu3.zmag);
			break;
		}

		case MAVLINK_MSG_ID_TERRAIN_REQUEST:
		{
			mavlink_terrain_request_t terrain_request = vehicle.terrain_request;
			printf("TERRAIN_REQUEST :\nMask : %lu, Lat : %d, Lon : %d, Grid_spacing : %d\n", terrain_request.mask, terrain_request.lat, terrain_request.lon, terrain_request.grid_spacing);
			break;
		}

		case MAVLINK_MSG_ID_TERRAIN_REPORT:
		{
			mavlink_terrain_report_t terrain_report = vehicle.terrain_report;
			printf("TERRAIN_REPORT :\nLat : %d, Lon : %d, Terrain_height : %f, Current_height : %f, Spacing : %d, Pending : %d, Loaded : %d\n", terrain_report.lat, terrain_report.lon, terrain_report.terrain_height, terrain_report.current_height, terrain_report.spacing, terrain_report.pending, terrain_report.loaded);
			break;
		}

		case MAVLINK_MSG_ID_SCALED_PRESSURE2:
		{
			mavlink_scaled_pressure2_t scaled_pressure2 = vehicle.scaled_pressure2;
			printf("SCALED_PRESSURE2 :\nTime_boot_ms : %d, Press_abs : %f, Press_diff : %f, Temperature : %d\n", scaled_pressure2.time_boot_ms, scaled_pressure2.press_abs, scaled_pressure2.press_diff, scaled_pressure2.temperature);
			break;
		}

		case MAVLINK_MSG_ID_NAMED_VALUE_INT:
		{
			mavlink_named_value_int_t named_value_int = vehicle.named_value_int;
			printf("NAMED_VALUE_INT :\nTime_boot_ms : %d, Value : %d, Name : %s\n", named_value_int.time_boot_ms, named_value_int.value, named_value_int.name);
			break;
		}

		case MAVLINK_MSG_ID_STATUSTEXT:
		{
			mavlink_statustext_t statustext = vehicle.statustext;
			printf("STATUSTEXT :\nSeverity : %d, Text : %s\n", statustext.severity, statustext.text);
			break;
		}

		default :
			printf("Unknow id\n");
			break;
	}
}


/**
* Display all informations from the vehicle
*
*
*/
void mavlink_display_info_vehicle_all(Vehicle vehicle){
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_HEARTBEAT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SYS_STATUS, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SYSTEM_TIME, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_GPS_RAW_INT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RAW_IMU, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_PRESSURE, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_ATTITUDE, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RC_CHANNELS_RAW, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SERVO_OUTPUT_RAW, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_MISSION_CURRENT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_VFR_HUD, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RADIO_STATUS, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_IMU2, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_POWER_STATUS, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_IMU3, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_TERRAIN_REQUEST, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_TERRAIN_REPORT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_PRESSURE2, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_NAMED_VALUE_INT, vehicle);
	mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_STATUSTEXT, vehicle);
}


/**
* Display the main menu
*
*
*/
void mavlink_display_main_menu(){
	printf("\n-------------------------------------------------------------------------------------Main menu-------------------------------------------------------------------------------------\n");
	printf("1 : arm motors\n");
	printf("2 : disarm motors\n");
	printf("p : display informations\n");
	printf("c : control drone\n");
	printf("e : to exit\n");
}


/**
* Display the display menu
*
*
*/
void mavlink_display_display_menu(){
	printf("\n-------------------------------------------------------------------------------------Display menu-------------------------------------------------------------------------------------\n");
	printf("1 : display all\n\n");
	printf("2 : display heartbeat");
	printf("	3 : display sys_status");
	printf("	4 : display system_time");
	printf("	5 : display gps_raw_int\n");
	printf("6 : display raw_imu");
	printf("	7 : display scaled_pressure");
	printf("	8 : display attitude");
	printf("	9 : display global_position_int\n");
	printf("10 : display rc_channels_raw");
	printf("	11 : display servo_output_raw");
	printf("	12 : display mission_current");
	printf("	13 : display nav_controller_output\n");
	printf("14 : display vfr_hud");
	printf("	15 : display radio_status");
	printf("	16 : display scaled_imu2");
	printf("	17 : display power_status\n");
	printf("18 : display scaled_imu3");
	printf("	19 : display terrain_request");
	printf("	20 : display terrain_report");
	printf("	21 : display scaled_pressure2\n");
	printf("22 : display named_value_int");
	printf("	23 : display statustext\n\n");	
	printf("0 : to quit this menu\n\n");
}


/**
* Display the control menu
*
*
*/
void mavlink_display_control_menu(){
	printf("\n-------------------------------------------------------------------------------------Control menu-------------------------------------------------------------------------------------\n");
	printf("z : move forward\n");
	printf("s : move back\n");
	printf("q : move left\n");
	printf("d : move right\n");
	printf("i : go up\n");
	printf("k : go down\n");
	printf("j : rotate left\n");
	printf("l : rotate right\n\n");
	printf("' ' : to exit this menu\n\n");
	//...
}
