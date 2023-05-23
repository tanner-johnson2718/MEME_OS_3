my_puts: my_puts.c
	gcc -fPIC -c my_puts.c -fno-asynchronous-unwind-tables
	objcopy --remove-section=.note.gnu.property --remove-section=.note.GNU-stack --remove-section=.comment my_puts.o

my_lib: my_puts
	gcc -shared -nostdlib -o libM.so my_puts.o

my_hello: my_hello.c my_lib
	gcc -nostdlib -fno-asynchronous-unwind-tables -I . -L/home/tanner/Desktop/MEME_OS_3/Dynamic_Linking my_hello.c -lM -o test

clean:
	rm -rf *o test *.so