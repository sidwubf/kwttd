all: notify recv

notify: app_notify.o kwttd_network.o
	gcc app_notify.o kwttd_network.o -o notify

app_notify.o: app_notify.c
	gcc -c app_notify.c

kwttd_network.o: kwttd_network.c
	gcc -c kwttd_network.c

recv: responce.o kwttd_util.o
	gcc responce.o kwttd_util.o -o recv

responce.o: responce.c
	gcc -c responce.c

kwttd_util.o: kwttd_util.c
	gcc -c kwttd_util.c

clean:
	rm -rf *o *~ notify recv
