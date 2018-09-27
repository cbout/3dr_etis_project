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

int mavlink_msg_pack(int rep, mavlink_message_t *msg){
		
				
	switch (rep) {
		
		case 1 :
		{
			/*Send Heartbeat */
			mavlink_msg_heartbeat_pack(1, 200, msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
			return 0;
		}
			
		case 2 :
		{
			/* Send Status */
			mavlink_msg_sys_status_pack(1, 200, msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
			return 0;
		}
			
		case 3 :
		{
			/* Send Local Position */
			float position[6] = {};
			mavlink_msg_local_position_ned_pack(1, 200, msg, 0, position[0], position[1], position[2], position[3], position[4], position[5]);
			return 0;
		}
			
		case 4 :
		{
			/* Send attitude */
			mavlink_msg_attitude_pack(1, 200, msg, 0, 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
			return 0;
		}
			
		default :
			printf("incorrect order\n");
			return -1;
	}
	
}