#include "mavlink_thread.h"


/**
 * @brief      Thread where we receive message
 *
 */
void* threadReciving (void* arg){

	mavlink_thread_arg_t* args = (mavlink_thread_arg_t*) arg; 

	uint8_t buf[BUFFER_LENGTH];
	ssize_t recsize;
	socklen_t fromlen;
	mavlink_channel_t chan = MAVLINK_COMM_0;

	while (args->run){
		memset(buf, 0, BUFFER_LENGTH);

		recsize = recvfrom(args->sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&args->targetAddr, &fromlen);
		if (recsize > 0)
		{
			// Something received
			mavlink_message_t msg;
			mavlink_status_t status;
			int i;
			pthread_mutex_lock (&args->mutex);
			for (i = 0; i < recsize; ++i)
			{
				if (mavlink_parse_char(chan, buf[i], &msg, &status))
				{
					if(mavlink_msg_decode_broadcast(msg, &args->vehicle)==-1){
						//If this is not a broadcast message
						mavlink_msg_decode_answer(msg);
					}
				}
			}
			pthread_mutex_unlock (&args->mutex);
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

	mavlink_thread_arg_t* args = (mavlink_thread_arg_t*) arg; 
	
	uint8_t buf[BUFFER_LENGTH];
	int bytes_sent;
	mavlink_message_t msg;
	uint16_t len;
	mavlink_system_t localSysId;
	localSysId.sysid = 255;
	localSysId.compid = 0;

	while(args->run){
		mavlink_msg_heartbeat_pack(localSysId.sysid,localSysId.compid,&msg,MAV_TYPE_GCS,MAV_AUTOPILOT_ARDUPILOTMEGA,0xc0,0x0,MAV_STATE_ACTIVE);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
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

	mavlink_thread_arg_t* args = (mavlink_thread_arg_t*) arg; 

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

	while(args->run){
		memset(buf, 0, BUFFER_LENGTH);

		//Main menu
		mavlink_display_main_menu();
		scanf("%s", &order);
		//arming
		if (strcmp(&order, "1") == 0){
			// Activate alt_hold mode to launch
			mavlink_order_select_mode('A', localSysId, targetSysId, &msg);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
			if (bytes_sent==-1) {
				perror("Sending data stream");
				exit(EXIT_FAILURE);
			}
			memset(buf, 0, BUFFER_LENGTH);
			// Activate mortors
			mavlink_msg_order_drone(order, localSysId, targetSysId, &msg);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
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
				pthread_mutex_lock (&args->mutex);
				mavlink_display_order(print, args->vehicle);
				pthread_mutex_unlock (&args->mutex);
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
				bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
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
				bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
				if (bytes_sent==-1) {
					perror("Sending data stream");
					exit(EXIT_FAILURE);
				}
			} while(strcmp(&order,"0") != 0);
			continue;
		}

		//Quit the prog
		if(strcmp(&order, "e") == 0){
			args->run = 0;
			// g_main_loop_quit(loop); 
			break;
		}

		//If the order doesn't exist
		if(mavlink_msg_order_drone(order, localSysId, targetSysId, &msg)==-1){
			continue;
		}

		//Sending order by UDP
		len = mavlink_msg_to_send_buffer(buf, &msg);
		bytes_sent = sendto(args->sock, buf, len, 0, (struct sockaddr*)&args->targetAddr, sizeof(struct sockaddr_in));
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