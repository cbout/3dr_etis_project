#include "mavlink_perso_types.h"

#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

void mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle);
void mavlink_msg_decode_answer(mavlink_message_t msg);
int mavlink_msg_param(int rep, char *param);
void mavlink_display_vehicule(int id, Vehicle vehicle);

#endif /* __MAVLINK_PERSO_LIB_H_ */