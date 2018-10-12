#include <stdio.h>
#include <errno.h>
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

void mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle){

	//!!!!!!!!!!!!!!!!!TO FINSIH!!!!!!!!!!!!!!!!!!!!!!!!
	switch (msg.msgid) {

		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			//printf("Heartbeat update\n");
			mavlink_heartbeat_t heartbeat;
			mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			vehicle->heartbeat = heartbeat;
			break;
		}

		case MAVLINK_MSG_ID_SYS_STATUS:
		{
			//printf("Sys_status update\n");
			mavlink_sys_status_t sys_status;
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			vehicle->sys_status = sys_status;
			break;
		}
		
		case MAVLINK_MSG_ID_SYSTEM_TIME:
		{
			//printf("System_time update\n");
			mavlink_system_time_t system_time;
			mavlink_msg_system_time_decode(&msg, &system_time);
			vehicle->system_time = system_time;
			break;
		}
		
		case MAVLINK_MSG_ID_GPS_RAW_INT:
		{
			//printf("Gps_raw_int update\n");
			mavlink_gps_raw_int_t gps_raw_int;
			mavlink_msg_gps_raw_int_decode(&msg, &gps_raw_int);
			vehicle->gps_raw_int = gps_raw_int;
			break;
		}
		
		case MAVLINK_MSG_ID_RAW_IMU:
		{
			//printf("Raw_imu update\n");
			mavlink_raw_imu_t raw_imu;
			mavlink_msg_raw_imu_decode(&msg, &raw_imu);
			vehicle->raw_imu = raw_imu;
			break;
		}
		
		case MAVLINK_MSG_ID_SCALED_PRESSURE:
		{
			//printf("Scaled_pressure update\n");
			mavlink_scaled_pressure_t scaled_pressure;
			mavlink_msg_scaled_pressure_decode(&msg, &scaled_pressure);
			vehicle->scaled_pressure = scaled_pressure;
			break;
		}
		
		case MAVLINK_MSG_ID_ATTITUDE:
		{
			//printf("Attitude update\n");
			mavlink_attitude_t attitude;
			mavlink_msg_attitude_decode(&msg, &attitude);
			vehicle->attitude = attitude;
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
			//printf("Statustext update\n");
			mavlink_statustext_t statustext;
			mavlink_msg_statustext_decode(&msg, &statustext);
			vehicle->statustext = statustext;
			break;
		}
		
		default :
			printf("This is an other type of message\n");
			break;
	}
		
}

void mavlink_msg_decode_answer(mavlink_message_t msg){
	
	switch (msg.msgid) {

 

		case MAVLINK_MSG_ID_PARAM_VALUE:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_COMMAND_INT:
		{
			
			break;
		}
		
		case MAVLINK_MSG_ID_COMMAND_LONG:
		{
			
			break;
		}

		
		case MAVLINK_MSG_ID_COMMAND_ACK:
		{

			mavlink_command_ack_t cmdAck;
			mavlink_msg_command_ack_decode(&msg, &cmdAck);
			//printf("\n\nCommande :%d:%02X\nResult: %d\n\n", cmdAck.command, cmdAck.command, cmdAck.result);
			// exit(EXIT_SUCCESS);
			break;
		}

		default :
			//printf("Unknow answer\n");
			break;
	}

}
