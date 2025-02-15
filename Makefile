PROJECT = cnc_software

CXX = g++
CXXFLAGS = -Wall -std=c++21

SRC_DIR = src
OBJ_DIR = build
MOCK_DIR = mock
ARCH_DIR = arch/rpi3


UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	PLATFORM_SRC = $(MOCK_DIR)/wiringMac.cpp
	CXXFLAGS += -D__APPLE__
else
	PLATFORM_SRC = -lwiringPi
endif

CXXFLAGS += -I$(ARCH_DIR)

SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(PLATFORM_SRC)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(PROJECT)

$(PROJECT): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/