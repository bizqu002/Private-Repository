ftp: handle_client.o main.o 
	$(CC) handle_client.o main.o -o $@

handle_client.o: handle_client.c ftp.h
	$(CC) -Wall -c $< -o $@

main.o: main.c ftp.h
	$(CC) -Wall -c $< -o $@

clean:
	rm -f ftp *.o core *~
