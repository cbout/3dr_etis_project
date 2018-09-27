

void mavlink_msg_pack(int rep, mavlink_message_t *msg){
	
	switch (rep) {
		
		case :
			/*Send Heartbeat */
			mavlink_msg_heartbeat_pack(1, 200, &msg, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
			break;
			
		case :
			/* Send Status */
			mavlink_msg_sys_status_pack(1, 200, &msg, 0, 0, 0, 500, 11000, -1, -1, 0, 0, 0, 0, 0, 0);
			break;
			
		case :
			/* Send Local Position */
			mavlink_msg_local_position_ned_pack(1, 200, &msg, microsSinceEpoch(), position[0], position[1], position[2], position[3], position[4], position[5]);
			break;
			
		case :
			/* Send attitude */
			mavlink_msg_attitude_pack(1, 200, &msg, microsSinceEpoch(), 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
			break;
			
		default :
			printf("this is an other type of message\n");
	}
	
}