#ifndef _DISPLAY_H_
#define _DISPLAY_H_
// TODO: Includes
#include <stdio.h>
#include <stdlib.h>
#include "mavlink_perso_types.h"
/**
 * @brief      Order for displaying informations of the vehicle
 *
 * @param[in]  order       The order
 * @param[in]  vehicle     The vehicle
 *
 * @return     0 if the exist -1 else
 */
int mavlink_display_order(int order, vehicle_t vehicle);

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
void mavlink_display_info_vehicle_by_id(int id, vehicle_t vehicle);


/**
 * @brief      Display all informations from the vehicle
 *
 * @param[in]  vehicle  The vehicle
 */
void mavlink_display_info_vehicle_all(vehicle_t vehicle);

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

#endif