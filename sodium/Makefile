CFLAGS := -Wall -Wextra -Werror -g -O0
COBJS := build/main.o build/serror.o build/lexer.o build/parser.o build/interpreter.o

build/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $^ -o $@ -c -Iinclude $(CFLAGS)

build/sodium: $(COBJS)
	@mkdir -p $(@D)
	@$(CC) $^ -o $@ -Iinclude $(CFLAGS)

all: build/sodium
