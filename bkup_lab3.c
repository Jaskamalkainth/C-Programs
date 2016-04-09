#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
 * 1. Construct the Game tree
 * 2. Evaluate the Game treE
 * 3. Preorder traversal of this Game tree.
 */
/******* Binary Tree code  BEGIN **********/
struct node
{
	int data;
	int label;
	struct node* parent;
	struct node* leftChild;
	struct node* rightChild;
	int flag_left_child;
	int flag_right_child;
	int flag_root;
};
typedef struct node* nodeptr;

struct btree
{
	int size;
	nodeptr root;
};

typedef struct btree* btreeptr;

int lastlabel = 0;
nodeptr createNode(int d)
{
	nodeptr nn = malloc(sizeof(struct node));
	nn->data = d;
	nn->leftChild = NULL;
	nn->rightChild = NULL;
	if(lastlabel == 0 )
	{
		nn->parent = NULL;  
	}
	lastlabel++;
	nn->label = lastlabel;
	return nn;
}
btreeptr createTree()
{
	btreeptr tt = malloc(sizeof(struct btree));
	tt->size = 0;
	tt->root = createNode(-1);
	return tt;
}
/******* Binary Tree code  END **********/
/******** Queue Code BEGIN ********/
struct Queue
{
	int front , rear;
	int size;
	nodeptr *array;
};

typedef struct Queue* queueptr;

queueptr qq ; // main queue
queueptr temp_q; // temporary queue
btreeptr tt;

queueptr createQueue( int size )
{
	queueptr qq = malloc(sizeof(struct Queue));
	qq->front = -1;
	qq->rear  = -1;
	qq->array = malloc(size * sizeof(nodeptr));
	int i;
	for(i = 0; i < size; i++)
		qq->array[i] = NULL;
	return qq;
}
int isEmpty (queueptr *qq) 
{
	if( (*qq)->front == -1 )
		return 1;
	return 0;
}

int sizeOne (queueptr *qq)
{
	return (*qq)->front == (*qq)->rear ;
}

void Enqueue( nodeptr rr ,queueptr *q)
{
	queueptr tq = *q;
	(*q)->array[++(*q)->rear] =  rr;
	if( isEmpty(&tq) )
		(*q)->front++;
}

nodeptr Dequeue(queueptr *q)
{
	queueptr tq = *q;
	if( isEmpty (&tq) )
	{
		return NULL;
	}
	nodeptr temp = (*q)->array[(*q)->front];

	if(sizeOne(q))
		(*q)->front = (*q)->rear = -1;
	else
		(*q)->front++;
	return temp;
}
nodeptr getFront(queueptr *qq)
{
	return (*qq)->array[(*qq)->front];  
}

void printQueue(queueptr *qq)
{
	int i; 
	if(isEmpty(qq))
		printf("%s\n","Empty queue");  
	else
		for(i = (*qq)->front; i <= (*qq)->rear; i++)
			printf("%d ",(*qq)->array[i]->label);
}
/********** Queue Code END **************/
/***** Construct the game Tree ********/
// if n variables then size = pow(2,n+1) - 1 nodes
void constructTree (int size ) // passing by ref
{ 
	tt->size = 1;
	Enqueue( tt->root,&qq );
	tt->root->flag_root = 1;
	tt->root->flag_left_child = 0;
	tt->root->flag_right_child = 0;
	while(!isEmpty(&qq))
	{
		if( size == tt->size )
			break;  
		nodeptr temp = Dequeue(&qq);  
		nodeptr child1 = createNode(-1);
		nodeptr child2 = createNode(-1);
		temp->leftChild = child1;
		child1->flag_left_child = 1;
		child1->flag_right_child = 0;
		child1->flag_root = 0;
		temp->rightChild = child2;
		child2->flag_left_child = 0;
		child2->flag_right_child = 1;
		child2->flag_root = 0;
		child1->parent = temp;
		child2->parent = temp;
		Enqueue(child1,&qq);
		Enqueue(child2,&qq);
		tt->size += 2;
	}
}
/******  n = number of char's A ,B ,C...*******/
int n ; 
char input_string[100];
/***************** INFIX EVAL  CODE BEGIN *************/
/****** stack1 for converting infix to postfix *******/
char stack1[100] = {0} ;
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
int size2 = 0;
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
	printf("len of inp inside evaluate_infix = %d\n",len);
	printf("string (inp) inside evaluate_infix = %s\n",inp);
	int num_of_bracks = 0;
	int num_of_zero_one = 0;
	int num_pf_mult_add = 0;
	int i , j , k=0;
	for(i = 0; i < len; i++)
	{
		if(inp[i] == '(' || inp[i] == ')')
			num_of_bracks++;
		if(inp[i] == '0' || inp[i] == '1')
			num_of_zero_one++;
		if(inp[i] == '+' || inp[i] == '*')
			num_pf_mult_add++;
	}
	inp[num_of_bracks+num_of_zero_one+num_pf_mult_add] = '\0';
	int len1 = strlen(inp);
	printf("len of inp inside evaluate_infix = %d\n",len1);
	printf("string (inp) inside evaluate_infix = %s\n",inp);
	char out[100];
	for(i = 0; i < len1; i++)
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
	out[num_of_zero_one+num_pf_mult_add] = '\0';
	int len2 = strlen(out);
	printf("len of out inside evaluate_infix = %d\n",len2);
	printf("string (out) inside evaluate_infix = %s\n",out);
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
/**************** INFIX EVAL CODE END *****************/
void update_leafnode(nodeptr *ln , int val)
{
	// assign values to all the char's and 
	// then conver the given string to desired infix exp 
	// then evaluater infix exp 
	// and we got our leaf node value
	// bin[0] = A bin[1] = B
	char bin[n+2] ;
	int i ;
	for(i = 0; i < n; i++)
	{
		if( val == 0 )
		{
			bin[i] = '0';
		}
		else
		{
			int rem = val % 2;
			if( rem == 1 )
				bin[i] = '1';
			else
				bin[i] = '0';
			val /= 2;
		}
	}
	for(i = 0; i < n; i++)
	{
		printf("%c ",bin[i]);
	}
	printf("\n");
	//  modify the input_string 
	//  bin[0] = A bin[1] = B  and so on.
	int j;
	char temp_string[100];
	strcpy(temp_string , input_string);
	int len = strlen(input_string);
	char ch;
	for(ch = 'A' ,i = n-1; ch <= 'Z' && i >=0 ; ch++ , i--)
		for(j = 0; j < len; j++)
			if(input_string[j] == ch )
				temp_string[j] = bin[i];
	printf("temp_string = %s\n",temp_string);
	// remove - signs
	char inp[100];
	int k = 0;
	for(i = 0; i < len; i++)
	{
		if(temp_string[i] == '-')
		{
			if( temp_string[i+1] == '0' )
				inp[k] = '1';
			if( temp_string[i+1] == '1' )
				inp[k] = '0';
			k++;
			i++;
		}
		else
			inp[k++] = temp_string[i];  
	}
	int len_inp = strlen(inp);
	inp[len_inp] = '\0';
		printf("inp = %s\n",inp);
	char output = evaluate_infix(inp);
		printf("output = %c\n",output);
	if( output == '1')
	{
		(*ln)->data = 1;
	}
	else
	{
		(*ln)->data = 0;
	}
	printf("%s \n","Main Queue");
	printQueue(&qq);
}
void evaluate_leaf_nodes()
{
	int i;
	int val = 0 ;
	for(i = qq->front; i <= qq->rear; i++)
	{
		printf("label %d\n",qq->array[i]->label);
		update_leafnode(&(qq->array[i]) ,val++);  
	}
}
int get_level(nodeptr root , int key , int index)
{
	if(root == NULL)
		return 0;
	else if(root->label==key)
		return index;
	else
		return get_level(root->leftChild,key , index + 1) + get_level(root->rightChild,key, index + 1);
}
void update_data(nodeptr *nn , int level)
{
	if(level % 2 == 1)
	{
		//add
		if((*nn)->leftChild->data == 1 && (*nn)->rightChild->data == 1)
			(*nn)->data = 1;
		if((*nn)->leftChild->data == 0 && (*nn)->rightChild->data == 1)
			(*nn)->data = 1;
		if((*nn)->leftChild->data == 1 && (*nn)->rightChild->data == 0)
			(*nn)->data = 1;
		if((*nn)->leftChild->data == 0 && (*nn)->rightChild->data == 0)
			(*nn)->data = 0;
	}
	else
	{
		if((*nn)->leftChild->data == 1 && (*nn)->rightChild->data == 1)
			(*nn)->data = 1;
		if((*nn)->leftChild->data == 0 && (*nn)->rightChild->data == 1)
			(*nn)->data = 0;
		if((*nn)->leftChild->data == 1 && (*nn)->rightChild->data == 0)
			(*nn)->data = 0;
		if((*nn)->leftChild->data == 0 && (*nn)->rightChild->data == 0)
			(*nn)->data = 0;
	}
}
void merge_bottom_up()
{
	/* Remove lead nodes and update the Queue */
	int i;
	// ceating a temporary queue 
	// copy all the contents in temp_ q
	for(i = qq->front; i <= qq->rear; i++)
	{
		Enqueue(qq->array[i],&temp_q);  
	}
	for(i = temp_q->front; i <= temp_q->rear; i++)
	{
		if(temp_q->array[i]->flag_left_child == 1)
		{
			nodeptr  garbage = Dequeue(&qq);  
			continue;
		}
		if(temp_q->array[i]->flag_right_child == 1)
		{
			nodeptr temp = Dequeue(&qq);
			Enqueue(temp->parent,&qq);
		}
	}
	printf("%s \n","printing queue merge_bottom_up");
	printQueue(&qq);
	// qq ( main queue) is updated 
	while(!isEmpty(&qq))
	{
		nodeptr nn = Dequeue(&qq);
		if( nn->flag_left_child == 1)
		{
			//evaluate this node
			int le = get_level(tt->root,nn->label,1);
			printf("label = %d\n",nn->label);
			printf("level = %d\n",le);
			update_data(&nn,le);
		}
		else if( nn->flag_right_child== 1 || nn->flag_root == 1)
		{
			//evaluate rhis node
			//deque it a
			int le = get_level(tt->root,nn->label,1);
			printf("label = %d\n",nn->label);
			printf("level = %d\n",le);
			update_data(&nn,le);
			if(nn->flag_root != 1)
			{
				Enqueue(nn->parent,&qq);
			}
		}
	}
}
void preorder(nodeptr nn)
{
	if(nn == NULL)
		return;
	printf("%d",nn->data);
	preorder(nn->leftChild);
	preorder(nn->rightChild);
}
int main()
{
	scanf("%s",input_string);
	int i;
	int cnt[26];
	memset(cnt,0,sizeof(cnt));
	for(i = 0; i < strlen(input_string); i++)
		cnt[input_string[i]-'A']++; 
	for(i = 0; i < 26; i++)
		if(cnt[i] != 0)
			n++;
	int size = (1<<(n+1))-1;
	printf("n = %d\nsize = %d\n",n,size);

	tt = createTree();
	qq = createQueue(size+10);
	temp_q = createQueue(size+10);
	constructTree(size);
	evaluate_leaf_nodes();

	/*** till now qq ( queue ) has all the leaf nodes ***/
	/*** Evaluate the leaf nodes then merge from bottom up in reverse level order traversal ***/

	merge_bottom_up();
	preorder(tt->root);
	return 0;
}






















