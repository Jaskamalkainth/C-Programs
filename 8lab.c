#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



struct node
{
	char *str;
	struct node* left;
	struct node* right;
	struct node* parent;
};
typedef struct node* nodeptr;

nodeptr createnode()
{
	nodeptr nn = malloc(sizeof(struct node));
	nn->str = malloc(100);
	nn->left = nn->right = nn->parent = NULL;
	return nn;
}

int compare ( char *str1 , char *str2 )
{
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i2 = 0  ;
	if( strcmp(str1,str2) == 0 ) return 1;
	if( strcmp(str1,str2) > 0 ) return 2;
	return -1;
}
int node_height(nodeptr nn)
{
	int ht_l = 0 , ht_r = 0;
	if(nn->left != NULL ) ht_l = node_height(nn->left);
	if(nn->right != NULL ) ht_r= node_height(nn->right);
	return ht_r > ht_l ? ++ht_r : ++ht_l ;
}

int balance_factor( nodeptr nn )
{
	int ans = 0;
	if( nn->left ) ans += node_height(nn->left);
	if( nn->right ) ans -= node_height(nn->right);
	return ans;
}
nodeptr rotate_LL( nodeptr *nn )
{
	nodeptr a = *nn;
	nodeptr b = a->left;

	a->left = b->right;
	b->right = a;

	return b;
}
nodeptr rotate_RR( nodeptr *nn )
{
	nodeptr a = *nn;
	nodeptr b = a->right;

//	printf("%s\n","DEBUGGING");
//	printf("a->right = %s\n",a->right->str);
//	printf("b->left = %s\n",b->left->str);
	a->right = b->left;
	b->left = a;

	return b;
}
nodeptr rotate_LR( nodeptr *nn )
{
	nodeptr a = *nn;
	nodeptr b = a->left;
	nodeptr c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;

	return c;
}
nodeptr rotate_RL( nodeptr *nn )
{
	nodeptr a = *nn;
	nodeptr b = a->right;
	nodeptr c = b->left;

	b->left = c->right;
	a->right = c->left;
	c->left = a;
	c->right = b;

	return c;
}

nodeptr balance_node( nodeptr nn )
{
	nodeptr new_root = NULL;
	if( nn->left )
		nn->left = balance_node(nn->left);
	if( nn->right )
		nn->right = balance_node(nn->right);

	int bal_fact_n = balance_factor(nn);

	if( bal_fact_n == 0 || bal_fact_n == -1 || bal_fact_n == 1 )
		new_root = nn;
	else if ( bal_fact_n >= 2 )
	{
		int bal_fact_n_left_child = balance_factor(nn->left);
		if( bal_fact_n_left_child <= -1 )
			new_root = rotate_LR(&nn);
		else
			new_root = rotate_LL(&nn);
		  
	}
	else if ( bal_fact_n <= -2 )
	{
		int bal_fact_n_right_child = balance_factor(nn->right);
		if( bal_fact_n_right_child >= 1 )
			new_root = rotate_RL(&nn);
		else
			new_root = rotate_RR(&nn);
	}
	return new_root;
}


void balance_tree( nodeptr *root)
{
	nodeptr new_root = NULL;

	new_root = balance_node(*root);
	if( new_root != *root )
	{
		*root = new_root;  
	}
}
void inorder( nodeptr root)
{
	if( root == NULL ) return ;
	inorder(root->left);
	printf("%s %d %d\n",root->str,node_height(root),balance_factor(root));
	inorder(root->right);
}
void preorder( nodeptr root)
{
	if( root == NULL ) return;
	printf("%s %d %d\n",root->str,node_height(root),balance_factor(root));
	preorder(root->left);
	preorder(root->right);
}
void insert( nodeptr *root, nodeptr z)
{
	nodeptr y = NULL;
	nodeptr x = *root;
	while( x != NULL)
	{
		y = x;
		if(strcmp(x->str,z->str) == 0 || strcmp(x->str,z->str) < 0 )
			x = x->right;
		else
			x = x->left;
	}
	z->parent = y;
	if(y == NULL )
		*root = z;
	else if( strcmp(y->str,z->str) == 0 || strcmp(y->str,z->str) < 0)
		y->right = z;
	else
		y->left = z;
	balance_tree(root);
//	inorder(*root);

}

int main()
{
	char inp[100];
	int rc;
	nodeptr root = NULL;
	while( (rc = scanf("%s",inp)) != EOF )
	{
		if( rc != 1 )
			break;
		nodeptr nn = createnode();
		strcpy(nn->str,inp);
		insert(&root,nn);
	}
	inorder(root);
	preorder(root);
	return 0;
}
