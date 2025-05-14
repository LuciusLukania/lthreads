BUILD_DIR := $(abspath ./build)

SUBDIRS := lib app
# DEBUG=1

export CFLAGS :=-std=gnu17 -Wall -Wextra -O0

all: build_dir
	@for dir in $(SUBDIRS); do \
		echo ">>> Building $$dir..."; \
		$(MAKE) -C $$dir BUILD_DIR=$(BUILD_DIR); \
	done

build_dir:
	mkdir -p $(BUILD_DIR)

run:
	make -C app run BUILD_DIR=$(BUILD_DIR)

compile_commands:
	compiledb make

clean:
	@for dir in $(SUBDIRS); do \
		echo ">>> Cleaning $$dir..."; \
		$(MAKE) -C $$dir BUILD_DIR=$(BUILD_DIR) clean; \
	done
