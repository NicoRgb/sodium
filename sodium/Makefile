CFLAGS := -Wall -Wextra -Wpedantic -Werror -g -O0
COBJS := build/main.o

build/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $^ -o $@ -c -Iinclude $(CFLAGS)

build/sodium: $(COBJS)
	@mkdir -p $(@D)
	@$(CC) $^ -o $@ -Iinclude $(CFLAGS)

all: build/sodium
