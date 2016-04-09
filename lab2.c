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
/*
 * stack of strings for compiler code 
 */

struct node1
{
	char* data;
	struct node1*  next;
};
typedef struct node1* nodeptr1;

nodeptr1 stack_head1;
nodeptr1 newnode1()
{
	nodeptr1 nn = malloc(sizeof(struct node1));  
	return nn;
}
void push1(char str[10])
{
	nodeptr1 nn = newnode1();
	nn->data = malloc(10);
	strcpy(nn->data,str);
	if(stack_head1 == NULL)
	{
		nn->next = NULL;
		stack_head1 = nn;
	}
	else
	{
		nn->next = stack_head1;
		stack_head1 = nn;
	}
}
void pop1()
{
	if(stack_head1 != NULL)
		stack_head1 = stack_head1->next;
}
char* top1()
{
	return stack_head1->data; 
}
int isoperand(char ch)
{
	if( ch <= 'Z' && ch >= 'A' )
		return 1;
	if( ch <= 'z' && ch >= 'a' )
		return 1;
	return 0;
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
			continue;
		}
		if(s[i] == '(')
		{
			push('(');  
			continue;
		}
		if(s[i] == ')')
		{
			while(size!=0 && top() != '(')
			{
				char ele = top();
				pop();
				if(ele != '(')
				{
					ans[k++] = ele;
				}
			}
			pop();
			continue;
		}
		while(size!=0 &&  priority(top()) >= priority(s[i]))
		{
			char ele = top();
			pop();
			if(ele != '(')
			{
				ans[k++] = ele;
			}
		}
		push(s[i]);
	}
	while( size!= 0 )
	{
		char ele = top();
		pop();
		ans[k++] = ele;
	}
	/*
	 * we got our postfix expression in ans 
	 *
	 */
	printf("%s\n",ans);
	/*
	 *
	 * now compiler code starts
	 *
	 */
	int ii ;
	int kk = 0;
	for(ii = 0; ii < len; ii++)
	{
		if(isoperand(ans[ii]))
		{
			char temp[2];
			temp[0] = ans[ii];
			temp[1] = '\0';
			push1(temp);
		}
		else
		{
			char *op1 = top1();  
			pop1();
			char *op2 = top1();  
			pop1();


			char temp[10];
			sprintf(temp,"TEMP%d",++kk);
			if( ans[ii] == '+' )
			{
				printf("LD %s\n",op2);
				printf("AD %s\n",op1);
				printf("ST %s\n",temp);
			}
			if( ans[ii] == '-' )
			{
				printf("LD %s\n",op2);
				printf("SB %s\n",op1);
				printf("ST %s\n",temp);
			}
			if( ans[ii] == '*' )
			{
				printf("LD %s\n",op2);
				printf("ML %s\n",op1);
				printf("ST %s\n",temp);
			}
			if( ans[ii] == '/' )
			{
				printf("LD %s\n",op2);
				printf("DV %s\n",op1);
				printf("ST %s\n",temp);
			}
			push1(temp);
		}
	}
	return 0;  
}


