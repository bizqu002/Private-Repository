
Student name and ID: Brenda Sofia Izquierdo Valenzuela   3886796



Operating system: Linux (Ubuntu 14.04 LTS)



Programing language: C



Compiling instructions: 
1. Open a terminal and cd to the parent folder where the source code is
2. Type "make" (without quotations)
e.g. (supposing the source code is located in Desktop):
user@ubuntu:~$ cd Desktop
user@ubuntu:~/Desktop$ make
cc -Wall -c handle_client.c -o handle_client.o
cc handle_client.o main.o -o ftp
user@ubuntu:~/Desktop$



Running instructions: 
1. Type "./ftp port_number" (without quotations as well & port_number could be any number greater than 1023, e.g. 1024)
2. Open a new terminal
3. Type "ftp machine_name port_number" (without quotations as well & machine_name is the name of the machine & port_number the same as in step 1) 
4. When asked for name, enter any string
5. When asked for password, enter the same string as in step 4
6. Enter commands cd, pwd, mkdir, get, put, delete or quit with corresponding parameters

  *To run server with more than one client:
	- Open another terminal (no need to close any of the previous terminals)
	- Repeat steps 3 to 6 (machine_name & port_number are still the same)





