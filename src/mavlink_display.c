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
	
	//!!!!!!!!!!!!!!!!!TO FINSIH!!!!!!!!!!!!!!!!!!!!!!!!
	switch (id) {

		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			mavlink_heartbeat_t heartbeat = vehicle.heartbeat;
			printf("Custom mode : %d\n", heartbeat.custom_mode);
			printf("type : %d\n", heartbeat.type);
			printf("autopilot : %d\n", heartbeat.autopilot);
			printf("base_mode : %d\n", heartbeat.base_mode);
			printf("system_status : %d\n", heartbeat.system_status);
			printf("mavlink_version : %d\n", heartbeat.mavlink_version);
			break;
		}

		case MAVLINK_MSG_ID_SYS_STATUS:
		{
			mavlink_sys_status_t sys_status = vehicle.sys_status;
			printf("onboard_control_sensors_present : %d\n", sys_status.onboard_control_sensors_present);
			printf("onboard_control_sensors_enabled : %d\n", sys_status.onboard_control_sensors_enabled);
			printf("onboard_control_sensors_health : %d\n", sys_status.onboard_control_sensors_health);
			printf("load : %d%%\n", sys_status.load);
			printf("voltage_battery : %dmV\n", sys_status.voltage_battery);
			printf("current_battery : %dcA\n", sys_status.current_battery);
			printf("drop_rate_comm : %d%%\n", sys_status.drop_rate_comm);
			printf("errors_comm : %d\n", sys_status.errors_comm);
			printf("errors_count1 : %d\n", sys_status.errors_count1);
			printf("errors_count2 : %d\n", sys_status.errors_count2);
			printf("errors_count3 : %d\n", sys_status.errors_count3);
			printf("errors_count4 : %d\n", sys_status.errors_count4);
			printf("battery_remaining : %d%%\n", sys_status.battery_remaining);
			break;
		}
		
		case MAVLINK_MSG_ID_SYSTEM_TIME:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_GPS_RAW_INT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_RAW_IMU:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_SCALED_PRESSURE:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_ATTITUDE:
		{
			mavlink_attitude_t attitude = vehicle.attitude;
			printf("The roll : %f\n", attitude.roll);
			break;
		}
		
		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_MISSION_CURRENT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_VFR_HUD:
		{
			mavlink_vfr_hud_t vfr_hud = vehicle.vfr_hud;
			printf("VFR_HUD :\nAirspeed : %f, Groundspeed : %f, Alt : %f, Climb : %f, Heading : %d, Throttle : %d\n", vfr_hud.airspeed, vfr_hud.groundspeed, vfr_hud.alt, vfr_hud.climb, vfr_hud.heading,  vfr_hud.throttle);
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
			printf("TERRAIN_REQUEST :\nMask : %llu, Lat : %d, Lon : %d, Grid_spacing : %d\n", terrain_request.mask, terrain_request.lat, terrain_request.lon, terrain_request.grid_spacing);
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
	printf("---------------------------Main menu-----------------------\n");
	printf("1 : arm motors\n");
	printf("2 : disarm motors\n");
	printf("p : display informations\n");
	printf("c : control drone\n");
}


/**
* Display the display menu
*
*
*/
void mavlink_display_display_menu(){
	printf("---------------------------Display menu-----------------------\n");
	printf("a : display all\n");
	//...
}


/**
* Display the control menu
*
*
*/
void mavlink_display_control_menu(){
	printf("---------------------------Control menu-----------------------\n");
	printf("z : move forward\n");
	printf("s : move back\n");
	printf("q : move left\n");
	printf("d : move right\n");
	printf("i : go up\n");
	printf("k : go down\n");
	printf("j : rotate left\n");
	printf("l : rotate right\n");
	//...
}