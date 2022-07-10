output: driver.o 
	gcc -w -O3 driver.o -o compiler

lexer.o: lexer.c 
	gcc -w -c -g lexer.c

parser.o: lexer.c parser.c 
	gcc -w -c -g parser.c

symboltable.o:  parser.c symboltable.c
	gcc -w -c -g symboltable.c

codegenerator.o : symboltable.c codegenerator.c 
	gcc -w -c -g codegenerator.c

driver.o: codegenerator.c driver.c 
	gcc -w -c -g driver.c

clean:
	rm *.o

