SRC = main.c

APP_BIN=$(BUILD_DIR)/lthreads_app
CFLAGS+=-I../lib
LIB+=$(BUILD_DIR)/liblthread.a

ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

$(APP_BIN): $(BUILD_DIR) $(SRC)
	gcc $(SRC) $(LIB) $(CFLAGS) -o $@

run:
	$(APP_BIN)

clean:
	rm -f $(APP_BIN)
