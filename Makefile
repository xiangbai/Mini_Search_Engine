SRC_DIR:=./src
INC_DIR:=./include
EXE_DIR:=./bin
CPPFLAGS := -g -o
CC:=g++
TARGET:=$(EXE_DIR)/main
OBJS:=$(SRC_DIR)/search_main.cpp $(SRC_DIR)/Socket.cpp
$(TARGET):$(OBJS) $(INC_DIR)/Socket.h
	$(CC) $(CPPFLAGS) $@ $(OBJS) -I$(INC_DIR) -ljson