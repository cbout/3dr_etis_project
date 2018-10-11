# MAVLink #

## Qu'est-ce que MAVLink ? ##

MAVLink (Micro Air Vehicle Link) est un protocole de communication pour les petits véhicules autonomes. Il est principalement utilisé dans les communications GCS <-> Unmanned Vehicule.

## Comment utiliser ce protocole dans ce projet ? ##

Nous avons décider d'utiliser une librairie C appelée *c_library_v1* [Github page](https://github.com/mavlink/c_library_v1.git) ou [fichier compressé](ressources/c_library_v1-master.zip) et d'utiliser la partie *common* qui référence les commandes et les messages standardisés par MAVLink 2 version 1.

## Composition d'une trame MAVLINK ##

![Décomposition d'une trame MAVLink](ressources/mavlink_v1_trame.png)

## Protocole de communication ##

MAVLink utilise le protocole UDP pour effectuer ses envoies de données

### Connexion ###

Pour pouvoir dialoguer avec le controller il faut selectionner le bon port d'écoute et le bon port d'envoie.
Pour ce faire, la fonction `init_mavlink_udp_connect()` cherche dynamiquement le port d'écoute du serveur et créé les bonnes `sockaddr_in` pour mettre en place la communication.

### Réception des données ###

Pour recevoir un message de la part du serveur SOLO 3DR, il suffit de se connecter au réseau wifi (par défaut SoloLink_###, mdp: sololink) et d'ouvrir une **socket UDP** pour écouter sur le port : **14550**, qui est le port que le serveur utilise.
Exemple de code pour initialiser :
```C
  //Socket UDP
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  //Adresse d'écoute
  struct sockaddr_in locAddr;
  memset(&locAddr, 0, sizeof(locAddr));
  locAddr.sin_family = AF_INET;
  locAddr.sin_addr.s_addr = INADDR_ANY;
  locAddr.sin_port = htons(listenning_port);

  // Bind the socket to port 14550 - necessary to receive packets from qgroundcontrol
  if (-1 == bind(sock,(struct sockaddr* )&locAddr, sizeof(struct sockaddr)))
  {
    perror("error bind failed");
    close(sock);
    exit(EXIT_FAILURE);
  }

```

Ainsi, une fois la socket effective il faut récupérer dans un buffer les messages envoyés par le serveur.

```C
//Reception du(des) message(s)
recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);


if (recsize > 0)
  {
  // Quelque chose est reçu, on affiche la taille et sa contenance
  mavlink_message_t msg;
  mavlink_status_t status;

  printf("Bytes Received: %d\nDatagram: ", (int)recsize);
  for (i = 0; i < recsize; ++i)
  {
    temp = buf[i];
    printf("%02x ", (unsigned char)temp);

    // Si nous avons réussi à parser le message hexa -> struct mavlink_message_t
    if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
    {
      // Structure d'un heartbeat (voir mavlink_udp/include/common/mavlink_msg_heartbeat.h)
      mavlink_heartbeat_t heartbeat_info;
      // Packet reçu
      printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);

      // Réaction en fonction du type de message
      switch (msg.msgid) {
        case MAVLINK_MSG_ID_HEARTBEAT:
          printf("This is a heartbeat message");
          //Décodage du message
          mavlink_msg_heartbeat_decode(&msg,&heartbeat_info);
          // Affiche le type de MAV (Micro Air Vehicule)
          printf("This MAV is a %d \n", heartbeat_info.type);
          break;
        default :
          printf("this is an other type of message\n");
          break;
      }
    }
  }
}
```
Il existe plusieurs types de messages identifiés par un ID unique (MAVLINK_MSG_ID_###), dans la librairie il y a pour chaque message une structure de données (mavlink_###\_t), d'une fonction de décodage (mavlink_msg_###\_decode()) et d'une fonction pour faire le paquet UDP (mavlink_msg_###\_pack()).

Exemple: le message heartbeat nous avons : msgid = MAVLINK_MSG_ID_HEARTBEAT et les fonctions mavlink_msg_heartbeat_decode(), mavlink_msg_heartbeat_pack() et de la structure mavlink_heartbeat_t.


### Envoie des données ###





MAVLINK MANUAL CONTROL
