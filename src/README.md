# MAVLink C Prog:

### Compilation :

```bash
make all;
```

## Using

### UDP :

```bash
./mavlink_udp --udp [--target-ip <Targets IP>] [--local-port <Listening port>] [--video-ip <Video serveur IP>] [--target-video-port <Video stream port>]
```

### UART :

```bash
./mavlink_udp --uart [-P <Port>][-B <baud>]
```

