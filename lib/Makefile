$(info "$(BUILD_DIR)")
LTHREAD_LIB=$(BUILD_DIR)/lthread.a
SRC_DIR= .

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

$(LTHREAD_LIB): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@ -I.

clean:
	rm -f $(OBJ)

