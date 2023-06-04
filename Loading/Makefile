cmd: cmd_args.c
	gcc -o cmd cmd_args.c

no_lib: no_lib.c
	gcc -nostdlib -static  -fno-asynchronous-unwind-tables -o no_lib no_lib.c

hello: hello.c
	gcc -o hello hello.c

clean: 
	rm -rf cmd no_lib hello