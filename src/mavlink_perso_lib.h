#include "mavlink_perso_types.h"

#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

int mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle);
void mavlink_msg_decode_answer(mavlink_message_t msg);
int mavlink_msg_order(int order, mavlink_message_t *msg);
void mavlink_display_info_vehicle_by_id(int id, Vehicle vehicle);
void mavlink_display_info_vehicle_all(Vehicle vehicle);

#endif /* __MAVLINK_PERSO_LIB_H_ */