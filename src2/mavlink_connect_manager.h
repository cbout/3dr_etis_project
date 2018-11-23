#ifndef _INIT_UDP_
#define _INIT_UDP_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>
#include <arpa/inet.h>

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

int init_solo_3dr_video_stream_connect(int* sock, struct sockaddr_in* serv_addr, int port, char* target_ip);
#endif