TARGET   ?= run
CC       := gcc
CFLAG_O  := -o
CFLAG_CO := -c -o
BIN_PATH := Sources/bin/
HEADERS  := -IHeaders
OBJS     := main.o\
			tcp_server.o\
			myepoll.o\
			tpool.o\
			mysqlite3.o\
			online.o\
			myfile.o\
			server_func.o

vpath %.c Sources/cpp

$(TARGET): $(OBJS)
	$(CC) $(BIN_PATH)*.o $(CFLAG_O) $@ -lpthread -lsqlite3

%.o: %.c
	$(CC) $< $(HEADERS) $(CFLAG_CO) $(BIN_PATH)$@

.PHONY: clean
clean:
	rm $(TARGET) $(BIN_PATH)*.o -rf