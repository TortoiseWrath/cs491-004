C = gcc
CFLAGS = -Wall -Wextra

PART3_BIN_NAME = proj2
PART4_BIN_PREFIX = proj2

compile: part3 part4_gcc7

part3:
	@$(C) $(CFLAGS) -o $(PART3_BIN_NAME) part3.c

part4_gcc7:
	@gcc $(CFLAGS) -O0 -o $(PART4_BIN_PREFIX)_O0_gcc7 part4.c
	@gcc $(CFLAGS) -O1 -o $(PART4_BIN_PREFIX)_O1_gcc7 part4.c
	@gcc $(CFLAGS) -O2 -o $(PART4_BIN_PREFIX)_O2_gcc7 part4.c
	@gcc $(CFLAGS) -O3 -o $(PART4_BIN_PREFIX)_O3_gcc7 part4.c

part4_gcc5:
	@gcc $(CFLAGS) -O0 -o $(PART4_BIN_PREFIX)_O0_gcc5 part4.c
	@gcc $(CFLAGS) -O1 -o $(PART4_BIN_PREFIX)_O1_gcc5 part4.c
	@gcc $(CFLAGS) -O2 -o $(PART4_BIN_PREFIX)_O2_gcc5 part4.c
	@gcc $(CFLAGS) -O3 -o $(PART4_BIN_PREFIX)_O3_gcc5 part4.c

clean:
	@rm -f $(PART3_BIN_NAME) $(PART4_BIN_PREFIX)_*