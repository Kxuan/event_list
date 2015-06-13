LDFLAGS += -lrt
el: main.o ontime.o
	$(CC) -o $@ $^ $(LDFLAGS)
clean:
	rm -rf el *.o

.PHONY: clean
