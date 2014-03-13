all: notify reply_udp require reply_tcp

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
	
require: app_require.o kwttd_util.o
	gcc app_require.o kwttd_util.o -o require

app_require.o: app_require.c
	gcc -c app_require.c
	
reply_tcp: switch_reply_tcp.o kwttd_util.o
	gcc switch_reply_tcp.o kwttd_util.o -o reply_tcp

switch_reply_tcp.o: switch_reply_tcp.c
	gcc -c switch_reply_tcp.c
		
kwttd_util.o: kwttd_util.c
	gcc -c kwttd_util.c

clean:
	rm -rf *o *~ notify reply_udp require reply_tcp
