#include "header.h"

int main(int argc, char** argv)
{
	//Extract args	
	if(argc != 3)
	{
		printf("The number of arguments is incorrect!\nCorrect usage: ./dns_resolver server_ip domain_name\n");
		exit(0);
	} 	
	strcpy((char*) server_ip, (const char*) argv[1]);	
	server_ip[strlen((const char*) server_ip)] = '\0';
	unsigned char* domain_name = (unsigned char*) argv[2];
	int ans = 0;
	while(ans == 0)
		ans = section_handler(domain_name);
	return 0;
}




