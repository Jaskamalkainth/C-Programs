#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/****** stack1 for converting infix to postfix *******/
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

/******* stack2 for evaluating postfix expression ********/
char stack2[100] ;
int front2 = -1;
int size2 ;
void push2(char ch)
{
	stack2[++front2] = ch;
	size2++;
}
void pop2()
{
	front2--;  
	size2--;
}
char top2()
{
	return stack2[front2];  
}

char evaluate_infix( char inp[100] )
{

	/*** code for converting infix to postfix ********/
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
	int len2 = strlen(out);
	/*************** code for evaluating postfix  ********/
	for(i = 0; i < len2; i++)
	{
		if( isdigit(out[i]) )
			push2(out[i]);
		else
		{
			char ch1 = top2();
			pop2();
			char ch2 = top2();
			pop2();
			if(out[i] == '+')
			{
				if( ch1 == '1' && ch2 == '1' )
					push2('1');			  
				if( ch1 == '1' && ch2 == '0' )
					push2('1');			  
				if( ch1 == '0' && ch2 == '1' )
					push2('1');			  
				if( ch1 == '0' && ch2 == '0' )
					push2('0');			  
			}
			if(out[i] == '*')
			{
				if( ch1 == '1' && ch2 == '1' )
					push2('1');			  
				if( ch1 == '1' && ch2 == '0' )
					push2('0');			  
				if( ch1 == '0' && ch2 == '1' )
					push2('0');			  
				if( ch1 == '0' && ch2 == '0' )
					push2('0');			  
			}
		}
	}
	char eval_ans = top2();
	return eval_ans;
}

int main()
{
	char inp[100];
	scanf("%s",inp);
	char eval_ans = evaluate_infix(inp);
	printf("%c\n",eval_ans);
	return 0;
}

