# Compiler
CC = g++
CFLAGS = -std=c++17

# Files
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = program

# Targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
