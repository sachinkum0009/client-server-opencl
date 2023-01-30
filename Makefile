CC = g++

CFLAGS = -g -std=c++17 -Wall -pedantic


all:server client
# all:cl_code server client

# cl_code: src/cl_code.cpp
# 	$(CC) $(CFLAGS) -o bin/cl_code.out src/cl_code.cpp -I ./include -lOpenCL

server: src/server.cpp
	$(CC) $(CFLAGS) -o bin/server.out src/server.cpp src/cl_code.cpp -I ./include -lOpenCL

client: src/client.cpp
	$(CC) $(CFLAGS) -o bin/client.out src/client.cpp -I ./include


clean:
	$(RM) bin/cl_code.out bin/server.out bin/client.out

run_server:
	./bin/server.out

run_client:
	./bin/client.out
