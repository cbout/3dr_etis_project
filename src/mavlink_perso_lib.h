#include "mavlink_perso_types.h"

#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_


/**
 * @brief      Decode the name of the command
 *
 * @param[in]  enumType      The type of command
 * @param[in]  value  		 The value of the command
 *
 * @return     the corresponding string name of the command
 */
char* mavlink_enum_to_string(MAV_ENUM enumType, int value);


/**
 * @brief      Decode broadcast mavlink messages and update the corresponding parameter of the vehicle
 *
 * @param[in]  msg      The message
 * @param      vehicle  The vehicle
 *
 * @return     0 if the message has been identified and decoded, else -1
 */
int mavlink_msg_decode_broadcast(mavlink_message_t msg, Vehicle *vehicle);


/**
 * @brief      Decode a answer Mavlink message
 *
 * @param[in]  msg   The message
 */
void mavlink_msg_decode_answer(mavlink_message_t msg);


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

/**
 * @brief      Order for displaying informations of the vehicle
 *
 * @param[in]  order       The order
 * @param[in]  vehicle     The vehicle
 *
 * @return     0 if the exist -1 else
 */
int mavlink_display_order(int order, Vehicle vehicle);

/**
 * @brief      Display the mode menu
 */
void mavlink_display_mode_menu();

/**
 * @brief      Display an information from the vehicle with the id
 *
 * @param[in]  id       The identifier
 * @param[in]  vehicle  The vehicle
 */
void mavlink_display_info_vehicle_by_id(int id, Vehicle vehicle);


/**
 * @brief      Display all informations from the vehicle
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
 * @brief      Display the main menu
 *
 */
void mavlink_display_main_menu();


/**
 * @brief      Display the display menu
 *
 */
void mavlink_display_display_menu();


/**
 * @brief      Display the control menu
 *
 */
void mavlink_display_control_menu();


/**
* Display the mode menu
*
*
*/
void mavlink_display_mode_menu();


#endif /* __MAVLINK_PERSO_LIB_H_ */
