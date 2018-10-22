#include "mavlink_perso_types.h"

#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

int mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle);
void mavlink_msg_decode_answer(mavlink_message_t msg);
int mavlink_msg_order(char order, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg);
void mavlink_display_info_vehicle_by_id(int id, Vehicle vehicle);
void mavlink_display_info_vehicle_all(Vehicle vehicle);
int init_mavlink_udp_connect(int* sock, struct sockaddr_in* locAddr, int local_port, struct sockaddr_in* targetAddr, char* target_ip, int timeout);


#endif /* __MAVLINK_PERSO_LIB_H_ */
