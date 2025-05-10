SRC = main.c

APP_BIN=$(BUILD_DIR)/lthreads_app

$(APP_BIN): $(BUILD_DIR) $(SRC)
	gcc -o $@ $(SRC)

run:
	$(APP_BIN)

clean:
	rm -f $(APP_BIN)
