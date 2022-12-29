lista_xor.o: lista_xor.h lista_xor.c
	gcc -Wall -c lista_xor.c -o lista_xor.o
	
proy2.o: proy2.c lista_xor.h
	gcc -Wall -c proy2.c -o proy2.o
	
proy2: proy2.o lista_xor.o
	gcc -Wall proy1.o lista_xor.o -o proy2	
		
