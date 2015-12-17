#include "header.h"

/**Byte processing:
DNS assumes that messages will be transmitted as datagrams or in a
byte stream carried by a virtual circuit**/

char* byte_handler(unsigned char* bytes, unsigned char* buf, int* num)
{
	unsigned char* name = malloc(sizeof(char)*256);
	int x = 0, counter = 0, offset = 0, i , j;
	(*num) = 1; // Change the value of num to distinguish sections, but keeping the same pointer address (marks the beginning and end of the readings) 
   	name[0] = '\0';
	
	// Read names in DNS format from byte array 
    	while((*bytes) != 0)
    	{
        	if((*bytes) >= 192)
        	{
			// All DNS queries are sent from a high-numbered source port (49152 or above)
			// 49152 = 11000000 00000000       		
			offset = ((*bytes)*256 + *(bytes+1)) - 49152; 
	       		bytes = buf + offset - 1;
        	    	counter = 1; // We have already jumped to another location
        	}
        	else
        	{
        	    	name[x++] = (*bytes); // Storing the byte into the name array
        	}
	        bytes = bytes + 1; // Reading next byte
	        if(counter == 0) 
		{
            		(*num) = (*num) + 1; 
        	}
    	}
	name[x]='\0'; 
	if(counter == 1)
	{
		(*num) = (*num) + 1; 
	} 

    	// Convert from DNS format to a mnemoric one e.g. cs.fiu.edu
	int k = (int) strlen((const char*)name);
    	for(i = 0; i < k; i++)
    	{
		// Take the number of letters ahead        	
		x = name[i];
        	for(j = 0; j < (int) x ; j++)
        	{
        	    	// Skip the number, store the letters
		 	name[i] = name[i+1];
        	    	i++;
        	}
		name[i] = '.'; // Add a dot
    	}
	name[i-1] = '\0'; // Remove last dot
    	return (char*) name;
}

