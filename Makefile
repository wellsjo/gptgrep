CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -O2
SRC = gpt_grep.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = gpt_grep

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJ) $(EXEC)