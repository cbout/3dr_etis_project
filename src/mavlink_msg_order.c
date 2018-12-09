/**********************************************************************************************************************************************************
 Copyright  ETIS — ENSEA, Université de Cergy-Pontoise, CNRS (1991-2018)
 promethe@ensea.fr


 Functions to make specific mavlink message.
 Those functions are an entry to understand how to make a mavlink communication program.
 To do that used the c_library_v1, that can be download here : https://github.com/mavlink/c_library_v1.
 We also make a little tutorial of Mavlink here : https://github.com/cbout/MAVLink_C_example.

 This software is governed by the CeCILL v2.1 license under French law and abiding by the rules of distribution of free software.
 You can use, modify and/ or redistribute the software under the terms of the CeCILL v2.1 license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info".
 As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license,
 users are provided only with a limited warranty and the software's author, the holder of the economic rights,  and the successive licensors have only limited liability.
 In this respect, the user's attention is drawn to the risks associated with loading, using, modifying and/or developing or reproducing the software by the user in light of its specific status of free software,
 that may mean  that it is complicated to manipulate, and that also therefore means that it is reserved for developers and experienced professionals having in-depth computer knowledge.
 Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured
 and, more generally, to use and operate it in the same conditions as regards security.
 The fact that you are presently reading this means that you have had knowledge of the CeCILL v2.1 license and that you accept its terms.
**********************************************************************************************************************************************************/
/*********************************************************************************************************************************************************
 Authors: Raphael Bergoin, Clement Bout
 Created: 10/2018
**********************************************************************************************************************************************************/
#include "mavlink_msg_order.h"

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
int mavlink_msg_order_drone(char order, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg){

	//!!!!!!!!!!!! To complete!!!!!!!!!!!!!!
	switch (order) {

		case '1' :
		{
			// Request arm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_COMPONENT_ARM_DISARM, 0, 1, 0, 0, 0, 0, 0, 0);
			return 0;
		}

		case '2' :
		{
			// Request disarm motors : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_COMPONENT_ARM_DISARM, 0, 0, 0, 0, 0, 0, 0, 0);
			return 0;
		}
		
		//Test
		case '3':
		{
			// Request test armed : expected COMMAND_ACK
			mavlink_msg_command_long_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid, target_sys.compid, MAV_CMD_SOLO_BTN_FLY_HOLD, 0, 1, 0, 0, 0, 0, 0,0);
			return 0;
		}
		
		//TO DO add mavlink command
		case 'z':
		{
			// Request move forward

			return 0;
		}

		case 's':
		{
			// Request move back

			return 0;
		}

		case 'q':
		{
			// Request move left

			return 0;
		}

		case 'd':
		{
			// Request move right

			return 0;
		}

		case 'i':
		{
			// Request go up

			return 0;
		}

		case 'k':
		{
			// Request go down

			return 0;
		}

		case 'j':
		{
			// Request rotate left

			return 0;
		}

		case 'l':
		{
			// Request rotate right

			return 0;
		}


		//...

		default :
			//printf("Incorrect order\n");
			return -1;
	}

}


/**
 * @brief      Order for displaying informations of the vehicle
 *
 * @param[in]  order       The order
 * @param[in]  vehicle     The vehicle
 *
 * @return     0 if the exist -1 else
 */
int mavlink_display_order(int order, vehicle_t vehicle){

	switch (order) {

		case 1:
		{
			// Order to display all informations of the vehicule
			mavlink_display_info_vehicle_all(vehicle);
			return 0;
		}
		
		case 2:
		{
			// Order to display heartbeat
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_HEARTBEAT, vehicle);
			return 0;
		}
		
		case 3:
		{
			// Order to display sys_status
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SYS_STATUS, vehicle);
			return 0;
		}
		
		case 4:
		{
			// Order to display system_time
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SYSTEM_TIME, vehicle);
			return 0;
		}
		
		case 5:
		{
			// Order to display gps_raw_int
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_GPS_RAW_INT, vehicle);
			return 0;
		}
		
		case 6:
		{
			// Order to display raw_imu
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RAW_IMU, vehicle);
			return 0;
		}
		
		case 7:
		{
			// Order to display scaled_pressure
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_PRESSURE, vehicle);
			return 0;
		}
		
		case 8:
		{
			// Order to display attitude
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_ATTITUDE, vehicle);
			return 0;
		}
		
		case 9:
		{
			// Order to display global_position_int
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, vehicle);
			return 0;
		}
		
		case 10:
		{
			// Order to display rc_channels_raw
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RC_CHANNELS_RAW, vehicle);
			return 0;
		}
		
		case 11:
		{
			// Order to display servo_output_raw
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SERVO_OUTPUT_RAW, vehicle);
			return 0;
		}
		
		case 12:
		{
			// Order to display mission_current
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_MISSION_CURRENT, vehicle);
			return 0;
		}
		
		case 13:
		{
			// Order to display nav_controller_output
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT, vehicle);
			return 0;
		}
		
		case 14:
		{
			// Order to display vfr_hud
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_VFR_HUD, vehicle);
			return 0;
		}
		
		case 15:
		{
			// Order to display radio_status
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_RADIO_STATUS, vehicle);
			return 0;
		}
		
		case 16:
		{
			// Order to display scaled_imu2
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_IMU2, vehicle);
			return 0;
		}
		
		case 17:
		{
			// Order to display power_status
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_POWER_STATUS, vehicle);
			return 0;
		}
		
		case 18:
		{
			// Order to display scaled_imu3
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_IMU3, vehicle);
			return 0;
		}
		
		case 19:
		{
			// Order to display terrain_request
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_TERRAIN_REQUEST, vehicle);
			return 0;
		}
		
		case 20:
		{
			// Order to display terrain_report
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_TERRAIN_REPORT, vehicle);
			return 0;
		}
		
		case 21:
		{
			// Order to display scaled_pressure2
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_SCALED_PRESSURE2, vehicle);
			return 0;
		}
		
		case 22:
		{
			// Order to display named_value_int
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_NAMED_VALUE_INT, vehicle);
			return 0;
		}
		
		case 23:
		{
			// Order to display statustext
			mavlink_display_info_vehicle_by_id(MAVLINK_MSG_ID_STATUSTEXT, vehicle);
			return 0;
		}

		default :
			//printf("Incorrect type of display\n");
			return -1;
	}

}


/**
 * @brief      Possibles order to change the mode
 *
 * @param[in]  selectedMode  The selected mode
 * @param[in]  source_sys    The source system
 * @param[in]  target_sys    The target system
 * @param      msg           The message
 *
 * @return     0 if succes, -1 otherwise
 */
int mavlink_order_select_mode(char selectedMode, mavlink_system_t source_sys, mavlink_system_t target_sys, mavlink_message_t *msg)
{
	switch (selectedMode) {
		case 'G':
		{
			mavlink_msg_set_mode_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid,MAV_MODE_GUIDED_ARMED+MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,COPTER_MODE_GUIDED);
			return 0;
		}
		case 'A':
		{
			mavlink_msg_set_mode_pack(source_sys.sysid, source_sys.compid, msg, target_sys.sysid,MAV_MODE_MANUAL_ARMED+MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,COPTER_MODE_ALT_HOLD);
			return 0;
		}
		default:
			return -1;
	}
	return -1;
}
