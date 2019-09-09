
HEAD_PATH = ./include
LIB_FLAGS = -I $(HEAD_PATH)

#需要事先安装  opencv3.4.3  libjpeg-dev libpng-dev
#OPENCV_FLAGS =`pkg-config --libs --cflags opencv`  -ljpeg -lpng


CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
COMPILE_FLAGS = -g -fPIC -lpthread -std=c++11

all:main

main:main.cpp
	$(CPP)  $^ -o $@  -L ./ -lusbdriver $(LIB_FLAGS)   $(COMPILE_FLAGS)  $(OPENCV_FLAGS)

clean:
	rm -rf main
