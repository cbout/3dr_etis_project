

void mavlink_msg_decode(mavlink_message_t msg){
	
	switch (msg.msgid) {
		
		case MAVLINK_MSG_ID_HEARTBEAT:
			mavlink_heartbeat_t heartbeat;
			mavlink_msg_heartbeat_decode(&msg, &heartbeat);
			printf("This is a heartbeat of type : %d\n", heartbeat.type);
			break;
			
		case MAVLINK_MSG_ID_ATTITUDE:
			mavlink_attitude_t attitude;
			mavlink_msg_attitude_decode(&msg, &attitude);
			printf("This is a atitude of roll : %f\n", attitude.roll);
			break;
			
			
			
			
			
		default :
			printf("this is an other type of message\n");
	}
	
}