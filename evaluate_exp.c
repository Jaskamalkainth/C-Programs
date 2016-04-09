#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main()
{

	char inp[100];
	scanf("%s",inp);

	int len =  strlen(inp);


	int i;
	int val = 1;
	//inp is in binary 
	for(i = 0; i < len; )
	{
		if(inp[i] == '(' )
		{
			int fval = 0;	
			int k = i+1;
			while(inp[k] != ')' && k < len)
			{
				if(inp[k] == '-')
				{
					fval += !inp[k+1];
					k += 2;
					i = k;
					continue;
				}
				if(inp[k] == '+' )
				{
					fval += inp[k+1];  
					i = k+1;
					continue;
				}
			}
			i = k;
		}
	}
	
	
	
	return 0;  
}
