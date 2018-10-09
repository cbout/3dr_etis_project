#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

void mavlink_msg_decode(mavlink_message_t msg);
int mavlink_msg_param(int rep, char *param);

#endif /* __MAVLINK_PERSO_LIB_H_ */