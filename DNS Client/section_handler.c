#include "header.h"

void section_reader(struct HEADER *dns_header, struct sockaddr_in host_struct);
void section_printer(struct HEADER *dns_header, struct sockaddr_in host_struct);

int section_handler(unsigned char* domain_name)
{
	int loop, s = 0, t = 0;
	num = 0;
	unsigned char *qname, *domain;
	
	struct sockaddr_in host_struct; //To extract sections from host
	struct sockaddr_in server_struct; // To assign info to server (family, port, addr)
	struct HEADER *dns_header = NULL; // Pointer to the header struct
	struct QUESTION *query = NULL; // Pointer to the question struct
	// struct RES_RECORD *rec = NULL; // Pointer to the res_record struct
	// struct R_DATA *data = NULL; // Pointer to the r_data struct

	// Cleaning all fields	
	memset(buffer, 0, BUFSIZ);
	memset(&host_struct, 0, sizeof(host_struct));
	memset(&server_struct, 0, sizeof(server_struct));
	memset(&dns_header, 0, sizeof(struct HEADER));
	memset(&query , 0, sizeof(struct QUESTION));
	//memset(&rec , 0, sizeof(struct RES_RECORD));
	//memset(&data , 0, sizeof(struct R_DATA));  

	// We need to change the domain_name to DNS format
	domain = (unsigned char*)&buffer[sizeof(struct HEADER)];
	change_domain_name_format(domain, domain_name);
		
	// Create a UDP socket to send query to server
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) 
	{ 
		printf("cannot create socket\n"); 
		exit(0); 
	}
	server_struct.sin_family = AF_INET;
	server_struct.sin_port = htons(53);
	server_struct.sin_addr.s_addr = inet_addr((const char*) server_ip);
		
	// Set values of HEADER structure 
	dns_header = (struct HEADER *)&buffer;
	dns_header->id = (unsigned short) htons(getpid()); // Assign any id, e.g. process id
	dns_header->rd = 0; // Recursion not desired
	dns_header->tc = 0; // This message is not truncated
	dns_header->aa = 0; // Not authoritative
	dns_header->opcode = 0; // This is a standard query
	dns_header->qr = 0; // This is a query
	dns_header->rcode = 0;
	dns_header->cd = 0;
	dns_header->ad = 0;
	dns_header->z = 0; // Reserved for future use
	dns_header->ra = 0;
	dns_header->q_count = htons(1); // We only have 1 query
	dns_header->ans_count = 0; 
	dns_header->auth_count = 0; 
	dns_header->add_count = 0; 

	// Point to the query portion
	qname = (unsigned char*)&buffer[sizeof(struct HEADER)];
	
	// Set values of QUESTION structure 
	query = (struct QUESTION*)&buffer[sizeof(struct HEADER) + (strlen((const char*)qname) + 1)];
	query->qtype = htons(1); // Type A
	query->qclass = htons(1); // It's internet
	
	// Sending packet...
	if((sendto(s, (char*)buffer, sizeof(struct HEADER) + (strlen((const char*) domain) + 1) + sizeof(struct QUESTION), 0, (struct sockaddr*)&server_struct, sizeof(server_struct))) < 0)
	{
		printf("Process failed. Package could not be sent."); 
		exit(0);
	}
	
	// Receiving the answer...
	t = sizeof(server_struct);
	if((recvfrom(s, (char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&server_struct, (socklen_t*)&t)) < 0)
	{
		perror("Process failed. Package could not be received.");
		exit(0);
	}
		
	// Move pointer ahead of the dns header to start readings
	pointer = &buffer[sizeof(struct HEADER) + (strlen((const char*)domain)+1) + sizeof(struct QUESTION)];
		
	// Print to the console:
	printf("\n-------------------------------------------------------------");
	printf("\nDNS server to query: %s\nReply received. Content overview:\n", server_ip);
	printf("\t%d Answers.\n", ntohs(dns_header->ans_count));
	printf("\t%d Intermediate Name Servers.\n", ntohs(dns_header->auth_count));
	printf("\t%d Additional Information Records.\n", ntohs(dns_header->add_count));
	loop = ntohs(dns_header-> ans_count);

	// Read data	
	section_reader(dns_header, host_struct);
	// Print data
	section_printer(dns_header, host_struct);
	
	return loop;

}

void section_reader(struct HEADER *dns_header, struct sockaddr_in host_struct)
{
	int i = 0, j = 0;	
	// Reading answers
	for(; i < ntohs(dns_header -> ans_count); i++)
	{
		answers[i].server = (unsigned char*) byte_handler(pointer, buffer, &num);
		pointer += num;
		answers[i].resource = (struct R_DATA*) pointer;
		pointer += sizeof(struct R_DATA);
		if(ntohs(answers[i].resource -> type) == 1)				
		{
			answers[i].rdata = (unsigned char*) malloc(ntohs(answers[i].resource -> data_len));
			for(j = 0; j < ntohs(answers[i].resource -> data_len); j++)
			{
				answers[i].rdata[j] = pointer[j];
			}
			answers[i].rdata[ntohs(answers[i].resource -> data_len)] = '\0';			
			pointer += ntohs(answers[i].resource -> data_len);
		}
		else
		{
			answers[i].rdata = (unsigned char*) byte_handler(pointer, buffer, &num);
			pointer += num;
		}
	}

	// Reading authorities 
    	for(i = 0; i < ntohs(dns_header -> auth_count); i++)
    	{
        	authoritive[i].server = (unsigned char*) byte_handler(pointer, buffer, &num);
        	pointer += num;
	        authoritive[i].resource = (struct R_DATA*)(pointer);
	        pointer += sizeof(struct R_DATA);
	        authoritive[i].rdata = (unsigned char*) byte_handler(pointer, buffer, &num);
	        pointer += num;
    	}	

    	// Reading additional
    	for(i = 0; i < ntohs(dns_header -> add_count); i++)
    	{
        	additional[i].server = (unsigned char*) byte_handler(pointer, buffer, &num);
        	pointer += num;
	        additional[i].resource = (struct R_DATA*)(pointer);
	        pointer += sizeof(struct R_DATA);
	        if(ntohs(additional[i].resource -> type) == 1)
	        {
	        	additional[i].rdata = (unsigned char*) malloc(ntohs(additional[i].resource -> data_len));
            		for(j = 0; j<ntohs(additional[i].resource -> data_len); j++)
			{
            			additional[i].rdata[j] = pointer[j];
			}	           	
			additional[i].rdata[ntohs(additional[i].resource -> data_len)] = '\0';
            		pointer += ntohs(additional[i].resource -> data_len);
        	}
        	else
        	{
            		additional[i].rdata = (unsigned char*) byte_handler(pointer,buffer, &num);
            		pointer += num;
        	}
    	}
}

void section_printer(struct HEADER *dns_header, struct sockaddr_in host_struct)
{
	int check = 0, i = 0;	
	// Printing answers
	printf("Answers Section:\n");
	for(i = 0 ; i < ntohs(dns_header -> ans_count); i++)
	{
		printf("\tName : %s", answers[i].server);
		if( ntohs(answers[i].resource -> type) == 1) 
		{
		    long* p = (long*) answers[i].rdata;
		    host_struct.sin_addr.s_addr = *p; 
		    printf("\tIP : %s", inet_ntoa(host_struct.sin_addr));
		}
		printf("\n");
	}

    	// Printing authorities
  	printf("Authoritive Section:\n");
    	for(i = 0; i < ntohs(dns_header -> auth_count) ; i++)
    	{
               	printf("\tName : %s", authoritive[i].server);
        	if(ntohs(authoritive[i].resource -> type)==2)
        	{
            		printf("\tName Server : %s", authoritive[i].rdata);
        	}
		printf("\n");
    	}

	// Printing additional resource records
	printf("Additional Information Section:\n");
	for(i = 0; i < ntohs(dns_header -> add_count) ; i++)
	{
		
		check =  (int) strlen((const char*) additional[i].server);
		if(check != 0)
		{		
			printf("\tName : %s ", additional[i].server);
			if(ntohs(additional[i].resource -> type) == 1)
			{
			    long *p = (long*) additional[i].rdata;
			    host_struct.sin_addr.s_addr = *p;
			    printf("\tIP : %s", inet_ntoa(host_struct.sin_addr));
			    if(i == 0)
			    {
				sscanf(inet_ntoa(host_struct.sin_addr), "%s", server_ip);
			    }
			}
		}
		printf("\n");
	}
	printf("\n");
}


