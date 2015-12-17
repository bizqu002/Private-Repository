#include<stdio.h>    
#include<string.h>    
#include<stdlib.h>    
#include<sys/socket.h>    
#include<arpa/inet.h>    
#include<netinet/in.h>
#include<unistd.h>
#include <netdb.h>

#ifndef HEADER_H
#define HEADER_H

struct HEADER
{
	unsigned short id; // identification number
 
	//3rd byte
	unsigned char rd :1; // recursion desired
	unsigned char tc :1; // truncated message
	unsigned char aa :1; // Authoritative Answer - this bit is valid in responses, and specifies that the responding name server is an authority for the domain name in question section.
	unsigned char opcode :4; // A four bit field that specifies kind of query in this message. 
	unsigned char qr :1; //A one bit field that specifies whether this message is a query (0), or a response (1).
 
	//4th byte
	unsigned char rcode :4; // Response code - this 4 bit field is set as part of responses.  
	unsigned char cd :1; // checking disabled
  	unsigned char ad :1; // authenticated data
  	unsigned char z :1; // its z! reserved
  	unsigned char ra :1; // recursion available
 
  	unsigned short q_count; // number of question entries
  	unsigned short ans_count; // number of answer entries
  	unsigned short auth_count; // number of authority entries
  	unsigned short add_count; // number of resource entries
};
 

struct QUESTION
{
  	unsigned short qtype; 
  	unsigned short qclass;
};
 
//make sure the alighment matches the DNS message format specification
//i.e., there should not be any padding.
//(by default, C struct aligment is based on the "wiserver_struct" field
#pragma pack(push, 1)
struct R_DATA
{
  	unsigned short type;
  	unsigned short class;
  	unsigned int ttl;
  	unsigned short data_len;
};
#pragma pack(pop)
 
struct RES_RECORD
{
  	unsigned char *server;
  	struct R_DATA *resource;
  	unsigned char *rdata;
};
 
typedef struct
{
  	unsigned char *server;
  	struct QUESTION *ques;
} QUERY;

// Read & print sections
	struct RES_RECORD answers[30], authoritive[30], additional[30]; //We need to create buffers to store the results of our query
#endif

void change_domain_name_format(unsigned char* domain, unsigned char* domain_name);
char* byte_handler(unsigned char* bytes, unsigned char* buf, int* num);
int section_handler(unsigned char* domain_name);
void section_reader(struct HEADER *dns_header, struct sockaddr_in host_struct);
void section_printer(struct HEADER *dns_header, struct sockaddr_in host_struct);
unsigned char server_ip[20];
unsigned char *pointer;
unsigned char buffer[65536];	
int num;
