debug:
	gcc roman_to_dec.c -o roman_to_dec -DDEBUG
	gcc dec_to_roman.c -o dec_to_roman -DDEBUG

all:
	gcc roman_to_dec.c -o roman_to_dec
	gcc dec_to_roman.c -o dec_to_roman

clean: 
	rm roman_to_dec roman_to_dec.exe dec_to_roman dec_to_roman.exe *.txt