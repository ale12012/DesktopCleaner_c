all:
	mkdir -p exec slib
	gcc -c src/cleanerfuncs.c -o slib/cleanerfuncs.o
	ar rcs slib/libcleanerfuncs.a slib/cleanerfuncs.o
	gcc main.c -o exec/desktopcleaner -Lslib -lcleanerfuncs
	rm -f slib/*.o

compile:
	gcc main.c -o exec/desktopcleaner -Lslib -lcleanerfuncs

uninstall:
	rm -rf exec slib