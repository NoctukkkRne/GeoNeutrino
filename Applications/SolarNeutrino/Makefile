.SECONDARY:

# the directories of the program
TOP := $(shell pwd)/
BUILD := $(TOP)build/
INCLUDE := $(TOP)include/
SRC := $(TOP)src/
BIN := $(TOP)bin/
OBJ := $(BUILD)obj/
TAR_OBJ := $(BUILD)tar_obj/

COM := $(shell pwd)/../Common/
COM_BUILD := $(COM)build/
COM_INCLUDE := $(COM)include/
COM_SRC := $(COM)src/
COM_OBJ := $(COM_BUILD)obj/

# add the includes
add_includes = -I$(INCLUDE)
# add_includes += -I$(COM_INCLUDE)

# find the CXX libraries
CXXLIBS += $(shell root-config --libs)
#CXXLIBS += $(shell geant4-config --libs) -Wl,-rpath,${GEANT4SYS}/lib

# decide the compile
CXX = g++

# add the cflags
#CXXFLAGS = -O -w -fPIC $(add_includes)
CXXFLAGS = -O -Wall -fPIC $(add_includes)
CXXFLAGS += $(shell root-config --cflags)
#CXXFLAGS += $(shell geant4-config --cflags)

# the files of the program
headers = $(wildcard $(INCLUDE)*.h)
sources = $(wildcard $(SRC)*.C)
objects = $(patsubst $(SRC)%.C, $(OBJ)%.o, $(sources))
tar_src = $(wildcard $(TOP)*.C)
targets = $(patsubst $(TOP)%.C, $(BIN)%, $(tar_src))

com_hed = $(wildcard $(COM_INCLUDE)*.h)
com_src = $(wildcard $(COM_SRC)*.C)
com_obj = $(patsubst $(COM_SRC)%.C, $(COM_OBJ)%.o, $(com_src))

all: $(targets)

####################### Make Executables #########################

$(BIN)%: $(TAR_OBJ)%.o $(objects) $(com_obj)
	$(CXX) $^ $(CXXLIBS) -o $(BIN)$(notdir $@)

######################## Make Objects ############################

-include $(TAR_OBJ)*.d
$(TAR_OBJ)%.o: $(TOP)%.C
	$(CXX) $(CXXFLAGS) -c -MMD $(TOP)$(notdir $<) -o $(TAR_OBJ)$(notdir $@)

-include $(OBJ)*.d
$(OBJ)%.o: $(SRC)%.C
	$(CXX) $(CXXFLAGS) -c -MMD $(SRC)$(notdir $<) -o $(OBJ)$(notdir $@)

######################### Make Clean #############################

.PHYONY: clean
clean:
	rm -rf $(OBJ)*.o
	rm -rf $(OBJ)*.d
	rm -rf $(TAR_OBJ)*.o
	rm -rf $(TAR_OBJ)*.d
	rm -rf $(BIN)*


.PHYONY: gen_json
gen_json:
	@rm -rf build/compile_commands.json
	@echo "[" >> build/compile_commands.json
	@echo "  {" >> build/compile_commands.json
	@echo "    \"directory\": \"$(BUILD)\"," >> ./build/compile_commands.json
	@echo "    \"command\": \"$(CXX) $(CXXFLAGS)\"," >> ./build/compile_commands.json
	@echo "    \"file\": \"\"" >> ./build/compile_commands.json
	@echo "  }" >> build/compile_commands.json
	@echo "]" >> build/compile_commands.json
