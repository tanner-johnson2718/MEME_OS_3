my_puts: my_puts.S
	as my_puts.S -o my_puts.o

my_hello: my_hello.c my_puts
	gcc -o test my_hello.c my_puts.o

clean:
	rm -rf *o test