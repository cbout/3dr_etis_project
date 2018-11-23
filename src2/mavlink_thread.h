#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "mavlink_msg_decode.h"
#include "mavlink_display.h"
#include "mavlink_msg_order.h"


/**
 * @brief      Thread where we receive message
 *
 * @param      arg   The argument
 *
 */
void* threadReciving (void* arg);


/**
 * @brief      Ping heartbeat
 *
 * @param      arg   The arguments
 *
 */
void* threadHeartbeatPing(void* arg);

/**
 * @brief      Thread where user send message
 *
 * @param      arg   The argument
 *
 */
void* threadSending (void* arg);