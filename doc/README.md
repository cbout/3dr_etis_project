# MAVLink #

## Qu'est-ce que MAVLink ? ##

MAVLink (Micro Air Vehicle Link) est un protocole de communication pour les petits véhicules autonome. Il est principalement utilisé dans les communications GCS <-> Unmanned Vehicule.

## Comment utiliser ce protocole dans ce projet ? ##

Nous avons décider d'utiliser une librairie C appelé *c_library_v2* [Github page](https://github.com/mavlink/c_library_v2.git) ou [fichier compressé](ressources/c_library_v2-master.zip) et d'utiliser la partie *common* qui référence les commandes et les messages standardisés par MAVLink 2.

### Lire un message ###

Cette librairie fournie un ensemble de fonction capable de décoder un type de message spécifique, identifié par son `MAVLINK_MSG_ID`

Protocole de lecture d'un message en supposant que nous avons demandé le heartbeat de l'appareil:

```C
//Reception du(des) message(s)
recsize = recvfrom(sock, (void *)buf, BUFFER_LENGTH, 0, (struct sockaddr *)&gcAddr, &fromlen);


if (recsize > 0)
  {
  // Something received - print out all bytes and parse packet

  mavlink_message_t msg;
  mavlink_status_t status;

  printf("Bytes Received: %d\nDatagram: ", (int)recsize);
  for (i = 0; i < recsize; ++i)
  {
    temp = buf[i];
    printf("%02x ", (unsigned char)temp);
    //Si nous avons réussi à parser le message
    if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
    {
      // Structure d'un heartbeat (voir mavlink_udp/include/common/mavlink_msg_heartbeat.h)
      mavlink_heartbeat_t heartbeat_info;
      // Packet received
      printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", msg.sysid, msg.compid, msg.len, msg.msgid);

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







MAVLINK MANUAL CONTROL
