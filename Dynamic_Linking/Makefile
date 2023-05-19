my_puts: my_puts.c
	gcc -fPIC -c my_puts.c -fno-asynchronous-unwind-tables
	objcopy --remove-section=.note.gnu.property --remove-section=.note.GNU-stack --remove-section=.comment my_puts.o

my_lib: my_puts
	gcc -shared -o my_lib.so my_puts.o
	sudo cp my_lib.so /usr/lib64
	sudo ldconfig

my_hello: my_hello.c my_lib
	gcc -I . -o test my_hello.c -lmy_puts

clean:
	rm -rf *o test *.so
	sudo rm /usr/lib64/my_lib.so