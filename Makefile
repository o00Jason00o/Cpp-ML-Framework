# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude
SRCS = src/dataset/Dataset.cpp src/dataset/DataLoader.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = ml_app

# Targets
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q /F $(subst /,\,$(OBJS)) $(TARGET).exe

run: $(TARGET)
	./$(TARGET) sample_data.csv

test: $(TARGET)
	# Insert command to run your test cases here

.PHONY: all clean run test
