all: recv

recv: responce.o kwttd_util.o
	gcc responce.o kwttd_util.o -o recv

responce.o: responce.c
	gcc -c responce.c

kwttd_util.o: kwttd_util.c
	gcc -c kwttd_util.c

clean:
	rm -rf *o recv
