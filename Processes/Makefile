proc: proc.c
	make -C ../MEME_Lib/
	gcc -I ../MEME_Lib/ -nostdlib -fno-asynchronous-unwind-tables -static -o proc proc.c ../MEME_Lib/lib_meme.o

clean:
	rm -rf proc
	make clean -C ../MEME_Lib/