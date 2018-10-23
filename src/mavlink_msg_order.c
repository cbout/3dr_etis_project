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
#include "mavlink_perso_lib.h"

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
		
		//Test
		case '3':
		{
			// Request test armed : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_DO_SET_MODE, 0, MAV_MODE_MANUAL_ARMED, 0, 0, 0, 0, 0,0);
			return 0;
		}
		
		//TO DO add mavlink command
		case 'z':
		{
			// Request move forward
			
			return 0;
		}
		
		case 's':
		{
			// Request move back
			
			return 0;
		}
		
		case 'q':
		{
			// Request move left
			
			return 0;
		}
		
		case 'd':
		{
			// Request move right
			
			return 0;
		}
		
		case 'i':
		{
			// Request go up
			
			return 0;
		}
		
		case 'k':
		{
			// Request go down
			
			return 0;
		}
		
		case 'j':
		{
			// Request rotate left
			
			return 0;
		}
		
		case 'l':
		{
			// Request rotate right
			
			return 0;
		}
		
		
		//...

		default :
			//printf("Incorrect order\n");
			return -1;
	}

}


int mavlink_display_order(char order, Vehicle vehicle){

	//!!!!!!!!!!!! To complete!!!!!!!!!!!!!!
	switch (order) {

		case 'a':
		{
			// Order to display all informations of the vehicule
			mavlink_display_info_vehicle_all(vehicle);
			return 0;
		}
		
		//... others displays

		default :
			//printf("Incorrect order\n");
			return -1;
	}

}
