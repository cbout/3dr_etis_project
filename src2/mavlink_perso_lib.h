#ifndef __MAVLINK_PERSO_LIB_H_
#define __MAVLINK_PERSO_LIB_H_

#include "mavlink_perso_types.h"

/**
 * @brief      Change keyboard entry
 *
 * @param[in]  activate  1 to activate the mode, 0 deactivate it
 */
void mode_raw(int activate);

/**
 * @brief      Thread where we receive message
 *
 */
void* threadReciving (void* arg);

/**
 * @brief      Thread which send heartbeat to drone
 *
 */
void* threadHeartbeatPing (void* arg);

/**
 * @brief      Thread where user send message
 *
 */
void* threadSending (void* arg);

/**
 * @brief	 Function where we get and display the video stream from the GoPro with GStreamer library
 * 
 * @return 0 if it finishes normally, else -1
 */
int goProVideoStream ();

#endif /* __MAVLINK_PERSO_LIB_H_ */
