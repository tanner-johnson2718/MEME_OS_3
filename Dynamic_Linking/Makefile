my_puts: my_puts.c
	gcc -c my_puts.c -fno-asynchronous-unwind-tables
	objcopy --remove-section=.note.gnu.property --remove-section=.note.GNU-stack --remove-section=.comment my_puts.o

my_lib: my_puts
	gcc -shared -o my_lib.so my_puts.o

my_hello: my_hello.c my_puts
	gcc -o test my_hello.c my_puts.o

clean:
	rm -rf *o test