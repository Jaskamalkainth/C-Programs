#include<stdlib.h>
#include<stdio.h>
#include<string.h>






char stack1[100] = {0};
int front1 = -1; 
int size1 = 0;
void push(char x)
{
	stack1[++front1] = x;
	size1++;
}
void pop()
{
	front1 -= 1;  
	size1--;
}
char top()
{
	return stack1[front1];  
}
int isdigit(char x)
{
	if( x == '0' || x == '1') return 1;
	return 0;
}
int priority ( char ch)
{
	if(ch == '(') return 0;
	if(ch == '+') return 1;
	if(ch == '*') return 2;
	return 3;
}
int main()
{
	char inp[100];
	scanf("%s",inp);
	int len = strlen(inp);
	int i , j , k=0;
	char out[100];
	for(i = 0; i < len; i++)
	{
		if(isdigit(inp[i]))
		{
			out[k++]=inp[i];
			continue;
		}
		if(inp[i] == '(')
		{
			push(inp[i]);
			continue;
		}
		if(inp[i] == ')')
		{
			while( size1 != 0 && top() != '(' )
			{
				char ele = top(); pop();
				out[k++] = ele;
			}
			pop();
			continue;
		}
		while(size1 !=0 && priority(top()) >= priority(inp[i]))
		{
				char ele = top(); pop();
				out[k++] = ele;
		}
		push(inp[i]);
	}
	while(size1 != 0 )
	{
		char ele = top(); pop();
		out[k++] = ele;

	}
	printf("%s\n",out);



	return 0;  
}
