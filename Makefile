##################################################
#                                                #
#      █▀▄▀█ ▄▀█ █▄▀ █▀▀   █▀▀ █ █░░ █▀▀         #
#      █░▀░█ █▀█ █░█ ██▄   █▀░ █ █▄▄ ██▄         #
#                                                #
##################################################
# Variables
BINARY_NAME=main
NUMBER_CORES=8
SOURCES = src/main.cpp src/lib/Employee.cpp
INCLUDE_DIR = -Isrc/lib
OUTPUT = build/debug/main

# Phony target since 'runcli' isn't a file
.PHONY: all debug release run


all: debug

debug: link_compile_commands
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
	$(MAKE) -j $(NUMBER_CORES) -C build/debug
	./build/debug/$(BINARY_NAME)

release: link_compile_commands
	cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release
	$(MAKE) -j $(NUMBER_CORES) build/release
	./build/debug/$(BINARY_NAME)

# For the clangd language server integration
link_compile_commands:
	if [ -L compile_commands.json ]; then \
		rm -f compile_commands.json; \
	fi
	ln -s build/debug/compile_commands.json compile_commands.json

# This will run the code using make, no need to use CMakeList.txt/cmake
run: $(OUTPUT)
	./$(OUTPUT)
	@$(MAKE) link_compile_commands

$(OUTPUT): $(SOURCES)
	clang++ -std=c++17 \
  	$(INCLUDE_DIR)
	-o $@ $(SOURCES)

clean:
	rm -rf ./build/



help:
	@echo "**********************************************************"
	@echo "       ▒█▀▀▀ █▀▄▀█ █▀▀█ █░░ █▀▀█ █░░█ █▀▀ █▀▀ 　  "
	@echo "       ▒█▀▀▀ █░▀░█ █░░█ █░░ █░░█ █▄▄█ █▀▀ █▀▀ 　  "
	@echo "       ▒█▄▄▄ ▀░░░▀ █▀▀▀ ▀▀▀ ▀▀▀▀ ▄▄▄█ ▀▀▀ ▀▀▀ 　  "
	@echo "                                                     "
	@echo "       ▒█▀▀█ █▀▀ █▀▀▄ █▀▀ █▀▀█ █▀▀█ ▀▀█▀▀ █▀▀█ █▀▀█  "
	@echo "       ▒█░▄▄ █▀▀ █░░█ █▀▀ █▄▄▀ █▄▄█ ░░█░░ █░░█ █▄▄▀  "
	@echo "       ▒█▄▄█ ▀▀▀ ▀░░▀ ▀▀▀ ▀░▀▀ ▀░░▀ ░░▀░░ ▀▀▀▀ ▀░▀▀ "
	@echo ""
	@echo "          Available Commands: ->                          "
	@echo "          Author: Ghasak Ibrahim                          "
	@echo "**********************************************************"
	@echo " [1]  make all     -> equivalent to make debug"
	@echo " [2]  make debug   -> build the project in Debug mode"
	@echo " [3]  make release -> build the project in Release mode"
	@echo " [4]  make help    -> show this help message"
	@echo "**********************************************************"

