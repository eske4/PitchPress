# The build directory
BUILD_DIR = build
EXECUTABLE = PitchPress
COMPILE_COMMANDS = $(BUILD_DIR)/compile_commands.json

# Declare build as a phony target to ensure it's always executed
.PHONY: all build clean test copy_compile_commands debugBuild runBuild run

# Default target: configure and build the project
all: build symlink_compile_commands

# Build the project inside the build directory
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && cmake --build .

# Custom target to copy compile_commands.json to the root directory
symlink_compile_commands:
	@if [ -f $(COMPILE_COMMANDS) ]; then \
		ln -sf $(COMPILE_COMMANDS) ./compile_commands.json; \
		echo "Created symlink for compile_commands.json in root directory."; \
	else \
		echo "compile_commands.json not found."; \
	fi

debugBuild:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ..

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)
	echo "Build directory cleaned."

# Run the tests (if you have tests set up with CTest)
test:
	cd $(BUILD_DIR)/tests && ctest

runBuild:
	cd $(BUILD_DIR) && make && ./app/$(EXECUTABLE)

run:
	cd $(BUILD_DIR) && ./app/$(EXECUTABLE)
