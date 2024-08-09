CC=clang
CFLAGS=
DEPS= printbits.h aes.h
OBJ= multiply.c printbits.c main.c
APPNAME=app

# %.o: %.c $(DEPS)
	# $(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -o $(APPNAME) $(OBJ)

run:
	./$(APPNAME)