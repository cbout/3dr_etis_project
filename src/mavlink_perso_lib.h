#include "mavlink_perso_types.h"

#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

/**
 * @brief      Decode default mavlink messages
 *
 * @param[in]  msg      The message
 * @param      vehicle  The vehicle
 *
 * @return     { description_of_the_return_value }
 */
int mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle);

/**
 * @brief      Decode a mavlink message
 *
 * @param[in]  msg   The message
 */
void mavlink_msg_decode_answer(mavlink_message_t msg);


/**
 * @brief      { function_description }
 *
 * @param[in]  order       The order
 * @param[in]  source_sys  The source system
 * @param[in]  target_sys  The target system
 * @param      msg         The message
 *
 * @return     { description_of_the_return_value }
 */
int mavlink_msg_order(char order, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg);

int mavlink_order_select_mode(char selectedMode, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg);

/**
 * @brief      { function_description }
 *
 * @param[in]  order       The order
 * @param[in]  vehicle     The vehicle
 *
 * @return     { description_of_the_return_value }
 */
int mavlink_display_order(int order, Vehicle vehicle);

void mavlink_display_mode_menu();

/**
 * @brief      Print a field by his id
 *
 * @param[in]  id       The identifier
 * @param[in]  vehicle  The vehicle
 */
void mavlink_display_info_vehicle_by_id(int id, Vehicle vehicle);

/**
 * @brief      Print all the vehicle informations
 *
 * @param[in]  vehicle  The vehicle
 */
void mavlink_display_info_vehicle_all(Vehicle vehicle);

/**
 * @brief      Init a UDP connection between groundControl and a MAV
 *
 * @param      sock        The sock
 * @param      locAddr     The location address
 * @param[in]  local_port  The local port
 * @param      targetAddr  The target address
 * @param      target_ip   The target ip
 * @param[in]  timeout     The timeout
 *
 * @return     0 if connection is done, -1 otherwise
 */
int init_mavlink_udp_connect(int* sock, struct sockaddr_in* locAddr, int local_port, struct sockaddr_in* targetAddr, char* target_ip, int timeout);


/**
 * @brief      Print the main menu
 *
 */
void mavlink_display_main_menu();


/**
 * @brief      Print the display menu
 *
 */
void mavlink_display_display_menu();


/**
 * @brief      Print the control menu
 *
 */
void mavlink_display_control_menu();

#endif /* __MAVLINK_PERSO_LIB_H_ */
