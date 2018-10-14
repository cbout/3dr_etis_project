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
			
			break;
		}
		
		case MAVLINK_MSG_ID_RADIO_STATUS:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_SCALED_IMU2:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_POWER_STATUS:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_SCALED_IMU3:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_TERRAIN_REQUEST:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_TERRAIN_REPORT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_SCALED_PRESSURE2:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_NAMED_VALUE_INT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_STATUSTEXT:
		{
			mavlink_statustext_t statustext = vehicle.statustext;
			printf("Severity :%d\n Text: %s\n", statustext.severity, statustext.text);
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