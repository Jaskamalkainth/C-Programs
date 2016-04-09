
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct node
{
	int data;
	struct node* next;
};

typedef struct node * Nodeptr;

Nodeptr stack_head = NULL;

Nodeptr newnode()
{
	Nodeptr nn  = malloc(sizeof(struct node));
	return nn;
}

void push(int x)
{
	if ( stack_head == NULL )
	{
		Nodeptr nn = newnode();
		stack_head = nn;
		nn->data = x;
		nn->next = NULL;
	}
	Nodeptr nn = newnode();
	nn->next = stack_head;
	nn->data = x;
	stack_head = nn;
}

void pop()
{
	if( stack_head == NULL )
	{
	}
	else
	{
		stack_head = stack_head->next;  
	}
}
int top()
{
	if(stack_head == NULL )
	{
		return -1; // empty
	}
	else
	{
		return stack_head->data;
	}
}

int isdigit(char c)
{
	if(c <= '9' && c >= '0' )
		return 1;
	else
		return 0;
}

int compute_value(int a ,int b,char ch)
{
	if(ch == '*')
		return a*b;
	if(ch == '+')
		return a+b;
	if(ch == '-')
		return b-a;
	if(ch == '/')
		return b/a;
	if(ch == '$')
	{
		return (int)pow(b,a);
	}
	return -1;
}

void print_stack()
{
	Nodeptr curr =stack_head;
		while( curr != NULL)
	{
		printf("%d ",curr->data);  
		curr = curr->next;
	}
	printf("\n");
}
int main()
{

		  
	char str[100000];
	scanf("%s",str);

	int len = strlen(str);
	int i;
	for(i = 0; i < len ; i++)
	{
		if( isdigit(str[i]) == 1 )
		{
			push(str[i]-'0');
		}
		else
		{
			int o1 = top();
			pop();
			int o2 = top();
			pop();
			push(compute_value(o1,o2,str[i]));
		}
		print_stack();
	}
	int ans = top();
	printf("%d \n", ans);


	return 0;  
}
