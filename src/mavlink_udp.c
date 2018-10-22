/* These headers are for QNX, but should all be standard on unix/linux */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>
#if (defined __QNX__) | (defined __QNXNTO__)
/* QNX specific headers */
#include <unix.h>
#else
/* Linux / MacOS POSIX timer headers */
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdbool.h> /* required for the definition of bool in C99 */
#endif

/* This assumes you have the mavlink headers on your include path
or in the same folder as this source file */
#include <mavlink.h>
#include "mavlink_perso_lib.h"

#define BUFFER_LENGTH 2041 // minimum buffer size that can be used with qnx (I don't know why)


/**
* Main
*
*
*/
int main(int argc, char* argv[])
{

	char help[] = "--help";


	char target_ip[100];
	int local_port=14550;

	//Struct of the vehicle
	Vehicle vehicle;

	//struct sockaddr_in fromAddr;
	uint8_t buf[BUFFER_LENGTH];
	ssize_t recsize;
	socklen_t fromlen;
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;
	int i = 0;

	// Check if --help flag was used
	if ((argc == 2) && (strcmp(argv[1], help) == 0))
	{
		printf("\n");
		printf("\tUsage:\n\n");
		printf("\t");
		printf("%s", argv[0]);
		printf(" <ip address of QGroundControl> [<Listening port>]\n");
		printf("\tDefault for localhost: udp-server 10.1.1.1, it refer to 3DR controller\n\n");
		exit(EXIT_FAILURE);
	}


	// Change the target ip if parameter was given
	strcpy(target_ip, "10.1.1.1");
	if (argc == 2)
	{
		strcpy(target_ip, argv[1]);
	}
	else if (argc == 3)
	{
		strcpy(target_ip, argv[1]);
		local_port = atoi(argv[2]);
	}

	int sock;
	struct sockaddr_in targetAddr;
	struct sockaddr_in locAddr;

	mavlink_system_t localSysId;
	localSysId.sysid = 255;
	localSysId.compid = 0;
	mavlink_system_t targetSysId;
	targetSysId.sysid = 1;
	targetSysId.compid = 0;
	//Connection
	if (init_mavlink_udp_connect(&sock, &locAddr, local_port, &targetAddr, target_ip, 100) == -1) {
		perror("init failed");
	};

	mavlink_channel_t chan = MAVLINK_COMM_0;

	//Initialization order
	// Sending an heartbeat : mean we are the ground control (cf. param : 255)
	mavlink_msg_heartbeat_pack(255,0,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_INVALID,MAV_MODE_MANUAL_ARMED,0x0,MAV_STATE_ACTIVE);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending Heartbeat");
		exit(EXIT_FAILURE);
	}
	memset(buf, 0, BUFFER_LENGTH);

	// Request param list : expected a MAVLINK_MSG_ID_PARAM_VALUE
	mavlink_msg_param_request_list_pack(255,0,&msg,1,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending param list");
		exit(EXIT_FAILURE);
	}
	memset(buf, 0, BUFFER_LENGTH);

	// Request protocol version : expected COMMAND_ACK
	mavlink_msg_command_long_pack(255,0,&msg,1,0,MAV_CMD_REQUEST_PROTOCOL_VERSION,4,1,0,0,0,0,0,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending data stream");
		exit(EXIT_FAILURE);
	}
	memset(buf, 0, BUFFER_LENGTH);
	//End initialization order


	//Process
	for (;;)
	{

		//Receiving message
		recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&targetAddr, &fromlen);
		if (recsize > 0)
		{
			// Something received
			mavlink_message_t msg;
			mavlink_status_t status;

			for (i = 0; i < recsize; ++i)
			{
				if (mavlink_parse_char(chan, buf[i], &msg, &status))
				{
					// Packet received
					//printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
					//Broadcast message
					if(mavlink_msg_decode_broadcast(msg, &vehicle)==-1){
						//If this is not a broadcast message
						mavlink_msg_decode_answer(msg);
					}
				}
			}
		}


		//Sending message
		int order;
		do{
			printf("Temporary menu : \n");
			printf("1 : arm motors\n");
			printf("2 : disarm motors\n");
			scanf("%d", &order);
		}

		while(mavlink_msg_order(order, localSysId, targetSysId, &msg)==-1);

		len = mavlink_msg_to_send_buffer(buf, &msg);
		bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
		if (bytes_sent==-1) {
			perror("Sending data stream");
			exit(EXIT_FAILURE);
		}

		memset(buf, 0, BUFFER_LENGTH);

		sleep(1); // Sleep one second
	}


	close(sock);
	exit(EXIT_SUCCESS);
}
