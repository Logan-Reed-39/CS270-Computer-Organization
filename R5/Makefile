C_OBJS		= main.o hello.o world.o
C_HEADERS	= hello.h world.h
EXE		= R5

CC 		= gcc
CC_FLAGS	= -std=c11 -g -Wall -c
LD_FLAGS	= -std=c11 -g -Wall




#####################################################
#Linking step
R5: $(C_OBJS)
	@echo "Linking..."
	$(CC) $(LD_FLAGS) $(C_OBJS) -o $(EXE)
	@echo "Build complete...."

#Recompile everything if headers are changed

$(C_OBJS): $(C_HEADERS)

#compiling step
%.o: %.c
	@echo "Compiling..."
	$(CC) $(CC_FLAGS) $<

#clean the project
clean:
	rm -rf *.o $(EXE)
	@echo "Clean completed"
