CC = gcc
CFLAGS  = -g -Wall

default: tests

tests:  all_tests.c spi_command_tests.h encoder_tests.h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean run
run: tests
	./tests

clean: 
	$(RM) tests *.o *~
