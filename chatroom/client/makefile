TARGET   ?= run
CC       := gcc
CFLAG_O  := -o
CFLAG_CO := -c -o
BIN_PATH := Sources/bin/
HEADERS  := -IHeaders
OBJS     := main.o\
			tcp_client.o\
			myfile.o\
			admin.o\
			client_func.o
			

vpath %.c Sources/cpp

$(TARGET): $(OBJS)
	$(CC) $(BIN_PATH)*.o $(CFLAG_O) $@ -lpthread

%.o: %.c
	$(CC) $< $(HEADERS) $(CFLAG_CO) $(BIN_PATH)$@

.PHONY: clean
clean:
	rm $(TARGET) $(BIN_PATH)*.o -rf