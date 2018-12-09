/**********************************************************************************************************************************************************
 Copyright  ETIS — ENSEA, Université de Cergy-Pontoise, CNRS (1991-2018)
 promethe@ensea.fr


 Structures to manage a mavlink communication.
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
#ifndef _PERSO_TYPES
#define _PERSO_TYPES

#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <mavlink.h>
#include <gst/gst.h>

#define BUFFER_LENGTH 2041

/**
 * @brief      Contains all informations of the vehicle
 *
 */
typedef struct vehicle {
	mavlink_system_t system_ids;
	mavlink_heartbeat_t heartbeat;
	mavlink_sys_status_t sys_status;
	mavlink_system_time_t system_time;
	mavlink_gps_raw_int_t gps_raw_int;
	mavlink_raw_imu_t raw_imu;
	mavlink_scaled_pressure_t scaled_pressure;
	mavlink_attitude_t attitude;
	mavlink_global_position_int_t global_position_int;
	mavlink_rc_channels_raw_t rc_channels_raw;
	mavlink_servo_output_raw_t servo_output_raw;
	mavlink_mission_current_t mission_current;
	mavlink_nav_controller_output_t nav_controller_output;
	mavlink_vfr_hud_t vfr_hud;
	mavlink_radio_status_t radio_status;
	mavlink_scaled_imu2_t scaled_imu2;
	mavlink_power_status_t power_status;
	mavlink_scaled_imu3_t scaled_imu3;
	mavlink_terrain_request_t terrain_request;
	mavlink_terrain_report_t terrain_report;
	mavlink_scaled_pressure2_t scaled_pressure2;
	mavlink_named_value_int_t named_value_int;
	mavlink_statustext_t statustext;
} vehicle_t;


typedef struct mavlink_thread_arg_udp
{
	vehicle_t vehicle;
	pthread_mutex_t mutex;
	int sock;
	struct sockaddr_in locAddr;
	struct sockaddr_in targetAddr;
	int run;
	GMainLoop *loop;
}mavlink_thread_arg_udp_t;


#endif
