#include "mavlink_connect_manager.h"
/**
 * @brief      Init a UDP connection between groundControl and a MAV
 *
 * @param      sock        The soket to bind
 * @param      locAddr     The local address
 * @param[in]  local_port  The local port
 * @param      targetAddr  The target address
 * @param      target_ip   The target ip
 * @param[in]  timeout     The timeout (if timeout<0 it's take default value 30 secs)
 *
 * @return     0 if connection is done, -1 otherwise
 */
int init_mavlink_udp_connect(int* sock, struct sockaddr_in* locAddr, int local_port, struct sockaddr_in* targetAddr, char* target_ip, int timeout)
{
	// Init the socket to receive datagram and support UDP protocol
	*sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	memset(locAddr, 0, sizeof(*locAddr));
	locAddr->sin_family = AF_INET;
	locAddr->sin_addr.s_addr = INADDR_ANY;
	locAddr->sin_port = htons(local_port);

	if (-1 == bind(*sock,(struct sockaddr *)locAddr, sizeof(struct sockaddr)))
	{
		perror("error bind failed");
		close(*sock);
    return -1;
	}

	printf("INIT listenning :\nUdpin: 0.0.0.0:%d\n", ntohs(locAddr->sin_port));
	
	/* Attempt to make it non blocking */
	#if (defined __QNX__) | (defined __QNXNTO__)
	if (fcntl(*sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
	#else
	if (fcntl(*sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
	#endif
	{
		fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
		close(*sock);
    	return -1;
	}

	// Receiving buffer
	char buf[256];
	memset(buf,0,256);

	// The possible socket which will received our messages
	struct sockaddr_in possibleTarget;
  	socklen_t possibleTargetLen = sizeof(possibleTarget);

  	time_t currentTime;
  	time_t startTime = time(&currentTime);
  	double timeLeft = 0;

  	// While we don't find a packet which can indicate sending port we read all messages received on our port
	while (recvfrom(*sock, buf, sizeof(buf), 0, (struct sockaddr*)(&possibleTarget), &possibleTargetLen)<=0
				|| possibleTarget.sin_addr.s_addr != inet_addr(target_ip)) {
		
		memset(buf,0,256);
		time(&currentTime);
		timeLeft = difftime(currentTime, startTime);
		if (timeLeft > timeout)
		{
			perror("Connection time out");
			close(*sock);
			return -1;	
		}
	}

	memset(targetAddr, 0, sizeof(*targetAddr));
	targetAddr->sin_family = AF_INET;
	targetAddr->sin_addr.s_addr = inet_addr(target_ip);
	targetAddr->sin_port = possibleTarget.sin_port;

	printf("INIT target :\nUdpout: %s:%d\n",target_ip,ntohs(targetAddr->sin_port));
	return 0;
}

/**
 * @brief      Init video stream connection for a solo 3dr
 *
 * @param      sock       The sock
 * @param      serv_addr  The serv address
 * @param[in]  port       The port
 * @param      target_ip  The target ip
 *
 * @return     0 if success, -1 otherwise
 */
int init_solo_3dr_video_stream_connect(int* sock, struct sockaddr_in* serv_addr, int port, char* target_ip)
{

	*sock = socket(PF_INET, SOCK_STREAM, 0);

	serv_addr->sin_family = AF_INET;
	serv_addr->sin_addr.s_addr = inet_addr (target_ip) ;
	serv_addr->sin_port = htons (port) ;
	memset (serv_addr->sin_zero, 0, sizeof(serv_addr->sin_zero));

	return connect (*sock, (struct sockaddr *)serv_addr, sizeof (*serv_addr));
}