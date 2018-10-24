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

char* mavlink_enum_to_string(MAV_ENUM enumType, int value)
{
	switch(enumType)
	{
		case ENUM_MAV_CMD_ACK:
			switch(value)
			{
				case 0:
					return "CMD_ACK value 0";
				case 1:
					return "MAV_CMD_ACK_OK";
				case 2:
					return "MAV_CMD_ACK_ERR_FAIL";
				case 3:
					return "MAV_CMD_ACK_ERR_ACCESS_DENIED";
				case 4:
					return "MAV_CMD_ACK_ERR_NOT_SUPPORTED";
				case 5:
					return "MAV_CMD_ACK_ERR_COORDINATE_FRAME_NOT_SUPPORTED";
				case 6:
					return "MAV_CMD_ACK_ERR_COORDINATES_OUT_OF_RANGE";
				case 7:
					return "MAV_CMD_ACK_ERR_X_LAT_OUT_OF_RANGE";
				case 8:
					return "MAV_CMD_ACK_ERR_Y_LON_OUT_OF_RANGE";
				case 9:
					return "MAV_CMD_ACK_ERR_Z_ALT_OUT_OF_RANGE";
				case 10:
					return "MAV_CMD_ACK_ENUM_END";
				default:
					return "UNKNOWN_MAV_CMD_ACK";
			}
		case ENUM_MAV_CMD:
			switch(value)
			{
				case 16:
					return "MAV_CMD_NAV_WAYPOINT";
				case 21:
					return "MAV_CMD_NAV_LAND";
				case 22:
					return "MAV_CMD_NAV_TAKEOFF";
				case 23:
					return "MAV_CMD_NAV_LAND_LOCAL";
				case 24:
					return "MAV_CMD_NAV_TAKEOFF_LOCAL";
				case 30:
					return "MAV_CMD_NAV_CONTINUE_AND_CHANGE_ALT";
				case 176:
					return "MAV_CMD_DO_SET_MODE";
				case 186:
					return "MAV_CMD_DO_CHANGE_ALTITUDE";
				case 400:
					return "MAV_CMD_COMPONENT_ARM_DISARM";
				case 519:
					return "MAV_CMD_REQUEST_PROTOCOL_VERSION";
				case 3001:
					return "MAV_CMD_ARM_AUTHORIZATION_REQUEST";
				default:
					return "OTHER TYPE OF MAV_CMD";
			}
		default:
			return "Unknow type";
	}
}

/**
* Decode broadcast messages and update the corresponding parameter of the vehicle
*
* return 0 if the message has been identified and decoded, else -1
*/
int mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle){

	vehicle->system_ids.sysid = msg.sysid;
	vehicle->system_ids.compid = msg.compid;
	switch (msg.msgid) {

		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			//printf("Heartbeat update\n");
			mavlink_heartbeat_t heartbeat;
			mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			vehicle->heartbeat = heartbeat;
			return 0;
		}

		case MAVLINK_MSG_ID_SYS_STATUS:
		{
			//printf("Sys_status update\n");
			mavlink_sys_status_t sys_status;
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			vehicle->sys_status = sys_status;
			return 0;
		}

		case MAVLINK_MSG_ID_SYSTEM_TIME:
		{
			//printf("System_time update\n");
			mavlink_system_time_t system_time;
			mavlink_msg_system_time_decode(&msg, &system_time);
			vehicle->system_time = system_time;
			return 0;
		}

		case MAVLINK_MSG_ID_GPS_RAW_INT:
		{
			//printf("Gps_raw_int update\n");
			mavlink_gps_raw_int_t gps_raw_int;
			mavlink_msg_gps_raw_int_decode(&msg, &gps_raw_int);
			vehicle->gps_raw_int = gps_raw_int;
			return 0;
		}

		case MAVLINK_MSG_ID_RAW_IMU:
		{
			//printf("Raw_imu update\n");
			mavlink_raw_imu_t raw_imu;
			mavlink_msg_raw_imu_decode(&msg, &raw_imu);
			vehicle->raw_imu = raw_imu;
			return 0;
		}

		case MAVLINK_MSG_ID_SCALED_PRESSURE:
		{
			//printf("Scaled_pressure update\n");
			mavlink_scaled_pressure_t scaled_pressure;
			mavlink_msg_scaled_pressure_decode(&msg, &scaled_pressure);
			vehicle->scaled_pressure = scaled_pressure;
			return 0;
		}

		case MAVLINK_MSG_ID_ATTITUDE:
		{
			//printf("Attitude update\n");
			mavlink_attitude_t attitude;
			mavlink_msg_attitude_decode(&msg, &attitude);
			vehicle->attitude = attitude;
			return 0;
		}

		case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
		{
			//printf("Global_position_int update\n");
			mavlink_global_position_int_t global_position_int;
			mavlink_msg_global_position_int_decode(&msg, &global_position_int);
			vehicle->global_position_int = global_position_int;
			return 0;
		}

		case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
		{
			//printf("Rc_channels_raw update\n");
			mavlink_rc_channels_raw_t rc_channels_raw;
			mavlink_msg_rc_channels_raw_decode(&msg, &rc_channels_raw);
			vehicle->rc_channels_raw = rc_channels_raw;
			return 0;
		}

		case MAVLINK_MSG_ID_SERVO_OUTPUT_RAW:
		{
			//printf("Servo_output_raw update\n");
			mavlink_servo_output_raw_t servo_output_raw;
			mavlink_msg_servo_output_raw_decode(&msg, &servo_output_raw);
			vehicle->servo_output_raw = servo_output_raw;
			return 0;
		}

		case MAVLINK_MSG_ID_MISSION_CURRENT:
		{
			//printf("Mission_current update\n");
			mavlink_mission_current_t mission_current;
			mavlink_msg_mission_current_decode(&msg, &mission_current);
			vehicle->mission_current = mission_current;
			return 0;
		}

		case MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT:
		{
			//printf("Nav_controller_output update\n");
			mavlink_nav_controller_output_t nav_controller_output;
			mavlink_msg_nav_controller_output_decode(&msg, &nav_controller_output);
			vehicle->nav_controller_output = nav_controller_output;
			return 0;
		}

		case MAVLINK_MSG_ID_VFR_HUD:
		{
			//printf("Vfr_hud update\n");
			mavlink_vfr_hud_t vfr_hud;
			mavlink_msg_vfr_hud_decode(&msg, &vfr_hud);
			vehicle->vfr_hud = vfr_hud;
			return 0;
		}

		case MAVLINK_MSG_ID_RADIO_STATUS:
		{
			//printf("Radio_status update\n");
			mavlink_radio_status_t radio_status;
			mavlink_msg_radio_status_decode(&msg, &radio_status);
			vehicle->radio_status = radio_status;
			return 0;
		}

		case MAVLINK_MSG_ID_SCALED_IMU2:
		{
			//printf("Scaled_imu2 update\n");
			mavlink_scaled_imu2_t scaled_imu2;
			mavlink_msg_scaled_imu2_decode(&msg, &scaled_imu2);
			vehicle->scaled_imu2 = scaled_imu2;
			return 0;
		}

		case MAVLINK_MSG_ID_POWER_STATUS:
		{
			//printf("Power_status update\n");
			mavlink_power_status_t power_status;
			mavlink_msg_power_status_decode(&msg, &power_status);
			vehicle->power_status = power_status;
			return 0;
		}

		case MAVLINK_MSG_ID_SCALED_IMU3:
		{
			//printf("Scaled_imu3 update\n");
			mavlink_scaled_imu3_t scaled_imu3;
			mavlink_msg_scaled_imu3_decode(&msg, &scaled_imu3);
			vehicle->scaled_imu3 = scaled_imu3;
			return 0;
		}

		case MAVLINK_MSG_ID_TERRAIN_REQUEST:
		{
			//printf("Terrain_request update\n");
			mavlink_terrain_request_t terrain_request;
			mavlink_msg_terrain_request_decode(&msg, &terrain_request);
			vehicle->terrain_request = terrain_request;
			return 0;
		}

		case MAVLINK_MSG_ID_TERRAIN_REPORT:
		{
			//printf("Terrain_report update\n");
			mavlink_terrain_report_t terrain_report;
			mavlink_msg_terrain_report_decode(&msg, &terrain_report);
			vehicle->terrain_report = terrain_report;
			return 0;
		}

		case MAVLINK_MSG_ID_SCALED_PRESSURE2:
		{
			//printf("Scaled_pressure2 update\n");
			mavlink_scaled_pressure2_t scaled_pressure2;
			mavlink_msg_scaled_pressure2_decode(&msg, &scaled_pressure2);
			vehicle->scaled_pressure2 = scaled_pressure2;
			return 0;
		}

		case MAVLINK_MSG_ID_NAMED_VALUE_INT:
		{
			//printf("Named_value_int update\n");
			mavlink_named_value_int_t named_value_int;
			mavlink_msg_named_value_int_decode(&msg, &named_value_int);
			vehicle->named_value_int = named_value_int;
			return 0;
		}

		case MAVLINK_MSG_ID_STATUSTEXT:
		{
			//printf("Statustext update\n");
			mavlink_statustext_t statustext;
			mavlink_msg_statustext_decode(&msg, &statustext);
			vehicle->statustext = statustext;
			return 0;
		}

		default :
			//printf("This is not a broadcast message\n");
			return -1;
	}
}


/**
* Decode a answer message and print informations of it
*
*/
void mavlink_msg_decode_answer(mavlink_message_t msg){
	switch (msg.msgid) {

		case MAVLINK_MSG_ID_PARAM_VALUE:
		{
			mavlink_param_value_t param_value;
			mavlink_msg_param_value_decode(&msg, &param_value);
			//printf("Param_value : %f, param_count : %d, param_index : %d, param_id : %s, param_type : %d\n", param_value.param_value, param_value.param_count, param_value.param_index, param_value.param_id, param_value.param_type);
			break;
		}

		case MAVLINK_MSG_ID_COMMAND_INT:
		{
			mavlink_command_int_t command_int;
			mavlink_msg_command_int_decode(&msg, &command_int);
			//printf("Param1 : %f, param2 : %f, param3 : %f, param4 : %f, x : %d, y : %d, z : %f, command : %d:%02X, target_system : %d, target_component : %d, frame : %d, current : %d, autocontinue : %d\n", command_int.param1, command_int.param2, command_int.param3, command_int.param4, command_int.x, command_int.y, command_int.z, command_int.command, command_int.command, command_int.target_system, command_int.target_component, command_int.frame, command_int.current, command_int.autocontinue);
			break;
		}

		case MAVLINK_MSG_ID_COMMAND_LONG:
		{
			mavlink_command_long_t command_long;
			mavlink_msg_command_long_decode(&msg, &command_long);
			//printf("Param1 : %f, param2 : %f, param3 : %f, param4 : %f, param5 : %f, param6 : %f, param7 : %f, command : %d:%02X, target_system : %d, target_component : %d, confirmation : %d\n", command_long.param1, command_long.param2, command_long.param3, command_long.param4,  command_long.param5,  command_long.param6,  command_long.param7, command_long.command, command_long.command, command_long.target_system, command_long.target_component, command_long.confirmation);
			break;
		}


		case MAVLINK_MSG_ID_COMMAND_ACK:
		{
			mavlink_command_ack_t command_ack;
			mavlink_msg_command_ack_decode(&msg, &command_ack);
			printf("\n\nCommand : %d:%02X:%s, result: %d:%s\n", command_ack.command, command_ack.command, mavlink_enum_to_string(ENUM_MAV_CMD, command_ack.command), command_ack.result, mavlink_enum_to_string(ENUM_MAV_CMD_ACK, command_ack.result));
			break;
		}

		default :
			//printf("Unknow answer\n");
			break;
	}

}
