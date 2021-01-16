CC      := gcc
LD      := ld
BIN     := bin
SRCS    := $(wildcard *.c)
EXE     := $(BIN)/vm
CFLAGS  := -Wall -Ofast -s
LIBS    := 
ifeq ($(OS),Windows_NT)
	LIBS := $(LIBS) -lws2_32
endif

.PHONY: clean

all: $(EXE)

$(EXE): $(SRCS) | $(BIN)
	$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $@
run:
	$(EXE)

clean:
	rm -rf bin/*

upload:
	scp -r /home/ryan/chiphttp/* ryan@192.168.0.100:/home/ryan/chipdrive