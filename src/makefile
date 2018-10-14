all : mavlink_udp


mavlink_msg_order.o : mavlink_msg_order.c mavlink_perso_lib.h mavlink_perso_types.h
	gcc -std=c99 -I include/common -c mavlink_msg_order.c

mavlink_msg_decode.o : mavlink_msg_decode.c mavlink_perso_lib.h mavlink_perso_types.h
	gcc -std=c99 -I include/common -c mavlink_msg_decode.c
	
mavlink_display.o : mavlink_display.c mavlink_perso_lib.h mavlink_perso_types.h
	gcc -std=c99 -I include/common -c mavlink_display.c

mavlink_udp.o :  mavlink_udp.c mavlink_perso_lib.h mavlink_perso_types.h
	gcc -std=c99 -I include/common -c mavlink_udp.c
	
	
mavlink_udp : mavlink_msg_order.o mavlink_msg_decode.o mavlink_display.o mavlink_udp.o
	gcc -std=c99 -I include/common -o mavlink_udp $^

clean : 
	rm -f  mavlink_udp *.o