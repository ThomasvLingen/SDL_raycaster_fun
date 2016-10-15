# Files to compile
SRC_PATH = src/
RAYCASTER_SRC = $(wildcard $(SRC_PATH)*.cpp)
RAYCASTER_OBJS = $(RAYCASTER_SRC:.cpp=.o)
# Compiler
CC = g++

# Compiler flags
# -w =  supress warnings
COMPILER_FLAGS = -w -std=c++11

# LINKER_FLAGS
# -lsSDL2 for SDL2
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

# Name of the resulting file
EXEC = build/vidya

SILENT = @

# Compile stuff
%.o : %.cpp
	@echo CC $<
	$(SILENT) $(CC) -c $< $(COMPILER_FLAGS) -o $@

$(EXEC) : $(RAYCASTER_OBJS)
	@echo
	mkdir -p build
	@echo LD $@
	$(SILENT) $(CC) $(COMPILER_FLAGS) $(RAYCASTER_OBJS) $(LINKER_FLAGS) -o $(EXEC)
	@echo
	@echo "Moving resources to bin"
	cp -r res build
	cp SDL2.dll build
	@echo

all : $(EXEC)

run : $(EXEC)
	$(EXEC)

# Kind cleaning lady
.PHONY: clean
clean:
	@echo "Hi, I'm here to clean up your project!"
	rm -rf $(SRC_PATH)*.o
	rm -rf build/*
