CFLAGS += -g -MMD -std=c99 -pedantic -Wall -Wextra

a.out: main.o utils.o map.o set.o priority_queue.o
	$(CC) $^ -o $@

-include *.d

clean:
	$(RM) *.o *.d a.out
