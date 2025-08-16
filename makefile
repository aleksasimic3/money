MAKEFLAGS += -j2

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude -lcurl

BIN_DIR = bin
SRC_DIR = src
INC_DIR = include

$(BIN_DIR)/money.exe: main.o money.o
	$(CXX) -o $@ $^ $(CXXFLAGS)

main.o: $(SRC_DIR)/main.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

money.o: $(SRC_DIR)/money.cpp $(INC_DIR)/money.h
	$(CXX) -c -o $@ $<  $(CXXFLAGS)