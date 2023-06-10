TARGET = px86.exe
OBJS = main.o emulator_function.o instruction.o modrm.o

CC = gcc
CFLAGS += -Wall

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS) Makefile
	$(CC) -o $@ $(OBJS)

.PHONY: clean
clean:
	rm -rf $(OBJS)
