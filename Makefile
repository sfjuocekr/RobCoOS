PROJECT_DIR	= .
USER_LIB_PATH	:= $(PROJECT_DIR)/lib
USER_LIB_PATH	:= /home/sjoer/sketchbook/libraries/
BOARD_TAG	= mega2560
#CPPFLAGS	= -pedantic -Wall -Wextra -Wno-variadic-macros
CURRENT_DIR	= $(shell basename $(CURDIR))
OBJDIR		= $(PROJECT_DIR)/bin
#ARDUINO_DIR	= /usr/share/arduino
ARDMK_DIR	= $(PROJECT_DIR)/mk
include $(ARDMK_DIR)/Arduino.mk

