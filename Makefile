
##################################################
#                                                #
#      █▀▄▀█ ▄▀█ █▄▀ █▀▀   █▀▀ █ █░░ █▀▀         #
#      █░▀░█ █▀█ █░█ ██▄   █▀░ █ █▄▄ ██▄         #
#                                                #
##################################################
# Variables
BINARY_NAME=main
BINARY_TEST_NAME=my_test
NUMBER_CORES=8
SDL2_DIR = $(HOMEBREW_DIR)/sdl2/2.28.5
SDL2_IMAGE_DIR = $(HOMEBREW_DIR)/sdl2_image/2.6.3_2
SOURCES = src/main.cpp src/lib/veclib/lib/vector2d.cpp ./src/lib/veclib/lib/vect.cpp
OUTPUT = build/debug/${BINARY_NAME}

# Phony target since 'runcli' isn't a file
.PHONY: all debug release run


all: debug_using_ninja

debug: link_compile_commands
	@cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake  -S . -B build/debug
	$(MAKE) -j $(NUMBER_CORES) -C build/debug
	./build/debug/$(BINARY_NAME)

release: link_compile_commands
	@cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake  -S . -B build/release
	$(MAKE) -j $(NUMBER_CORES) build/release
	./build/debug/$(BINARY_NAME)

debug_using_ninja: link_compile_commands
	@cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/opt/homebrew/bin/ninja \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-G Ninja -S . \
		-B ./build/debug
	/opt/homebrew/bin/ninja -j${NUMBER_CORES} -C build/debug
	./build/debug/$(BINARY_NAME)


release_using_ninja: link_compile_commands
	@cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=/opt/homebrew/bin/ninja \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-G Ninja -S . \
		-B ./build/release
	/opt/homebrew/bin/ninja -j${NUMBER_CORES} -C build/release
	./build/release/$(BINARY_NAME)

# -------------------------------------------------------------------------
#                      TESTING (GOOGLE TEST MODULE)
#      ./build/test/tests/$(BINARY_TEST_NAME);deprecated in favor of ctest \
# -------------------------------------------------------------------------
test:
	@if [ -n "$(BINARY_TEST_NAME)" ] && [ -f "./build/test/tests/$(BINARY_TEST_NAME)" ]; then \
		GTEST_COLOR=1 ctest --test-dir build/test/ --output-on-failure -j${NUMBER_CORES}; \
	else \
		cmake -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Test \
		-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake \
		-DCMAKE_MAKE_PROGRAM=/opt/homebrew/bin/ninja \
		-G Ninja -S . -B ./build/test; \
		/opt/homebrew/bin/ninja -j${NUMBER_CORES} -C ./build/test; \
		if [ -L compile_commands.json ]; then \
			rm -f compile_commands.json; \
		fi; \
		ln -s build/test/compile_commands.json compile_commands.json; \
		GTEST_COLOR=1 ctest --test-dir build/test/ --output-on-failure -j${NUMBER_CORES}; \
	fi
# -------------------------------------------------------------------------
# For the clangd language server integration
link_compile_commands:
	@if [ -L compile_commands.json ]; then \
		rm -f compile_commands.json; \
	fi
	@ln -s build/debug/compile_commands.json compile_commands.json

# Run Command - will not be maintained, as the project will grow later
run: $(OUTPUT)
	./$(OUTPUT)
	@$(MAKE) link_compile_commands

$(OUTPUT): $(SOURCES)
	mkdir -p ./build/debug
	clang++ -v -std=c++17 \
	-I$(SDL2_DIR)/include/SDL2/ \
	-I$(SDL2_IMAGE_DIR)/include/SDL2/ \
	-I$(HOME)vcpkg/packages/gflags_arm64-osx/include \
	-I$(HOME)vcpkg/packages/glog_arm64-osx/include \
	-L$(SDL2_DIR)/lib -lSDL2 \
	-L$(SDL2_IMAGE_DIR)/lib -lSDL2_image \
	-L$(HOME)vcpkg/packages/gflags_arm64-osx/lib -lgflags \
	-L$(HOME)vcpkg/packages/glog_arm64-osx/lib -lglog \
	-o $@ $(SOURCES)

# Cleaning the build from the current project by deleting both the debug and
# release directories.
clean:
	@rm -rf build .cache
	@rm -rf vcpkg-manifest-install.log \
		vcpkg_installed CMakeCache.txt \
		cmake_install.cmake CMakeFiles \
		compile_commands.json .idea cmake-build-debug
	@rm -rf src/logs/*

clean_dependencies:
	@rm -rf ./dependencies

help:
	@echo "\033[35m ********************************************************\033[0m"
	@echo ""
	@echo "\033[31m      ░█▀▀█ █▀▀▄ ░▀░ █▀▄▀█ █▀▀█ ▀▀█▀▀ ░▀░ █▀▀█ █▀▀▄ 　\033[0m"
	@echo "\033[31m      ▒█▄▄█ █░░█ ▀█▀ █░▀░█ █▄▄█ ░░█░░ ▀█▀ █░░█ █░░█ 　\033[0m"
	@echo "\033[31m      ▒█░▒█ ▀░░▀ ▀▀▀ ▀░░░▀ ▀░░▀ ░░▀░░ ▀▀▀ ▀▀▀▀ ▀░░▀ 　\033[0m"
	@echo "\033[31m               ▒█▀▀▀ █▀▀▄ █▀▀▀ ░▀░ █▀▀▄ █▀▀           \033[0m"
	@echo "\033[31m               ▒█▀▀▀ █░░█ █░▀█ ▀█▀ █░░█ █▀▀           \033[0m"
	@echo "\033[31m               ▒█▄▄▄ ▀░░▀ ▀▀▀▀ ▀▀▀ ▀░░▀ ▀▀▀           \033[0m"
	@echo ""
	@echo "\033[35m ********************************************************\033[0m"
	@echo "Available commands:"
	@echo "\033[32m   make all                       \033[0m   - equivalent to make debug"
	@echo "\033[32m   make debug                     \033[0m   - build the project in Debug mode"
	@echo "\033[32m   make release                   \033[0m   - build the project in Release mode"
	@echo "\033[32m   make run                       \033[0m   - build and run the project using Clang compiler"
	@echo "\033[32m   make clean                     \033[0m   - clean build and other artifacts"
	@echo "\033[32m   make test                      \033[0m   - Run all tests in [tests] module"
	@echo ""
	@echo "NOTE: Run Command - will not be maintained, as the project will grow later"
	@echo "\033[35m ********************************************************\033[0m"
