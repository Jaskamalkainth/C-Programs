#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node * next;
};


typedef struct node *Nodeptr;

Nodeptr getnode()
{
	Nodeptr nn ;
	nn =malloc(sizeof(struct node));
	return nn;
}

void addFront(Nodeptr *head , int  x)
{
	Nodeptr nn = getnode();
	nn->data = x;
	nn->next = *head;
	*head = nn;
}


void removeFront(Nodeptr *head)
{
	if(*head == NULL )
		printf("List is empty");
	else
	{
		*head = (*head)->next;
	}
}
void insertAfter(Nodeptr p , int x)
{
	Nodeptr nn = getnode();
	if ( p == NULL )
	{
		printf("empty list, call add front");  
	}
	else
	{
	 nn->data = x;
	 nn->next = p->next;
	 p->next  = nn;
	}
}

void deleteAfter(Nodeptr p )
{
	if ( p == NULL || ( p->next == NULL ) )
	{
		printf("deletion not possilbe");  
	}
	else
	{
		p->next = (p->next)->next;  
		free(p->next);
	}
}


void printlist(Nodeptr list)
{
	if ( list == NULL )
	{
		printf("Empty list");  
	}
	else
	{
		Nodeptr curr = list;
		while(curr != NULL)
		{
			printf("%d ",curr->data);
			curr = curr->next;
		}
		printf("\n");
	}
}
int main()
{

	Nodeptr *list1 ;
	addFront(list1,5);
	addFront(list1,4);
	addFront(list1,2);
	addFront(list1,-1);

	printlist(*list1);

	removeFront(list1);
	printlist(*list1);
	insertAfter(*list1,5);
	printlist(*list1);

	return 0;  
}
