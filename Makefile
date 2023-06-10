TARGET = px86.exe
OBJS = main.o emulator_function.o instruction.o modrm.o io.o

CC = gcc
RM = rm
CFLAGS += -Wall
RMFLAGS += -rf

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS) Makefile
	$(CC) -o $@ $(OBJS)

.PHONY: clean
clean:
	$(RM) $(RMFLAGS) $(OBJS)
