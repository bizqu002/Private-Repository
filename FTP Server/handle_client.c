#include "ftp.h"

void handle_client(int sock)
{
	int n = 0, x = 0, y = 0, z = 0, compare = 0;;
	char buffer[BUFSIZ], login_user[BUFSIZ], login_password[BUFSIZ], buff1[BUFSIZ], buff2[BUFSIZ];
	
	
	// Ask for the username	
	n = send(sock, "220 (mY FtP SeRvEr)\r\n", 21, 0); 
	if(n < 0)
	{
		close(sock);
	}
	x = read(sock, login_user, sizeof(login_user));
	if(x < 0)
	{
		//perror("server: can't receive from client");
		close(sock);
	}
	else
	{
		login_user[x] = '\0';	
	}
	strncpy(buff1, login_user + 5, strlen(login_user)-7); //this copies only the username taking out surplus characters
	
	
	// Ask for password	
	n = send(sock, "331 Please specify the password.\r\n", 34, 0); 
	if(n < 0)
	{
		close(sock);
	}
	y = read(sock, login_password, sizeof(login_password));
	if(y < 0)
	{
		//perror("server: can't receive from client");
		close(sock);
	}
	else
	{
		login_password[y] = '\0';
	}
	strncpy(buff2, login_password + 5, strlen(login_password)-7); //this copies only the password taking out surplus characters


	// If username and password are the same, grant access, else exit connection
	compare = strcmp(buff1, buff2);
        if(compare == 0)
	{
		n = send(sock, "230 Login successful.\r\n", 23, 0);	
		if(n < 0)
		{
			close(sock);
		}	
	} 
	else
	{
		n = send(sock, "530 Login incorrect.\r\n", 22, 0); 
		if(n < 0)
		{
			close(sock);
		}
	}

	z = recv(sock, buffer, sizeof(buffer), 0);                

	if(z < 0) 
	{
		//perror("server: can't receive from client");  
		close(sock);      
	}
	else
	{ 
		buffer[z] = '\0';
	}
	              
	if(strncmp(buffer, "SYST", 4) == 0)
	{
		n = send(sock, "215 Unix\r\n", 10, 0);
		if(n < 0)
		{
			close(sock);
		}

		// Set working directory of client as the root directory
		char cwd[BUFSIZ];			
		if(getcwd(cwd, BUFSIZ) != NULL)
			chroot(cwd);
		else
		{
			perror("Could not get root directory");
			close(sock);
		}
	}
	
		
	// While there is a connection and login is succesful
	for(;;)  
	{
		char aux_buffer[BUFSIZ];
		int fd, new_sock, a, b, m;		
		
		a = recv(sock, buffer, sizeof(buffer), 0);
		if(a < 0) 
		{
			//perror("server: can't receive from client");  
			close(sock);      
		}
		else
		{ 
			buffer[a] = '\0';
			//printf("BUFFER %s\n", buffer);
		}
		
		// MKDIR COMMAND 
		if(strncmp(buffer, "MKD ", 4) == 0)
		{
			char *remote_path = strtok(buffer, " ");
			remote_path = strtok(NULL, " ");
			remote_path[strlen(remote_path)-2] = '\0';
			b = mkdir(remote_path, 0777);
			if(b < 0)
			{
				perror("Couldn't create directory");
				close(sock);
			}
			else
			{
				sprintf(aux_buffer, "257 \"%s\" created\r\n", remote_path);
				m = send(sock, aux_buffer, sizeof(aux_buffer), 0);
				if(m < 0) 
				{
					//perror("server: can't receive from client");  
					close(sock);      
				}	
			}
		}

		// DELETE COMMAND (enter remote path, not just file name)
		if(strncmp(buffer, "DELE ", 5) == 0)
		{
			char *remote_path = strtok(buffer, " ");
			remote_path = strtok(NULL, " ");
			remote_path[strlen(remote_path)-2] = '\0';
			b = remove(remote_path);
			if(b == 0)
			{
				m = send(sock, "250 Delete operation succesful.\r\n", 33, 0);
				if(m < 0) 
				{
					//perror("server: can't receive from client");  
					close(sock);      
				}
			}
			else
			{
				perror("File could not be deleted");
				close(sock);
			}
		}

		// CD COMMAND
		else if(strncmp(buffer, "CWD ", 4) == 0)
		{
			char *remote_path = strtok(buffer, " ");
			remote_path = strtok(NULL, " ");
			remote_path[strlen(remote_path)-2] = '\0';
			b = chdir(remote_path);
			if(b < 0)
			{
				perror("Directory could not be found");
				close(sock);
			}
			else
			{			
				m = send(sock, "250 Directory succesfully changed.\r\n", 36, 0);
				if(m < 0) 
				{
					//perror("server: can't receive from client");  
					close(sock);      
				}
			}
		} 

		// PWD COMMAND
		else if(strncmp(buffer, "PWD", 3) == 0)
		{
			char pwd[BUFSIZ];			
			if(getcwd(pwd, BUFSIZ) != NULL)
			{
				sprintf(aux_buffer, "257 \"%s\"\r\n", pwd);
				m = send(sock, aux_buffer, BUFSIZ,  0);
				if(m < 0) 
				{
					//perror("server: can't receive from client");  
					close(sock);      
				}
			}
			else
			{
				perror("Current directory could not be found");
				close(sock);
			}
		}

		// QUIT COMMAND 
		else if(strncmp("QUIT", buffer, 4) == 0)
		{
			//printf("Client requested to end connection.\nBye.\n");	
			close(sock);
		}
		
		// GET & PUT COMMAND
		else if(strncmp("PORT ", buffer, 5) == 0)                       
		{
			// Tokenizing procedure to get IP Address and Port
			char *token = strtok(buffer, " ");
			token = strtok(NULL, " ");
			token[strlen(token)-2] = '\0';
			int i, n = 0, j = 0;
			char port[BUFSIZ];
			char p1[BUFSIZ];
			char p2[BUFSIZ];
			for(i=0; token[i]!= '\0'; i++)
			{
				if(token[i] == ',')
			 	{
					token[i] = '.';
					n++;
			    	}
				if(i > 9)
				{
					port[j] = token[i];
					j++;
				}
	
			}
			port[strlen(token)-10] = '\0';
			strcpy(p1, strtok(port, "."));
   			strcpy(p2, strtok(NULL, "."));
			int new_port = (atoi(p1))*256 + atoi(p2);
			//printf("The port is: %d\n", new_port); 
			token[9] = '\0';
			//printf("IP addres is: %s\n", token);
									
			// Establish queue for connection requests 
			struct sockaddr_in address;
			memset(&address, 0, sizeof(address)); 
			address.sin_family = AF_INET; 
			address.sin_port = htons(new_port); 
			address.sin_addr.s_addr = inet_addr(token); 
			
			if((new_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			{
				perror("ERROR on socket");
			} 

			if(connect(new_sock, (struct sockaddr*)&address, sizeof(address)) < 0) 
			{  
				perror("bind failed:%s\n");  
				close(new_sock);  
		      	}   
			else
			{
				m = send(sock, "200 PORT command successful.\r\n", 30, 0);
				if(m < 0) 
				{
					//perror("server: can't receive from client");  
					close(sock);      
				}				
			}
			
		}
		
		// "RETR" (get) && "STOR" (put) implementations
		else if(strncmp("RETR ", buffer, 5) == 0 || strncmp("STOR ", buffer, 5) == 0)   
		{
		
			char ch;			
			char *file_path = strtok(buffer, " ");
			file_path = strtok(NULL, " ");
			file_path[strlen(file_path)-2] = '\0';	
			//printf("FILE PATH: %s\n", file_path);	
			if(strncmp("RETR", buffer, 4) == 0)
			{	
				send(sock, "150 Opening ASCII mode data connection.\r\n", 41, 0);
				
			}
			else if(strncmp("STOR", buffer, 4) == 0)
			{
				send(sock, "150 OK to send data.\r\n", 22, 0);
				
			}
			if((fd = open(file_path, O_RDONLY | O_RDWR | O_CREAT)) < 0)
			{
				perror("File could not be opened");
				close(sock);
			}
			while((read(fd, &ch, 1)) > 0)
			{								
				send(new_sock, &ch, 1, 0);
				
			}
			close(new_sock);
			send(sock, "226 Transfer complete.\r\n", 24, 0); 
			
			
		}

		
	}
}
