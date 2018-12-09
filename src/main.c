/**********************************************************************************************************************************************************
 Copyright  ETIS — ENSEA, Université de Cergy-Pontoise, CNRS (1991-2018)
 promethe@ensea.fr


 Short program to receive video stream data from the solo 3DR drone and to send and receive Mavlink messages with the solo 3DR.
 This program is an entry to understand how to make a mavlink communication program.
 To do that used the c_library_v1, that can be download here : https://github.com/mavlink/c_library_v1.
 We also make a little tutorial of Mavlink here : https://github.com/cbout/MAVLink_C_example.

 This software is governed by the CeCILL v2.1 license under French law and abiding by the rules of distribution of free software.
 You can use, modify and/ or redistribute the software under the terms of the CeCILL v2.1 license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
 As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license,
 users are provided only with a limited warranty and the software's author, the holder of the economic rights,  and the successive licensors have only limited liability.
 In this respect, the user's attention is drawn to the risks associated with loading, using, modifying and/or developing or reproducing the software by the user in light of its specific status of free software,
 that may mean  that it is complicated to manipulate, and that also therefore means that it is reserved for developers and experienced professionals having in-depth computer knowledge.
 Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured
 and, more generally, to use and operate it in the same conditions as regards security.
 The fact that you are presently reading this means that you have had knowledge of the CeCILL v2.1 license and that you accept its terms.
 
 Compilation : 
 make all
 
 Information :
 ./mavlink_udp --help
 UDP execution :
 ./mavlink_udp --udp
 UART execution :
 ./mavlink_udp --uart
**********************************************************************************************************************************************************/
/*********************************************************************************************************************************************************
 Authors: Raphael Bergoin, Clement Bout
 Created: 10/2018
**********************************************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>


/* This assumes you have the mavlink headers on your include path
or in the same folder as this source file */
#include <mavlink.h>
#include "mavlink_display.h"
#include "mavlink_connect_manager.h"
#include "mavlink_msg_decode.h"
#include "mavlink_msg_order.h"
#include "mavlink_thread.h"
#include "serial.h"
/* This assumes you have the GStreamer headers on your include path
or in the same folder as this source file */
#include <gst/gst.h>

/**
 * @brief      Display the use of the prog
 *
 * @param[in]  argc  The argc
 * @param      argv  The argv
 */
void menu(int argc, char*argv [])
{
	char help[] = "--help";

	// Check if --help flag was used
	if ((argc == 2) && (strcmp(argv[1], help) == 0))
	{
		printf("\n");
		printf("\tUsage:\n\n");
		printf("\t");
		printf("%s", argv[0]);
		printf(" --udp [--target-ip <Target's IP>] [--local-port <Listening port>] [--video-ip <Video serveur IP>] [--target-video-port <Video stream port>]\n");
		printf("\tDefault :\n\tLocal:0.0.0.0:14550\n\tTarget:10.1.1.1\n\tVideo:10.1.1.1:5502\n\n");
		printf("\t");
		printf("%s", argv[0]);
		printf(" --uart [-P <Port>] [-B <baud>]\n");
		printf("\tDefault :\n\tPort:/dev/ttyACM0\n\tBaud:57600\n");
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief      Init the connection and all the variable needed to connect and
 *             communicate
 *
 * @param[in]  argc                 The argc
 * @param      argv                 The argv
 * @param      targetAddr           The target address
 * @param      locAddr              The location address
 * @param      servAddr             The serv address
 * @param      discuss_socket       The discuss socket
 * @param      video_socket         The video socket
 * @param      video_stream_enable  The video stream enable (0 if connection failed, 1 otherwise)
 */
void init_connection(int argc, char* argv [], struct sockaddr_in* targetAddr, struct sockaddr_in* locAddr, struct sockaddr_in* servAddr, int* discuss_socket, int* video_socket, int* video_stream_enable)
{
	int rep;
	char target_ip[100];
	int local_port;
	char video_target_ip[100];
	int target_video_port;

	/*--Default settings for Solo 3dr--*/
	strcpy(target_ip, "10.1.1.1");
	local_port = 14550;
	strcpy(video_target_ip, "10.1.1.1");
	target_video_port = 5502;
	int i;

	/* Parsing arguments */
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "--target-ip") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				strcpy(target_ip, argv[i+1]);
			}
		}
		else if (strcmp(argv[i], "--local-port") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				local_port = atoi(argv[i+1]);
			}
		}
		else if (strcmp(argv[i], "--video-ip") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				strcpy(video_target_ip, argv[i+1]);
			}
		}
		else if (strcmp(argv[i], "--target-video-port") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				target_video_port = atoi(argv[i+1]);
			}
		}
	}

	/*----- Setting and Starting UDP Connection -----*/

	// Check if connection is valid
	rep = init_mavlink_udp_connect(discuss_socket, locAddr, local_port, targetAddr, target_ip, 10);
	if (rep == -1)
	{
		fprintf(stderr, "%s\n", "Init UDP connection failed");
		exit(EXIT_FAILURE);
	}

	// Check if video stream is valid
	rep = init_solo_3dr_video_stream_connect(video_socket, servAddr, target_video_port, video_target_ip);
	if (rep == -1)
	{
		fprintf(stderr, "%s\n", "Video connection failed");
		*video_stream_enable = 0;
	}

	return;
}

int run_udp(int argc, char* argv[])
{
	/*----- Variables declaration -----*/
	int run = 1;

	// Connection variables
	struct sockaddr_in targetAddr;
	struct sockaddr_in locAddr;
	struct sockaddr_in servAddr;

	int discuss_socket;
	int video_socket;
	
	int video_stream_enable = 1;
	
	init_connection(argc, argv, &targetAddr, &locAddr, &servAddr, &discuss_socket, &video_socket, &video_stream_enable);

	//Mutex to protect vehicle_t
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	mavlink_thread_arg_udp_t thread_arguments;
	pthread_t myThreadReciving;
	pthread_t myThreadHeartbeatPing;
	pthread_t myThreadSending;
	


	/*----- Setting Threads -----*/

    // Setting Thread arguments
	thread_arguments.mutex = mutex;
	thread_arguments.sock = discuss_socket;
	thread_arguments.locAddr = locAddr;
	thread_arguments.targetAddr = targetAddr;
	thread_arguments.run = run;

	// Init mutex for vehicle
	if (pthread_mutex_init(&thread_arguments.mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	/*----- Start Threads -----*/

	pthread_create (&myThreadReciving, NULL, threadReciving, (void*)&thread_arguments);
	pthread_create (&myThreadSending, NULL, threadSending, (void*)&thread_arguments);
	pthread_create (&myThreadHeartbeatPing, NULL, threadHeartbeatPing, (void*)&thread_arguments);
	
	/*----- Start Video stream -----*/

	if (video_stream_enable)
	{
		//Create and wait video stream receiver
		goProVideoStream (&thread_arguments);
	}

	/*----- Wait end of the program -----*/

	pthread_join (myThreadReciving, NULL);
	pthread_join (myThreadSending, NULL);
	pthread_join (myThreadHeartbeatPing, NULL);
	

	close(discuss_socket);
	close(video_socket);
	return 1;
}

int init_uart(int argc, char* argv[])
{
	/* Default setting */
	char* port = "/dev/ttyACM0";
	int baud = 57600;
	int fd, state;
	int i;

	/* Setting UART connection */
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-P") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				strcpy(port, argv[i+1]);
			}
		} else if (strcmp(argv[i], "-B") == 0)
		{
			if (i+1 >= argc)
			{
				fprintf(stderr, "%s\n", "Invalid arguments");
				exit(EXIT_FAILURE);
			}
			else
			{
				baud = atoi(argv[i+1]);
			}
		}
	}

	/* Openning and setting file descriptor (see serial.c) */
	open_serial(&fd, port, baud, &state);

	if (fd == -1)
	{
		perror(port);
		exit(EXIT_FAILURE);
	}
	return fd;
}

int run_uart(int argc, char* argv[])
{
	/* Init connection */
	int fd = init_uart(argc, argv);

	/* Init variables */
	uint8_t buf[BUFFER_LENGTH];
	memset(buf, 0, BUFFER_LENGTH * sizeof(char));
	int count = 0;

	ssize_t recsize;
	mavlink_message_t msg;
	int bytes_sent;
	uint16_t len;
	
	mavlink_system_t localSysId;
	localSysId.sysid = 255;
	localSysId.compid = 0;

	/* Example of sending by UART */
	mavlink_msg_heartbeat_pack(localSysId.sysid,localSysId.compid,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_ARDUPILOTMEGA,0xc0,0x0,MAV_STATE_ACTIVE);
	len = mavlink_msg_to_send_buffer(buf, &msg);
	bytes_sent = write(fd, (void*) buf, len);
	if (bytes_sent==-1) {
		perror("Sending Heartbeat in thread");
		exit(EXIT_FAILURE);
	}

	/* Exemple of receiving by UART */
	while(count < 25)
	{
		recsize = read_message(&msg, fd);
		if (recsize)
		{
			count++;
			printf("Received packet: SYS: %d, COMP: %d, PAYLOAD LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);
		}
	}
	printf("\n");
	return 1;
}

int main(int argc, char* argv[])
{
	// Print help menu if asked
	menu(argc, argv);

	/*----- Main option parsing -----*/
	// Case : missing --udp or --uart
	if (argc == 1)
	{
		fprintf(stderr, "Unvalid args, see: %s --help for more details\n", argv[0]);
	}
	// If udp asked then start as UDP
	else if (strcmp(argv[1], "--udp") == 0)
	{
		run_udp(argc, argv);
	}
	// If uart asked then start as UART
	else if (strcmp(argv[1], "--uart") == 0)
	{
		run_uart(argc, argv);
	}
	else
	{
		fprintf(stderr, "Unvalid args, see: %s --help for more details\n", argv[0]);
	}

	/* Programm finished */	
	exit(EXIT_SUCCESS);
}