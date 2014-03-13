all: notify reply_udp

notify: app_notify.o kwttd_network.o
	gcc app_notify.o kwttd_network.o -o notify

app_notify.o: app_notify.c
	gcc -c app_notify.c

kwttd_network.o: kwttd_network.c
	gcc -c kwttd_network.c

reply_udp: switch_reply_udp.o kwttd_util.o
	gcc switch_reply_udp.o kwttd_util.o -o reply_udp

switch_reply_udp.o: switch_reply_udp.c
	gcc -c switch_reply_udp.c

kwttd_util.o: kwttd_util.c
	gcc -c kwttd_util.c

clean:
	rm -rf *o *~ notify reply_udp
