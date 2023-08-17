##************************* Platform dependent definitions ******************##
CC = gcc
AR = ar

DEBUG_FLAGS = -g
OPTIMIZATION = -O2
##***************************************************************************##

##************************* Prerequisite definitions ************************##

CFLAGS += $(OPTIMIZATION)\
          $(DEBUG_FLAGS)\
          -D__LINUX_OS__ \
          -Wall
ROOT_FOLDER = ./
SRC_FOLDER = $(ROOT_FOLDER)/src
SRC_TEST = $(SRC_FOLDER)/polynomial.c $(SRC_FOLDER)/main.c
INC_DIR = -I$(ROOT_FOLDER)/inc 

BIN = $(ROOT_FOLDER)/bin/output.out

##*************************** Library Names and Paths ***********************##
OBJ_TEST = ${SRC_TEST:.c=.o}

##***************************************************************************##


##******************************** Build rules ******************************##
test: $(OBJ_TEST) 
all : $(OBJ_TEST) $(BIN) src_clean
##***************************************************************************##


##************************* Compilation and target creation *****************##

$(OBJ_TEST): %.o : %.c
	$(CC) -c $(CFLAGS) $(INC_DIR) $*.c -o $*.o


$(BIN): $(OBJ_TEST)
	$(CC) -o $@ $(OBJ_TEST) 

##***************************************************************************##


##**************************** Clean rule ***********************************##
clean: src_clean
	rm -fv $(BIN) *.debug *.o core

src_clean:
	rm -fv   $(OBJ_TEST)
	rm -fv   *.o

##***************************************************************************##
