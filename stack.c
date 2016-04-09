#include<stdio.h>
#include<stdlib.h>


struct node
{
	int data;
	int size ;
	struct node* next;
};
typedef struct node* Nodeptr;

Nodeptr getnode()
{
	Nodeptr nn = malloc(sizeof(struct node));  
	return nn; 
}

void push(Nodeptr *head ,int x)
{
	if(*head == NULL )
	{
		//empty stack

		Nodeptr nn = getnode();
		*head = nn;
		nn->data = x;
		nn->next = NULL;
	}
	else
	{
		Nodeptr nn = getnode();
		nn->next = *head;
		nn->data = x;
		*head = nn;
	}
	(*head)->size += 1;

}

void pop(Nodeptr *head )
{
	if( *head == NULL )
	{
	}
	else
	{
		*head = (*head)->next;
		(*head)->size -= 1;
	}
}
int top(Nodeptr *head)
{
	int x = (*head)->data;
	return x;
}
void printstack(Nodeptr *head)
{

	if(*head == NULL)
	{
	}
	else
	{
		Nodeptr curr = *head;
		while( curr != NULL)
		{
			printf("%d ", curr->data);
			curr = curr->next;
		}
	}
	  
	printf("\n");
}

int size(Nodeptr *head)
{
	return (*head)->size;  
}

int main()
{

	Nodeptr stack1 = NULL;
	stack1->size = 0;
	push(&stack1 , 5);
	push(&stack1 , 2);
	printf("Size = %d \n",size(&stack1));
	push(&stack1 , 3);
	printstack(&stack1);
	printf("Size = %d \n",size(&stack1));
	pop(&stack1);
	pop(&stack1);
	printf("Size = %d \n",size(&stack1));
	push(&stack1 , 2);
	push(&stack1 , 3);
	printf("Size = %d \n",size(&stack1));

	printstack(&stack1);
	printf("%d \n",top(&stack1));
	return 0;

}
