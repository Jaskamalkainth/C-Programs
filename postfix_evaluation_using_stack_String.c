#include<stdlib.h>
#include<stdio.h>
#include<string.h>


struct node
{
	char* data;
	struct node* next;
};

typedef struct node* nodeptr;
nodeptr stackhead = NULL;

nodeptr newnode()
{
	nodeptr nn = malloc(sizeof(struct node));
	nn->data = malloc(6);
	return nn;
}

void push(char str[10])
{
	nodeptr nn = newnode();
	strcpy(nn->data,str);

	if(stackhead == NULL )
	{
		stackhead = nn;
		nn->next = NULL;
	}
	else
	{
		nn->next = stackhead;
		stackhead = nn;
	}
}

void pop()
{
	if(stackhead != NULL)
		stackhead = stackhead->next;  
}

char* top()
{
	return stackhead->data;
}

int isoperand(char ch)
{
	if( ch <= 'Z' && ch >= 'A')
		return 1;
	if( ch <= 'z' && ch >= 'a')
		return 1;
	return 0;
}
void printstack()
{
	nodeptr curr = stackhead;
	if( curr == NULL ) printf("empty\n");
	while(curr != NULL)
	{
		printf("%s ",curr->data);
		curr = curr->next;
	}
	printf("\n");
}
int main()
{
	/*
INPUT:
ABC*+DE-/
OUTPUT:
LD B
ML C
ST TEMP1
LD A
AD TEMP1
ST TEMP2
LD D
SB E
ST TEMP3
LD TEMP2
DV TEMP3
ST TEMP4
*/


	char inp[100];
	scanf("%s",inp);
	int len = strlen(inp);

	int i , k = 0;

	for(i = 0; i < len; i++)
	{

		if( isoperand(inp[i]) == 1 )
		{
			char temp[2];
			temp[0]= inp[i];
			temp[1] = '\0';
			push(temp);
			//		printf("######temp %s \n", temp);
			//		printf("******inp[i] %c \n", inp[i]);
		}
		else
		{
			char *op1 = top();
			pop();
			//		printf("op1= ~~~~~%s\n",op1);


			char* op2 = top();  
			pop();
			//		printf("op2= ~~~~~%s\n",op2);


			char temp[10];
			sprintf(temp,"TEMP%d",++k);


			if ( inp[i] == '+' )
			{
				printf("LD %s\n",op2);  
				printf("AD %s\n",op1);  
				printf("ST TEMP%d\n",k);  
				push(temp);
			}
			if ( inp[i] == '-' )
			{
				printf("LD %s\n",op2);  
				printf("SB %s\n",op1);  
				printf("ST TEMP%d\n",k);  
				push(temp);
			}
			if ( inp[i] == '*' )
			{
				printf("LD %s\n",op2);  
				printf("ML %s\n",op1);  
				printf("ST TEMP%d\n",k);  
				push(temp);
			}
			if ( inp[i] == '/' )
			{
				printf("LD %s\n",op2);  
				printf("DV %s\n",op1);  
				printf("ST TEMP%d\n",k);  
				push(temp);
			}
		}
	}

	return 0;

}
