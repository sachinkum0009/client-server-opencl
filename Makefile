CC = g++

CFLAGS = -g -std=c++17 -Wall -pedantic


all:cl_code server client

cl_code: src/cl_code.cpp
	$(CC) $(CFLAGS) -o bin/cl_code.out src/cl_code.cpp -I ./include -lOpenCL

server: src/server.cpp
	$(CC) $(CFLAGS) -o bin/server.out src/server.cpp -I ./include

client: src/client.cpp
	$(CC) $(CFLAGS) -o bin/client.out src/client.cpp -I ./include


clean:
	$(RM) bin/cl_code.out bin/server.out bin/client.out

run:
	./bin/server.out
	./bin/client.out
