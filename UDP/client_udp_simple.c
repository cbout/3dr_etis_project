#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>


int main () {
	char buf [80] ;
	int s, exp_len ;
	struct sockaddr_in serveur ;

	s = socket (PF_INET, SOCK_DGRAM, 0) ;

	serveur.sin_family = AF_INET ;
	serveur.sin_addr.s_addr = inet_addr ("127.0.0.1") ;
	serveur.sin_port = htons (5000) ;
	memset (&serveur.sin_zero, 0, sizeof(serveur.sin_zero));


	memset (buf, 0, 80);
	strcpy (buf, "Bonjour") ;
	sendto (s, buf, 80, 0, (struct sockaddr *)&serveur, sizeof serveur) ;
        printf ("J'ai envoye [%s] à %s:%d\n", buf, inet_ntoa (serveur.sin_addr), ntohs (serveur.sin_port) ) ;

        memset (buf, 0, 80);
	exp_len = sizeof (serveur) ;
	recvfrom (s, buf, 80, 0, (struct sockaddr *)&serveur, &exp_len) ;
        printf ("J'ai recu [%s] de %s:%d\n", buf, inet_ntoa (serveur.sin_addr), ntohs (serveur.sin_port) ) ;

        memset (buf, 0, 80);
	recvfrom (s, buf, 80, 0, (struct sockaddr *)&serveur, &exp_len) ;
        printf ("J'ai recu [%s] de %s:%d\n", buf, inet_ntoa (serveur.sin_addr), ntohs (serveur.sin_port) ) ;

	memset (buf, 0, 80);
	strcpy (buf, "Au revoir") ;
	sendto (s, buf, 80, 0, (struct sockaddr *)&serveur, sizeof serveur) ;
        printf ("J'ai envoye [%s] à %s:%d\n", buf, inet_ntoa (serveur.sin_addr), ntohs (serveur.sin_port) ) ;

        memset (buf, 0, 80);
	recvfrom (s, buf, 80, 0, (struct sockaddr *)&serveur, &exp_len) ;
        printf ("J'ai recu [%s] de %s:%d\n", buf, inet_ntoa (serveur.sin_addr), ntohs (serveur.sin_port) ) ;

	close (s) ;
}
