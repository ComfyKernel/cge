SHELL=/bin/bash

ORIGIN  := $(realpath .)
SOURCE  := $(ORIGIN)/source
INCLUDE := $(ORIGIN)/include
OUT     := $(ORIGIN)/build

C   := gcc
CXX := g++

CFLAGS   := -std=c++17 -I$(INCLUDE) -O0 -Wall -Wextra
CXXFLAGS := $(CFLAGS)

L_END := "\e[0m"
L_INF := "\e[32m[INFO]"$(L_END)

export C
export CXX

export CFLAGS
export CXXFLAGS

export ORIGIN
export INCLUDE
export OUT

all: info

info:
	@echo -e $(L_INF) "Using path              :" $(ORIGIN)
	@echo -e $(L_INF) "Kernel       (uname -r) :" $(shell uname -a)
	@echo -e $(L_INF) "Architecture (uname -m) :" $(shell uname -m)
	$(MAKE) src

src:
	$(MAKE) -C $(SOURCE)

runtest:
	LD_LIBRARY_PATH=$(OUT) $(OUT)/cgetester
