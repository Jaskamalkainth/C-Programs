#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node
{
	char data;
	struct node* next;
};
int size ;
typedef struct node* nodeptr;
nodeptr stack_head = NULL;

nodeptr newnode(int x)
{
	nodeptr nn = malloc(sizeof(struct node));
	if(x != -1)
		nn->data =x;
	return nn;
}

void push(char x)
{
	nodeptr nn = newnode(x);
	if(stack_head == NULL)
	{
		stack_head = nn;
		nn->next = NULL;
	}
	else
	{
		nn->next = stack_head;
		stack_head = nn;
	}
	size += 1;
}
void pop()
{
	if(stack_head != NULL)
	{
		stack_head = stack_head->next;  
	size -= 1;
	}
}
char top()
{
	return stack_head->data;
}
int isdigit(char c)
{
	if(c <= '9' && c >= '0' )
		return 1;
	if( c <= 'Z' && c >= 'A' )
		return 1;
	if( c <= 'z' && c >= 'a' )
		return 1;
	return 0;
}
int priority(char c)
{
	if( c == '(' )
		return 0;
	if( c == '+' || c == '-' )
		return 1;
	if( c == '*' || c == '/' || c == '$' )
		return 2;
		
	return 3;
	
}
int isempty()
{
	if( size == 0 )
		return 1;
	return 0;
}
void print_stack()
{
	nodeptr curr = stack_head;
	while(  curr != NULL )
	{
		printf("%c ", curr->data);
		curr = curr->next;
	}
	printf("\n");
}
int main()
{
	char s[10000];
	char ans[100000];
	scanf("%s",s);
	int len = strlen(s);
	int i , k = 0;
	for(i = 0;i < len; i++)
	{
		if( isdigit(s[i])  == 1)
		{
			ans[k++] = s[i];
			printf("%c",s[i]);
			continue;
		}
		if(s[i] == '(')
		{
			push('(');  
			continue;
		}
		if(s[i] == ')')
		{
			while(isempty() == 0 && top() != '(')
			{
				char ele = top();
				pop();
				if(ele != '(')
				{
					printf("%c",ele);
					ans[k++] = ele;
				}
			}
			pop();
			continue;
		}
		while(isempty() == 0 &&  priority(top()) >= priority(s[i]))
		{
			char ele = top();
			pop();
			if(ele != '(')
			{
				printf("%c",ele);
				ans[k++] = ele;
			}
		}
		push(s[i]);
	}
	while( size!= 0 )
	{
		char ele = top();
		pop();
		printf("%c",ele);
		ans[k++] = ele;
	}

	printf("\n%s",ans);
	

	

	return 0;  
}
