dns_resolver: main.o byte_handler.o domain_format.o section_handler.o 
	$(CC) main.o byte_handler.o domain_format.o section_handler.o -o $@

byte_handler.o: byte_handler.c header.h
	$(CC) -Wall -c $< -o $@

domain_format.o: domain_format.c header.h 
	$(CC) -Wall -c $< -o $@

section_handler.o: section_handler.c header.h
	$(CC) -Wall -c $< -o $@

main.o: main.c header.h
	$(CC) -Wall -c $< -o $@

clean:
	rm -f dns_resolver *.o core *~
