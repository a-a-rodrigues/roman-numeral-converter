all:
	gcc num_to_dec.c -o num_to_dec

debug:
	gcc num_to_dec.c -o num_to_dec -DDEBUG

clean: 
	rm num_to_dec num_to_dec.exe