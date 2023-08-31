.PHONY: all debug release runcli

all: debug

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug && cd build/debug && make && ./main
	cd ../../
	rm compile_commands.json && ln -s build/debug/compile_commands.json compile_commands.json

release:
	cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release && cd build/release && make && ./main
	cd ../../
	rm compile_commands.json && ln -s build/release/compile_commands.json compile_commands.json

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
	@echo "   make all          -> equivalent to make debug"
	@echo "   make debug        -> build the project in Debug mode"
	@echo "   make release      -> build the project in Release mode"
	@echo "   make help         -> show this help message"
	@echo "**********************************************************"




