
HEAD_PATH = ./include
LIB_FLAGS = -I $(HEAD_PATH)

#need to install  opencv3.4.3  libjpeg-dev libpng-dev
#OPENCV_FLAGS =`pkg-config --libs --cflags opencv`  -ljpeg -lpng

OPENCV_FLAGS ?=

CROSS_COMPILE ?= aarch64-linux-gnu-
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
COMPILE_FLAGS = -g -fPIC -lpthread -std=c++11


all:main

main:main.c
	$(CPP)  $^ -o $@  -L ./ -lusbdriver $(LIB_FLAGS)   $(COMPILE_FLAGS)  $(OPENCV_FLAGS)

clean:
	rm -rf main
