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

int mavlink_msg_order(char order, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg){

	//!!!!!!!!!!!! To complete!!!!!!!!!!!!!!
	switch (order) {

		case '1' :
		{
			// Request arm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 0, 0, 0, 0, 0, 0);

			return 0;
		}

		case '2' :
		{
			// Request disarm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_COMPONENT_ARM_DISARM, 0, 0, 0, 0, 0, 0, 0, 0);

			return 0;
		}

		case '3':
		{
			// Request test armed : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_MANUAL_ARMED, 0, 0, 0, 0, 0,0);
			return 0;
		}
		//...

		default :
			//printf("Incorrect order\n");
			return -1;
	}

}
