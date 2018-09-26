#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int main () {
	char buf [80] ;
	
	int s, exp_len ;
	struct sockaddr_in moi, client ;

	moi.sin_family = AF_INET ;
	moi.sin_addr.s_addr = INADDR_ANY ;
	moi.sin_port = htons (5000) ;
	memset (&moi.sin_zero, 0, sizeof(moi.sin_zero));

	s = socket (PF_INET, SOCK_DGRAM, 0) ;
	bind (s, (struct sockaddr *)&moi, sizeof moi) ;

	memset (buf, 0, 80);
	exp_len = sizeof (client) ;
	recvfrom (s, buf, 80, 0, (struct sockaddr *)&client, &exp_len) ;
	printf ("J'ai recu [%s] de %s:%d\n", buf, inet_ntoa (client.sin_addr), ntohs (client.sin_port) ) ;

        memset (buf, 0, 80);
        strcpy (buf, "Bonjour client ! ") ;
	sendto (s, buf, 80, 0, (struct sockaddr *)&client, sizeof client) ;
	printf ("J'ai envoye [%s] à %s:%d\n", buf, inet_ntoa (client.sin_addr), ntohs (client.sin_port) ) ;

        memset (buf, 0, 80);
        strcpy (buf, "Ca va ?") ;
	sendto (s, buf, 80, 0, (struct sockaddr *)&client, sizeof client) ;
	printf ("J'ai envoye [%s] à %s:%d\n", buf, inet_ntoa (client.sin_addr), ntohs (client.sin_port) ) ;

        memset (buf, 0, 80);
	recvfrom (s, buf, 80, 0, (struct sockaddr *)&client, &exp_len) ;
	printf ("J'ai recu [%s] de %s:%d\n", buf, inet_ntoa (client.sin_addr), ntohs (client.sin_port) ) ;

	/* Exemple de réponse variant suivant ce qu'on a recu */
	if (!strncmp (buf, "Au revoir", strlen ("Au revoir"))) {
        	strcpy (buf, "Bye") ;
	}
	else {
        	strcpy (buf, "Salut") ;
	}
	sendto (s, buf, 80, 0, (struct sockaddr *)&client, sizeof client) ;
	printf ("J'ai envoye [%s] à %s:%d\n", buf, inet_ntoa (client.sin_addr), ntohs (client.sin_port) ) ;
	close (s) ;
}
