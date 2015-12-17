#include "header.h"

void change_domain_name_format(unsigned char* domain, unsigned char* domain_name)
{
	int location = 0 , i;
	strcat((char*)domain_name,".");
	for(i = 0 ; i < strlen((char*) domain_name); i++)
    	{
		if(domain_name[i]=='.')
		{
		    *domain++ = i - location;
		    for(;location<i;location++)
		    {
		        *domain++ = domain_name[location];
		    }
		    location++; 
		}
    	}
    	*domain++ ='\0';
} 

