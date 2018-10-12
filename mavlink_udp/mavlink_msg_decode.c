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

void mavlink_msg_decode(mavlink_message_t msg){

	//!!!!!!!!!!!!!!!!!TO FINSIH!!!!!!!!!!!!!!!!!!!!!!!!
	switch (msg.msgid) {

		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			mavlink_heartbeat_t heartbeat;
			mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			printf("MavLink heartbeat answer :\n");
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
			mavlink_sys_status_t sys_status;
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			printf("MavLink system status answer :\n");
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

		case MAVLINK_MSG_ID_LOCAL_POSITION_NED_COV:
		{
			mavlink_local_position_ned_cov_t local_position_ned_cov;
			mavlink_msg_local_position_ned_cov_decode(&msg, &local_position_ned_cov);
			printf("Position x : %f, y : %f, z : %f; Speed x : %f, y : %f, z : %f; Acceleration x : %f, y : %f, z : %f;\n", local_position_ned_cov.x, local_position_ned_cov.y, local_position_ned_cov.z, local_position_ned_cov.vx, local_position_ned_cov.vy, local_position_ned_cov.vz, local_position_ned_cov.ax, local_position_ned_cov.ay, local_position_ned_cov.az);
			break;
		}

		case MAVLINK_MSG_ID_ATTITUDE:
		{
			mavlink_attitude_t attitude;
			mavlink_msg_attitude_decode(&msg, &attitude);
			printf("This is a atitude of roll : %f\n", attitude.roll);
			break;
		}

		case MAVLINK_MSG_ID_MANUAL_CONTROL:
		{
			mavlink_manual_control_t manual_control;
			mavlink_msg_manual_control_decode(&msg, &manual_control);
			printf("x : %d, y : %d, z %d, r : %d\n", manual_control.x, manual_control.y, manual_control.z, manual_control.r);
			break;
		}

		case MAVLINK_MSG_ID_STATUSTEXT:
		{
			mavlink_statustext_t statustext;
			mavlink_msg_statustext_decode(&msg, &statustext);
			printf("Severity :%d\nText: %s\n", statustext.severity, statustext.text);
			// exit(EXIT_SUCCESS);
			break;
		}
		//...
		case MAVLINK_MSG_ID_COMMAND_ACK:
		{

				mavlink_command_ack_t cmdAck;
				mavlink_msg_command_ack_decode(&msg, &cmdAck);
				printf("\n\nCommande :%d:%02X\nResult: %d\n\n", cmdAck.command, cmdAck.command, cmdAck.result);
				// exit(EXIT_SUCCESS);
				break;
		}

		default :
			printf("This is an other type of message\n");
			break;
	}

}
