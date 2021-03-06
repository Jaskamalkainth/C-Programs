#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


/** LAB: 05  **/
/*
 *
 * 1: Create the Divide tree ( top-down approach ) using Level order traversal .
 * 2: when this tree is ready ,queue will be empty and stack will have all the nodes so fill the queue with all the leaf nodes.
 * 3: perform the reverse level order traversal on this and evaluate the nodes.
 *
 * Printing rule:
 * FOR LEAF NODES: N1 X N2 = N
 * FOR NON-LEAF NODES : N1 X N2 = B X 10^N + (A - B - C) X 10^N + C = N
*/

struct node
{
	long long int value;
	int label;
	char *str;
	int flag_leftchild;
	int flag_rightchild;
	int flag_middlechild;
	struct node* parent;
	struct node* leftchild;
	struct node* middlechild;
	struct node* rightchild;
};
typedef struct node* nodeptr;

int lastlabel;

nodeptr newnode()
{
	nodeptr nn = malloc(sizeof(struct node));
	nn->leftchild = NULL;
	nn->middlechild = NULL;
	nn->rightchild = NULL;
	if(lastlabel == 0)
		nn->parent = NULL;
	lastlabel++;
	nn->label = lastlabel;
	nn->str = malloc(100);
	nn->value = -1;
	return nn;
}
/****** queue BEGIN *****/
struct Queue
{
	int front , rear;
	int size;
	nodeptr *array;
};
typedef struct Queue* queueptr;
queueptr createQueue( int size )
{
	queueptr qq = malloc(sizeof(struct Queue));
	qq->front = qq->rear = -1;
	qq->size = size;
	qq->array = malloc(size*sizeof(nodeptr));
	int i;
	for(i = 0; i < size; i++)
		qq->array[i] = NULL;
	return qq;
}

int isEmpty(queueptr *qq )
{
	if( (*qq)->front == -1 )
		return 1;
	else
		return 0;
}

int sizeone(queueptr *qq )
{
	return (*qq)->front == (*qq)->rear;
}
void Enqueue( nodeptr nn , queueptr *qq )
{
	queueptr tq = *qq;
	(*qq)->array[++(*qq)->rear] = nn;
	if( isEmpty( &tq ))
		(*qq)->front++;
}

nodeptr Dequeue ( queueptr *qq )
{
	queueptr tq = *qq;
	if( isEmpty(&tq) )
		return NULL;
	nodeptr temp = (*qq)->array[(*qq)->front];
	if(sizeone(&tq))
		(*qq)->front = (*qq)->rear = -1;
	else
		(*qq)->front++;
	return temp;
}

nodeptr getfront(queueptr *qq )
{
	return (*qq)->array[(*qq)->front];  
}

void printQueue( queueptr *q )
{
	printf("%s\n","PRINTING QUEUE");
	int i;
	queueptr tq = *q;
	if( isEmpty(&tq))
		printf("%s\n","EMPTY queue");
	else
		for(i = (*q)->front ; i <= (*q)->rear; i++)
			printf("(%s )",(*q)->array[i]->str);
}
/****** queue END *****/
/******** stack BEGIN********/
struct stack
{
	int front;
	int size;
	nodeptr *array;
};
typedef struct stack* stackptr;

stackptr createStack(int size)
{
	stackptr ss = malloc(sizeof(struct stack));
	ss->front = -1;
	ss->array = malloc(size*sizeof(nodeptr));
	int i;
	for(i = 0; i < size;i++)
		ss->array[i] = NULL;
	return ss;
}
int isEmpty_stack(stackptr ss)
{
 return (ss->front == -1 );
}
void push(stackptr *ss ,nodeptr nn )
{
	(*ss)->size++;
	(*ss)->array[++(*ss)->front] = nn;
}
void pop(stackptr *ss)
{	
	(*ss)->front--;
	(*ss)->size--;
}
nodeptr top(stackptr *ss)
{
	return (*ss)->array[(*ss)->front];
}
void printstack(stackptr ss)
{
	int i; 
	printf("%s\n","PRINTING STACK:");
	for(i = 0; i <= ss->front; i++)
	{
		printf("[%s ]",ss->array[i]->str);  
	}
	printf("\n");
}

/******** stack END********/





struct tree
{
	nodeptr root;
	int size;
};
typedef struct tree* treeptr;
treeptr createTree()
{
	treeptr tt = malloc(sizeof(struct tree));
	tt->size = 0;
	tt->root = newnode();
	return tt;
}

queueptr main_queue;
treeptr  main_tree;
stackptr main_stack;

void  make_it_even_if_odd_len(nodeptr *nn)
{
	char str[100];
	strcpy(str,(*nn)->str);
	char num1str[100];
	char num2str[100];
	int i = 0;
	while( str[i] != 'X' )
	{
		num1str[i] = str[i];  
		i++;
	}
	num1str[i] = '\0';
	i++;
	int k = 0;
	while(str[i] != '\0')
	{
		num2str[k++] = str[i];
		i++;
	}
	
	num2str[k] = '\0';
	printf("input strinf = %s\n",(*nn)->str);
	printf("\nnum1str = %s\n",num1str);
	printf("\nnum2str = %s\n",num2str);

	
	int len1 = strlen(num1str);
	int len2 = strlen(num2str);
	int new_len;

	if( len1 > len2 )
		new_len = len1;
	else
		new_len = len2;

	if(new_len&1) new_len++;

	int num_zero_num1str = new_len-len1;
	int num_zero_num2str = new_len-len2;
	
	char newstr1[50],newstr2[50];

	k = 0;
	for(i = 0; i < num_zero_num1str+len1;i++)
	{
		if(i < num_zero_num1str )
			newstr1[i] = '0';
		else
			newstr1[i] = num1str[k++];
	}
	newstr1[i] = '\0';
	k = 0;
	for(i = 0; i < num_zero_num2str+len2;i++)
	{
		if(i < num_zero_num2str )
			newstr2[i] = '0';
		else
			newstr2[i] = num2str[k++];
	}
	newstr2[i] = '\0';
	printf("\nnew1str = %s\n",newstr1);
	printf("\nnew2str = %s\n",newstr2);
	char *final_str = malloc(100);
	sprintf(final_str,"%sX%s",newstr1,newstr2);
	strcpy((*nn)->str,final_str);
}




void computeABC(char **childAstr , char **childBstr , char **childCstr,char tempstr[100])
{
	printf("%s\n","FFFFFFFFUUUUUUUCCCCCCCCCKKKKKKKKKK");
	printf("%s\n",tempstr);
	char str[100];
	memcpy(str,tempstr,100);
	// A = (H1 + L1 )* ( H2 + L2 )
	
	char *checking = malloc(100);
	char num1str[100];
	char num2str[100];
	int i = 0;
	while( str[i] != 'X' )
	{
		num1str[i] = str[i];  
		i++;
	}
	num1str[i] = '\0';
	i++;
	int k = 0;
	while(str[i] != '\0')
	{
		num2str[k++] = str[i];
		i++;
	}
	num2str[k] = '\0';

	// num1str[] = 1234
	// num2str[] = 4321
	
	int H1len = strlen(num1str)/2;
	int L1len = H1len;
	int H2len = strlen(num2str)/2;
	int L2len = H2len;

	char H1str[100];
	char L1str[100];
	char H2str[100];
	char L2str[100];
	for(i = 0; i < H1len;i++)
	{
		H1str[i] = num1str[i];  
	}
	k = 0;
	for(i = H1len; i < 2*H1len;i++)
	{
		L1str[k++] = num1str[i];  
	}
	for(i = 0; i < H2len;i++)
	{
		H2str[i] = num2str[i];  
	}
	k = 0;
	for(i = H2len; i < 2*H2len;i++)
	{
		L2str[k++] = num2str[i];  
	}
	printf("H1str = %s\n",H1str);
	printf("L1str = %s\n",L1str);
	printf("H2str = %s\n",H2str);
	printf("L2str = %s\n",L2str);
	printf("%s\n","debug");
	H1str[H1len] = '\0';
	L1str[L1len] = '\0';
	H2str[H2len] = '\0';
	L2str[L2len] = '\0';
	int H1 = atoi(H1str);
	int L1 = atoi(L1str);
	int H2 = atoi(H2str);
	int L2 = atoi(L2str);
	printf("H1 = %d\n",H1);
	printf("L1 = %d\n",L1);
	printf("H2 = %d\n",H2);
	printf("L2 = %d\n",L2);
	int HL1 = H1+L1;
	int HL2 = H2+L2;
	printf("HL1 = %d\n",HL1);
	printf("HL2 = %d\n",HL2);

	char *outstrA = malloc(100);
	char *outstrB = malloc(100);
	char *outstrC = malloc(100);

	sprintf(outstrA,"%dX%d",HL1,HL2);
	sprintf(outstrB,"%dX%d",H1,H2);
	sprintf(outstrC,"%dX%d",L1,L2);

	*childAstr = outstrA;
	*childBstr = outstrB;
	*childCstr = outstrC;
	printf("outstrA = %s\n",outstrA);
	printf("outstrB = %s\n",outstrB);
	printf("outstrC = %s\n",outstrC);
}
void constructTREE()
{
	main_tree->size = 1;

	Enqueue(main_tree->root, &main_queue);
	printf("BURRRRRR  %s\n",main_tree->root->str);
	make_it_even_if_odd_len(&main_tree->root);
	printf("BURRRRRR  %s\n",main_tree->root->str);
	while( !isEmpty(&main_queue))
	{
		nodeptr temp = Dequeue(&main_queue);
		if( strlen(temp->str) == 3 )
		{
			push(&main_stack , temp);
			continue;
		}
		// if temp is a leaf node then don't enqueue child A , childB , childC
		nodeptr childA = newnode();
		nodeptr childB = newnode();
		nodeptr childC = newnode();
		childA->parent = childB->parent = childC->parent =  temp;
		char *childAstr , *childBstr, *childCstr;
		make_it_even_if_odd_len(&temp);
		computeABC(&childAstr , &childBstr , &childCstr, temp->str);
		strcpy(childA->str,childAstr);
		strcpy(childB->str,childBstr);
		strcpy(childC->str,childCstr);
		childA->flag_leftchild = 1;
		childB->flag_middlechild = 1;
		childC->flag_rightchild = 1;

		temp->leftchild = childA;
		temp->middlechild = childB;
		temp->rightchild = childC;

		Enqueue(childA , &main_queue);
		Enqueue(childB , &main_queue);
		Enqueue(childC , &main_queue);
		main_tree->size += 3;
		printQueue(&main_queue);
	}
}
void task2()
{
	while(!isEmpty_stack(main_stack))
	{
		nodeptr temp = top(&main_stack);
		pop(&main_stack);
		Enqueue(temp,&main_queue);
	}
}


void update_leaf_node(nodeptr *leafnode )
{
	int value ;
	char ch[3];
	memcpy(ch,(*leafnode)->str,3);
	int a = ch[0]-'0'; int b = ch[2]-'0';
	value = a*b;
	(*leafnode)->value = value;
	printf("%s=%lld\n",(*leafnode)->str,(*leafnode)->value);
}


void evaluate_leafnodes(queueptr *qq)
{
	int i;
	for(i = (*qq)->front; i<= (*qq)->rear; i++)
	{
		update_leaf_node(&((*qq)->array[i]));  
	}
}
void remove_extra_0(nodeptr *nn)
{
    char str[100];
    memcpy(str,(*nn)->str,100);
    char num1str[100];
    char num2str[100];
    int i = 0;
    while( str[i] != 'X' )
    {
        num1str[i] = str[i];
        i++;
    }
    num1str[i] = '\0';
    i++;
    int k = 0;
    while(str[i] != '\0')
    {
        num2str[k++] = str[i];
        i++;
    }
    num2str[k] = '\0';
    char newstr1[50],newstr2[50];
    
    i = 0;
    while(num1str[i] == '0')  	i++;
    k = 0;
    while(num1str[i] != '\0')	newstr1[k++] = num1str[i++];
    newstr1[i] = '\0';
    
    i = 0;
    while(num2str[i] == '0')  	i++;
    k = 0;
    while(num2str[i] != '\0')	newstr2[k++] = num2str[i++];
    newstr2[i] = '\0';
    
    if(strlen(newstr1) == 0 ) { newstr1[0] = '0'; newstr1[1] = '\0'; }
    if(strlen(newstr2) == 0 ) { newstr2[0] = '0'; newstr2[1] = '\0'; }
    char *final_str = malloc(100);
    sprintf(final_str,"%sX%s",newstr1,newstr2);
    strcpy((*nn)->str,final_str);
    
}

void update_value(nodeptr *nn)
{
	printf("%s\n","inside update_value");

	char str[100];
	memcpy(str,(*nn)->str,100);
	
	char num1str[100];
	char num2str[100];
	int i = 0;
	while( str[i] != 'X' )
	{
		num1str[i] = str[i];  
		i++;
	}
	num1str[i] = '\0';
	i++;
	int k = 0;
	while(str[i] != '\0')
	{
		num2str[k++] = str[i];
		i++;
	}
	num2str[k] = '\0';
	int n = strlen(num1str);
	// calc n
	long long int A,B,C;
	long long int N;
	A= (*nn)->leftchild->value;
	B= (*nn)->middlechild->value;
	C= (*nn)->rightchild->value;

	printf("%s\n",num1str);
	printf("%s\n",num2str);
	long long int x = 1;
	printf("n = %d\n",n);
	n /= 2;
	while(n!=0)
		x *= 10,n--;
	printf("x = %lld\n",x);
	N = B*x*x + (A-B-C)*x + C;
	(*nn)->value = N;
	char out_str[100];
	sprintf(out_str , "%lldX%lldX%lld+(%lld-%lld-%lld)X%lld+%lld=%lld",B,x,x,A,B,C,x,C,N);
    remove_extra_0(nn);
    printf("%s=%s\n",(*nn)->str,out_str);}


void evaluate_the_tree(queueptr *main_queue)
{
	queueptr tempqueue = createQueue(1000);
	int i;
	for(i = (*main_queue)->front; i <= (*main_queue)->rear; i++)
		Enqueue((*main_queue)->array[i] , &tempqueue);
	for(i = tempqueue->front; i <= tempqueue->rear; i++)
	{
		if( tempqueue->array[i]->flag_leftchild == 1 || tempqueue->array[i]->flag_middlechild == 1)
		{
			nodeptr shit = Dequeue(main_queue);
		}

		if( tempqueue->array[i]->flag_rightchild == 1)
		{
			nodeptr tt = Dequeue(main_queue);
			Enqueue(tt->parent, main_queue);
		}
	}

	printQueue(main_queue);
	printf("%s\n","inside evaluate_the_tree");
	printf("%s\n","deeeeebug");
	while( !isEmpty(main_queue))
	{
		nodeptr nn = Dequeue(main_queue);
		if(nn->flag_leftchild == 1 )
		{
			update_value(&nn);
		}
		if(nn->flag_middlechild== 1 )
		{
			update_value(&nn);
		}
		if(nn->flag_rightchild == 1 )
		{
			update_value(&nn);
			Enqueue(nn->parent,main_queue);
		}
		printQueue(main_queue);
	}
	update_value(&main_tree->root);
}

int main()
{
	char inp[100]; 
	scanf("%s",inp);
	main_tree = createTree();
	main_queue = createQueue(1000);
	main_stack = createStack(1000);
	memcpy(main_tree->root->str,inp,100);

	// works fine 7333 overflowmemcpy(main_tree->root->str,"6333X1234",100);
/*
	char *outstrA;
	char *outstrB;
	char *outstrC;
	computeABC(&outstrA,&outstrB,&outstrC,"1234X4321");
	printf("A = %s\n",outstrA);
	printf("B = %s\n",outstrB);
	printf("C = %s\n",outstrC);
*/
	constructTREE();
	printstack(main_stack);
	printQueue(&main_queue);
	task2();
	printf("%s\n","deeeeebug");
	evaluate_leafnodes(&main_queue);
	printQueue(&main_queue);
	evaluate_the_tree(&main_queue);
	printQueue(&main_queue);


	
	return 0;
}
