/*******************************************************************************
Copyright (C) 2010  Bryan Godbolt godbolt ( a t ) ualberta.ca

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

****************************************************************************/
/*
This program sends some data to qgroundcontrol using the mavlink protocol.  The sent packets
cause qgroundcontrol to respond with heartbeats.  Any settings or custom commands sent from
qgroundcontrol are printed by this program along with the heartbeats.


I compiled this program sucessfully on Ubuntu 10.04 with the following command

gcc -I ../../pixhawk/mavlink/include -o udp-server udp-server-test.c

the rt library is needed for the clock_gettime on linux
*/
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

uint64_t microsSinceEpoch();
void init_mavlink_udp_connect(int* sock, struct sockaddr_in* locAddr, int local_port, struct sockaddr_in* targetAddr, char* target_ip);

int main(int argc, char* argv[])
{

	char help[] = "--help";


	char target_ip[100];
	int local_port=14550;

	//struct sockaddr_in fromAddr;
	uint8_t buf[BUFFER_LENGTH];
	ssize_t recsize;
	socklen_t fromlen;
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;
	int i = 0;
	//int success = 0;
	unsigned int temp = 0;

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

	init_mavlink_udp_connect(&sock, &locAddr, local_port, &targetAddr, target_ip);
	mavlink_channel_t chan = MAVLINK_COMM_0;

	// Sending an heartbeat : mean we are the ground control (cf. param : 255)
	mavlink_msg_heartbeat_pack(255,0,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_INVALID,MAV_MODE_MANUAL_ARMED,0x0,MAV_STATE_ACTIVE);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending data stream");
		exit(EXIT_FAILURE);
	}

	// Request param list : expected a MAVLINK_MSG_ID_PARAM_VALUE
	mavlink_msg_param_request_list_pack(255,0,&msg,1,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending data stream");
		exit(EXIT_FAILURE);
	}


	for (;;)
	{
		memset(buf, 0, BUFFER_LENGTH);

		recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&targetAddr, &fromlen);
		if (recsize > 0)
		{
			// Something received - print out all bytes and parse packet
			mavlink_message_t msg;
			mavlink_status_t status;

			printf("Bytes Received: %d\nDatagram: ", (int)recsize);
			for (i = 0; i < recsize; ++i)
			{
				temp = buf[i];
				printf("%02x ", (unsigned char)temp);
				if (mavlink_parse_char(chan, buf[i], &msg, &status))
				{
					// Packet received
					printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
					if (msg.msgid == 22) {
						printf("PARAM REQUEST RESPONSE RECEIVED : SUCCESS\n");
						close(sock);
						exit(EXIT_SUCCESS);
					}
					// mavlink_msg_decode(msg);
				}
			}
			printf("\n");
		}
		sleep(1); // Sleep one second
	}
	close(sock);
}


/* QNX timer version */
#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t microsSinceEpoch()
{

	struct timespec time;

	uint64_t micros = 0;

	clock_gettime(CLOCK_REALTIME, &time);
	micros = (uint64_t)time.tv_sec * 1000000 + time.tv_nsec/1000;

	return micros;
}
#else
uint64_t microsSinceEpoch()
{

	struct timeval tv;

	uint64_t micros = 0;

	gettimeofday(&tv, NULL);
	micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;

	return micros;
}

void init_mavlink_udp_connect(int* sock, struct sockaddr_in* locAddr, int local_port, struct sockaddr_in* targetAddr, char* target_ip)
{
	*sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(locAddr, 0, sizeof(*locAddr));
	locAddr->sin_family = AF_INET;
	locAddr->sin_addr.s_addr = INADDR_ANY;
	locAddr->sin_port = htons(local_port);

	if (-1 == bind(*sock,(struct sockaddr *)locAddr, sizeof(struct sockaddr)))
	{
		perror("error bind failed");
		close(*sock);
		exit(EXIT_FAILURE);
	}
	printf("INIT listenning :\nUdpin: 0.0.0.0:%d\n", ntohs(locAddr->sin_port));
	/* Attempt to make it non blocking */
	#if (defined __QNX__) | (defined __QNXNTO__)
	if (fcntl(*sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
	#else
	if (fcntl(*sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
	#endif

	{
		fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
		close(*sock);
		exit(EXIT_FAILURE);
	}

	char buf[256];
	memset(buf,0,256);
	struct sockaddr_in possibleTarget;
  socklen_t possibleTargetLen = sizeof(possibleTarget);
	while (recvfrom(*sock, buf, sizeof(buf), 0, (struct sockaddr*)(&possibleTarget), &possibleTargetLen)<=0
				|| possibleTarget.sin_addr.s_addr != inet_addr(target_ip)) {
		memset(buf,0,256);
	}

	memset(targetAddr, 0, sizeof(*targetAddr));
	targetAddr->sin_family = AF_INET;
	targetAddr->sin_addr.s_addr = inet_addr(target_ip);
	targetAddr->sin_port = possibleTarget.sin_port;

	printf("INIT target :\nUdpout: %s:%d\n",target_ip,ntohs(targetAddr->sin_port));
	return;
}

#endif
