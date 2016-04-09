#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char stack2[100] ;
int front2 = -1;
int size2 ;
void push(char ch)
{
	stack2[++front2] = ch;
	size2++;
}
void pop()
{
	front2--;  
	size2--;
}
char top()
{
	return stack2[front2];  
}
int isdigit(char ch)
{
	if( ch == '0' || ch == '1' )return 1;
	return 0;
}
int main()
{
	char out[100];
	scanf("%s",out);
	int len = strlen(out);
	int i ;
	
	for(i = 0; i < len; i++)
	{
		if( isdigit(out[i]) )
			push(out[i]);
		else
		{
			char ch1 = top();
			pop();
			char ch2 = top();
			pop();
			if(out[i] == '+')
			{
				if( ch1 == '1' && ch2 == '1' )
					push('1');			  
				if( ch1 == '1' && ch2 == '0' )
					push('1');			  
				if( ch1 == '0' && ch2 == '1' )
					push('1');			  
				if( ch1 == '0' && ch2 == '0' )
					push('0');			  
			}
			if(out[i] == '*')
			{
				if( ch1 == '1' && ch2 == '1' )
					push('1');			  
				if( ch1 == '1' && ch2 == '0' )
					push('0');			  
				if( ch1 == '0' && ch2 == '1' )
					push('0');			  
				if( ch1 == '0' && ch2 == '0' )
					push('0');			  
			}
		}
	}
	printf("%c\n", top());
	return 0;
}
