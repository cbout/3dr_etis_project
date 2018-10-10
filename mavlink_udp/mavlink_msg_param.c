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

int mavlink_msg_param(int rep, char *param){

	//!!!!!!!!!!!!!!!!!!!TO DO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	switch (rep) {

		case 1 :
		{
			/*Send Heartbeat */
			param="MAVLINK_MSG_ID_HEARTBEAT";
			return 0;
		}

		case 2 :
		{
			/* Send Status */
			param="SR0_EXT_STAT";
			return 0;
		}

		case 3 :
		{
			/* Send Local Position */
			param="SR0_POSITION";
			return 0;
		}

		case 4 :
		{
			/* Send attitude */
			param="";
			return 0;
		}

		case 5 :
		{
			/* Send camera image */
			param="";
			return 0;
		}

		case 6 :
		{
			/* Send manual control */
			param="";
			return 0;
		}
		//...
		default :
			printf("incorrect order\n");
			return -1;
	}

}
