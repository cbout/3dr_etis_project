/* These headers are for QNX, but should all be standard on unix/linux */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>
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
#include "./include/ardupilotmega/mavlink.h"
#include "mavlink_perso_lib.h"

/* This assumes you have the GStreamer headers on your include path
or in the same folder as this source file */
#include <gst/gst.h>


#define BUFFER_LENGTH 2041

//Mutex to protect vehicle
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Struct of the vehicle
Vehicle vehicle;

//Connect
int sock;
struct sockaddr_in targetAddr;
struct sockaddr_in locAddr;

//The prog is running
int run = 1;

//Loop of the video stream
GMainLoop *loop;


/**
 * @brief      Main
 *
 * @param][in]      argc        number of argement
 * @param [in]     argv        help and port
 *
 * @return     0
 */
int main(int argc, char* argv[])
{

	char help[] = "--help";


	char target_ip[100];
	int local_port=14550;


	//struct sockaddr_in fromAddr;
	uint8_t buf[BUFFER_LENGTH];
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;

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


	//Connection
	int rep = init_mavlink_udp_connect(&sock, &locAddr, local_port, &targetAddr, target_ip, 10);
	if (rep == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}

	//Initialization order
	// Sending an heartbeat : mean we are the ground control (cf. param : 255)
	mavlink_msg_heartbeat_pack(255,0,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_ARDUPILOTMEGA,0xc0,0x0,MAV_STATE_ACTIVE);
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
	mavlink_msg_command_long_pack(255,0,&msg,1,0,MAV_CMD_REQUEST_PROTOCOL_VERSION,0,1,0,0,0,0,0,0);
	len = mavlink_msg_to_send_buffer(buf, &msg);

	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending data stream");
		exit(EXIT_FAILURE);
	}
	printf("\n");
	memset(buf, 0, BUFFER_LENGTH);
	
	/*// Request change type video stream		!!!!!TO DO!!!!!										  
	mavlink_msg_request_data_stream_pack(255, 0, &msg, 1, 0, MAVLINK_DATA_STREAM_IMG_RAW8U, 2, 1);
	len = mavlink_msg_to_send_buffer(buf, &msg);

	bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
	if (bytes_sent==-1) {
		perror("Sending data stream");
		exit(EXIT_FAILURE);
	}
	printf("\n");
	memset(buf, 0, BUFFER_LENGTH);*/
	


	//Init TCP connection to get video stream
	int s;
	struct sockaddr_in serv_addr;

	s = socket(PF_INET, SOCK_STREAM, 0);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr ("10.1.1.1") ;
	serv_addr.sin_port = htons (5502) ;
	memset (&serv_addr.sin_zero, 0, sizeof(serv_addr.sin_zero));
	connect (s, (struct sockaddr *)&serv_addr, sizeof serv_addr);
	//End initialization order


	pthread_t myThreadReciving;
	pthread_t myThreadHeartbeatPing;
	pthread_t myThreadSending;

	//Create threads
	pthread_create (&myThreadReciving, NULL, threadReciving, (void*)NULL);
	pthread_create (&myThreadHeartbeatPing, NULL, threadHeartbeatPing, (void*)NULL);
	pthread_create (&myThreadSending, NULL, threadSending, (void*)NULL);
	
	//Create and wait video stream receiver
	goProVideoStream ();

	//Wait threads
	pthread_join (myThreadSending, NULL);
	pthread_join (myThreadReciving, NULL);
	pthread_join (myThreadHeartbeatPing, NULL);
	

	close(sock);
	close(s);
	exit(EXIT_SUCCESS);
}


/**
 * @brief      Thread where we receive message
 *
 */
void* threadReciving (void* arg){

	uint8_t buf[BUFFER_LENGTH];
	ssize_t recsize;
	socklen_t fromlen;
	mavlink_channel_t chan = MAVLINK_COMM_0;

	while (run){
		memset(buf, 0, BUFFER_LENGTH);

		recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&targetAddr, &fromlen);
		if (recsize > 0)
		{
			// Something received
			mavlink_message_t msg;
			mavlink_status_t status;
			int i;
			pthread_mutex_lock (&mutex);
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
			pthread_mutex_unlock (&mutex);
		}

		sleep(1); // Sleep one second
	}

	pthread_exit(NULL); /* End of the thread */
}


/**
 * @brief      Ping heartbeat
 *
 * @param      arg   The arguments
 *
 * @return     { description_of_the_return_value }
 */
void* threadHeartbeatPing(void* arg){

	uint8_t buf[BUFFER_LENGTH];
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;
	mavlink_system_t localSysId;
	localSysId.sysid = 255;
	localSysId.compid = 0;

	while(run){
		mavlink_msg_heartbeat_pack(localSysId.sysid,localSysId.compid,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_ARDUPILOTMEGA,0xc0,0x0,MAV_STATE_ACTIVE);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
		if (bytes_sent==-1) {
			perror("Sending Heartbeat in thread");
			exit(EXIT_FAILURE);
		}

		memset(buf, 0, BUFFER_LENGTH);
		sleep(1);
	}

	//End of the thread
	pthread_exit(NULL);
}


/**
 * @brief      Thread where user send message
 *
 */
void* threadSending (void* arg){

	uint8_t buf[BUFFER_LENGTH];
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;
	mavlink_system_t localSysId;
	localSysId.sysid = 255;
	localSysId.compid = 0;
	mavlink_system_t targetSysId;
	targetSysId.sysid = 1;
	targetSysId.compid = 0;
	char order;
	int print;

	while(run){
		memset(buf, 0, BUFFER_LENGTH);

		//Main menu
		mavlink_display_main_menu();
		scanf("%s", &order);
		//arming
		if (strcmp(&order, "1") == 0){
			// Activate alt_hold mode to launch
			mavlink_order_select_mode('A', localSysId, targetSysId, &msg);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
			if (bytes_sent==-1) {
				perror("Sending data stream");
				exit(EXIT_FAILURE);
			}
			memset(buf, 0, BUFFER_LENGTH);
			// Activate mortors
			mavlink_msg_order_drone(order, localSysId, targetSysId, &msg);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
			if (bytes_sent==-1) {
				perror("Sending data stream");
				exit(EXIT_FAILURE);
			}
			continue;
		}

		//Print menu
		else if(strcmp(&order, "p") == 0){
			do{
				mavlink_display_display_menu();
				scanf("%d", &print);
				//To protect the vehicule global variable
				pthread_mutex_lock (&mutex);
				mavlink_display_order(print, vehicle);
				pthread_mutex_unlock (&mutex);
			}while(print!=0);
			continue;
		}

		//Control menu
		else if(strcmp(&order, "c") == 0){
			mavlink_display_control_menu();
			mode_raw(1);
			do{
				memset(buf, 0, BUFFER_LENGTH);
				order = getchar();
				if(mavlink_msg_order_drone(order, localSysId, targetSysId, &msg)==-1){
					continue;
				}
				//Sending order by UDP
				len = mavlink_msg_to_send_buffer(buf, &msg);
				bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
				if (bytes_sent==-1) {
					perror("Sending data stream");
					exit(EXIT_FAILURE);
				}
			}while(order!=' ');
			mode_raw(0);
			continue;
		}

		//Mode menu
		else if (strcmp(&order, "m") == 0){
			do {
				mavlink_display_mode_menu();
				scanf("%s", &order);
				if (mavlink_order_select_mode(order, localSysId, targetSysId, &msg)==-1) {
					continue;
				}
				//Sending order by UDP
				len = mavlink_msg_to_send_buffer(buf, &msg);
				bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
				if (bytes_sent==-1) {
					perror("Sending data stream");
					exit(EXIT_FAILURE);
				}
			} while(strcmp(&order,"0") != 0);
			continue;
		}

		//Quit the prog
		if(strcmp(&order, "e") == 0){
			run = 0;
			g_main_loop_quit(loop); 
			break;
		}

		//If the order doesn't exist
		if(mavlink_msg_order_drone(order, localSysId, targetSysId, &msg)==-1){
			continue;
		}

		//Sending order by UDP
		len = mavlink_msg_to_send_buffer(buf, &msg);
		bytes_sent = sendto(sock, buf, len, 0, (struct sockaddr*)&targetAddr, sizeof(struct sockaddr_in));
		if (bytes_sent==-1) {
			perror("Sending data stream");
			exit(EXIT_FAILURE);
		}

		// Sleep one second
		sleep(1);
	}

	//End of the thread
	pthread_exit(NULL);
}


/**
 * @brief	 Function where we get and display the video stream from the GoPro with GStreamer library
 * 
 * @return 0 if it finishes normally, else -1
 */
int goProVideoStream (){

	GstElement *pipeline;
    GstBus *bus;
	GstStateChangeReturn ret;
	
	
	/* Initialize GStreamer */
    gst_init(NULL, NULL);

	/* Build the pipeline */
    pipeline = gst_parse_launch("-v udpsrc port=5600 caps = \"application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264, payload=(int)96\" ! rtph264depay ! decodebin ! videoconvert ! autovideosink", NULL);
	bus = gst_element_get_bus(pipeline);
	
	/* Start playing */
	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
      g_printerr ("Unable to set the pipeline to the playing state.\n");
      gst_object_unref (pipeline);
      run = 0;
	  return -1;
    }
	
	/* Loop */
	loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
	
	/* Free resources */
	g_main_loop_unref (loop);
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	
	
	return 0;
}



/**
 * @brief      Change keyboard entry
 *
 * @param[in]  activate  1 to activate the mode, 0 deactivate it
 */
void mode_raw(int activate)
{
    static struct termios cooked;
    static int raw_activate = 0;

    if (raw_activate == activate)
        return;

    if (activate)
    {
        struct termios raw;

        tcgetattr(STDIN_FILENO, &cooked);

        raw = cooked;
        cfmakeraw(&raw);
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    else
        tcsetattr(STDIN_FILENO, TCSANOW, &cooked);

    raw_activate = activate;
}
