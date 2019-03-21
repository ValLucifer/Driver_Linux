
HEAD_PATH = ./include
LIB_FLAGS = -I $(HEAD_PATH)

OPENCV_FLAGS =`pkg-config --libs --cflags opencv`  -ljpeg -lpng
LIBUDEV_FLAGS =  -ludev

CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
COMPILE_FLAGS = -g -fPIC -lpthread -std=c++11

all:main

main:main.c
	$(CPP)  $^ -o $@  -L ./ -lusbdriver $(LIB_FLAGS)  $(LIBUDEV_FLAGS)  $(COMPILE_FLAGS)  $(OPENCV_FLAGS)

clean:
	rm -rf main
