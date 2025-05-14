$(info "$(BUILD_DIR)")
LTHREAD_LIB=$(BUILD_DIR)/liblthread.a
SRC_DIR= .

ifeq ($(DEBUG), 1)
	CFLAGS += -g -DDEBUG
endif

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

$(LTHREAD_LIB): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@ -I.

clean:
	rm -f $(OBJ)

