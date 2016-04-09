#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>



typedef struct node
{
	int i , r , c , p;
	struct node* left;
	struct node* right;
	struct node* parent;
	int f;
}node;

typedef node* nodeptr;

nodeptr creatnode()
{
	nodeptr nn = malloc( sizeof(node));
	nn->parent = NULL;
	nn->left = nn->right = NULL;
	nn->i = nn->r = nn->c = nn->p = -1;
	return nn;
}

void insert( nodeptr *root ,nodeptr z)
{
	nodeptr y = NULL;
	nodeptr x = *root;
	while( x != NULL )
	{
		y = x;
		if( x->p < z->p )
			x = x->right;
		else
			x = x->left;
	}
	z->parent = y;
	if( y == NULL )
		*root = z;
	else if( z->p < y->p )
		y->left  = z;
	else
		y->right = z;
}

nodeptr tree_max(nodeptr nn)
{
	while(nn->right != NULL)
		nn = nn->right;
	return nn;
}
void transplant( nodeptr *root , nodeptr *u , nodeptr *v )
{
	if( (*u)->parent == NULL ) // root node
		*root = *v;
	else if ( (*u)->parent->left == *u )
		(*u)->parent->left = *v;
	else if ( (*u)->parent->right == *u ) 
		(*u)->parent->right = *v;

	if( *v != NULL )
		(*v)->parent = (*u)->parent;
}
nodeptr delete(nodeptr *root )
{
	nodeptr temp_root = *root;
	nodeptr z = tree_max(temp_root);  
	if( z->left == NULL )
		transplant(root,&z,&(z->right));
	else if ( z->right == NULL )
		transplant(root,&z,&(z->left));
	
	z->left = z->right = NULL;
	return z;
}
int isempty(nodeptr root)
{
	return ( root == NULL );  
}
void inorder(nodeptr root)
{
	if(root == NULL )
		return ;
	inorder(root->left);
	printf("%d ",root->p);
	inorder(root->right);
}
int main()
{
	nodeptr root = NULL;
	nodeptr processor_node = NULL;

	nodeptr inp_arr[100];
	int u;
	for( u = 0; u < 100; u++)
	{
		inp_arr[u] = creatnode();  
	}
	char line[100];
	int num_inp = 0;

	int rc,a,b,c,d;
	while((rc = scanf("%d %d %d %d",&a,&b,&c,&d)) != EOF)
	{
		if( rc != 4 )
			break;
		inp_arr[num_inp]->i = a;
		inp_arr[num_inp]->r = b;
		inp_arr[num_inp]->c = c;
		inp_arr[num_inp]->p = d;
		num_inp++;
	}
	int t = 0;
	int idx = 0;
	if( processor_node == NULL) 
	{	
		processor_node = creatnode();
		processor_node->f = -1;
	}
	while(1)
	{
		if( processor_node->f != -1 )
		{
			processor_node->c--;  
			if( processor_node->c == 0 )
				processor_node->f = -1;
		}
		int tflag = 0;
		while(idx < num_inp && inp_arr[idx]->r == t )
		{

			insert(&root,inp_arr[idx]);
			if( processor_node->f != -1  && inp_arr[idx]->p > processor_node->p )
			{
				tflag = 1;
				insert(&root,processor_node);
				processor_node->f = -1;
			}
			idx++;

		}
		if(idx >= num_inp && isempty(root) && processor_node->f == -1)  
			break;
		if( !isempty(root)  )
		{

			nodeptr max_node = tree_max(root);
			if( max_node->p > processor_node->p  || processor_node->f == -1 )
			{
				nodeptr dd = delete(&root);
				processor_node = dd;
				processor_node->f = 0;
			}

		}
		if( processor_node->f != -1 )
			printf("%d\n",processor_node->i);
		if( processor_node->f == -1 && isempty(root) && idx < num_inp )
			printf("0\n");
		t++;
	}

	return 0;
}
