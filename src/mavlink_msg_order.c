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

int mavlink_msg_order(int order, mavlink_message_t *msg){

	//!!!!!!!!!!!! To complete!!!!!!!!!!!!!!
	switch (order) {

		case 1 :
		{
			// Request arm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(255, 0, msg, 1, 0, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 0, 0, 0, 0, 0, 0);
			
			return 0;
		}

		case 2 :
		{
			// Request disarm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(255, 0, msg, 1, 0, MAV_CMD_COMPONENT_ARM_DISARM, 0, 0, 0, 0, 0, 0, 0, 0);
			
			return 0;
		}
		
		//...
		
		default :
			//printf("Incorrect order\n");
			return -1;
	}

}
