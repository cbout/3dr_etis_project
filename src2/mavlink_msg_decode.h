#ifndef _DECODE_H_
#define _DECODE_H_
// A completer

#include "../include/ardupilotmega/mavlink.h"
#include "mavlink_perso_types.h"

/**
 * @brief      Decode broadcast mavlink messages and update the corresponding parameter of the vehicle
 *
 * @param[in]  msg      The message
 * @param      vehicle  The vehicle
 *
 * @return     0 if the message has been identified and decoded, else -1
 */
int mavlink_msg_decode_broadcast(mavlink_message_t msg, vehicle_t *vehicle);


/**
 * @brief      Decode a answer Mavlink message
 *
 * @param[in]  msg   The message
 */
void mavlink_msg_decode_answer(mavlink_message_t msg);

#endif