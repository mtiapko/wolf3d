CMD_DEFINES := $(addprefix -D, $(DEF))
CFLAGS := -c -g -I./include $(CMD_DEFINES) -MMD -MP -Wall -Wextra -pedantic -std=c99
LDFLAGS := -lm -lSDL2 -lGLEW -lGL 

OUT := wolf3d

SRC_DIR := src
OBJ_DIR := bin

SRC := $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

.PHONY: 
	all \
	run \
	print_build \
	print_success \
	clean \
	del \
	re

all: print_build $(OUT) print_success

run: all
	@ ./$(OUT)

print_build:
	@echo -e "\n\t\e[1;97m### BUILDING \e[96m$(OUT) \e[97m###\e[0m\n"

print_success:
	@if [ "$$?" == "0" ]; then \
		echo -e "\n\t\e[1;97m### \e[92mSUCCESS \e[97m###\e[0m\n"; \
	fi

$(OUT): $(OBJ)
	gcc $(OBJ) $(LDFLAGS) -o $(OUT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc $^ $(CFLAGS) -MF $@.d -o $@

clean:
	@rm -rf $(OBJ_DIR)

del: clean
	@rm -f $(OUT)

re: del all
