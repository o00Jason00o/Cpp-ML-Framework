# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude

# Automatically detect source files
SRCS = $(wildcard src/dataset/*.cpp src/algorithms/*.cpp src/utils/*.cpp src/evaluation/*.cpp main.cpp)
OBJS = $(SRCS:.cpp=.o)
TARGET = ml_app

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# General rule for compiling object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q /F $(subst /,\,$(OBJS)) $(TARGET).exe

run: $(TARGET)
	./$(TARGET) sample_data.csv

test: $(TARGET)
	# Insert command to run your test cases here

.PHONY: all clean run test
