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
	
	switch (msg.msgid) {
		
		case MAVLINK_MSG_ID_HEARTBEAT:
		{
			mavlink_heartbeat_t heartbeat;
			mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			printf("This is a heartbeat of type : %d\n", heartbeat.type);
			break;
		}
		
		case MAVLINK_MSG_ID_SYS_STATUS:
		{
			mavlink_sys_status_t sys_status;
			mavlink_msg_sys_status_decode(&msg, &sys_status);
			printf("Battery %d %%\n", sys_status.battery_remaining);
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
			
			
			
			
			
		default :
			printf("this is an other type of message\n");
	}
	
}