CC = g++
CXXFLAGS = -std=c++11 -pedantic -Wall
LIBFLAGS = -lssl -lcrypto -lpthread
NAME = servidor
SRC_PATH=src
OUT_PATH=.

all : $(NAME)

$(NAME) :
	$(CC) $(CXXFLAGS) $(SRC_PATH)/main.cpp\
	 $(SRC_PATH)/BindingSocket.cpp \
	 $(SRC_PATH)/Socket.cpp \
	 $(SRC_PATH)/Cache.hpp \
	 $(SRC_PATH)/ThreadPool.cpp \
	 $(SRC_PATH)/ServerThreadPool.cpp \
	 $(SRC_PATH)/utility.cpp \
	 $(SRC_PATH)/Server.cpp -o $(OUT_PATH)/$(NAME) $(LIBFLAGS)

clean :
	rm $(OUT_PATH)/$(NAME)
