#ifndef _ORDER_H_
#define _ORDER_H_
// A completer
#include <stdio.h>
#include <stdlib.h>
#include "../include/ardupilotmega/mavlink.h"
#include "mavlink_display.h"
/**
 * @brief      Order for the drone
 *
 * @param[in]  order       The order
 * @param[in]  source_sys  The source system
 * @param[in]  target_sys  The target system
 * @param      msg         The message
 *
 * @return     0 if the exist -1 else
 */
int mavlink_msg_order_drone(char order, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg);


/**
 * @brief      Order to change mode
 *
 * @param[in]  selectedMode  The selected mode
 * @param[in]  source_sys    The source system
 * @param[in]  target_sys    The target system
 * @param      msg           The message
 *
 * @return     0 if succes, -1 otherwise
 */
int mavlink_order_select_mode(char selectedMode, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg);

#endif