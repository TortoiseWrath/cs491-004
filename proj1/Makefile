C = gcc
CFLAGS = -O3 -Wall -Wextra

BIN_NAME = proj1
N = 64 128 256 512 1024 2048

test: compile
	@for n in 64 128 256 512 1024 2048; do \
		echo "Testing n=$$n" ; \
		./${BIN_NAME} $$n ; \
		echo ; \
	done

compile:
	@$(C) $(CFLAGS) -o $(BIN_NAME) proj1.c

clean:
	@rm -f $(BIN_NAME)
