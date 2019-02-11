CC = g++
CFLAGS = -Wall -std=c++11
EXEC_NAME = main
INCLUDES =
LIBS =
src = $(wildcard *.cpp)
OBJ_FILES = $(src:.cpp=.o)


all : $(EXEC_NAME)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm *.o main