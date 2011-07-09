all: buildclient

buildserver:
	gcc -o cmdserver kvs.c cmdserver.c

buildclient:
	gcc -o client/client common/msg.c client/client.c

runclient:
	./client/client

clean:
	rm *.o */*.o client/client cmdserver
