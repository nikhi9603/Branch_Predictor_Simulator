CC = g++

srcDir := src/
includeDir := include/

srcfiles := bimodal.cpp bp_simulator.cpp bp_utils.cpp gshare.cpp main.cpp trace.cpp 
src_files := $(addprefix $(srcDir), $(srcfiles))
executable_file := bpsim

all: $(executable_file)

$(executable_file) : $(src_files)
	$(CC) -g $^ -I $(includeDir) -o $@

clean:
	rm -f $(executable_file)