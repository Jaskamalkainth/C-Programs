#include<stdio.h>
#include<stdlib.h>


typedef struct node
{
	int key;
	struct node *left , *right ,*parent;

}node;
typedef node* nodeptr;

nodeptr createNode(int data )
{
	nodeptr nn = malloc(sizeof(node));
	nn->key = data;
	nn->parent = NULL;
	nn->left = NULL;
	nn->right = NULL;
	return nn;
}
void insert(nodeptr *root , nodeptr z)
{
	nodeptr y = NULL;
	nodeptr x = *root;
	while( x != NULL )
	{
		y = x;
		if( x->key < z->key ) x = x->right;
		else x = x->left;
	}
	z->parent = y;
	if( y == NULL )
		*root = z;  
	else if ( z->key < y->key )
		y->left = z;
	else
		y->right = z;
}
nodeptr tree_MIN(nodeptr nn)
{
	while(nn->left != NULL)
		nn = nn->left;  
	return nn;
}
void transplant( nodeptr *root , nodeptr *uu , nodeptr *vv )
{
	nodeptr u = *uu;
	nodeptr v = *vv;
	if( u->parent == NULL ) // root node
		*root = v;
	else if ( (u->parent)->left == u ) 
		u->parent->left = v;
	else if ( (u->parent)->right == u ) 
		u->parent->right = v;

	if( v != NULL )
		v->parent = u->parent;
}
void delete( nodeptr *root , nodeptr z)
{
	if(z->left == NULL )
		transplant(root,&z,&z->right);
	else if( z->right == NULL)
		transplant(root,&z,&z->left);
	else
	{
		nodeptr y = tree_MIN(z->right);
		printf("%d\n",z->key);
		printf("%d\n",y->key);
		if( y->parent!= z)
		{
			transplant(root,&y,&y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(root,&z,&y);
		y->left = z->left;
		y->left->parent = y;
	}

	z->left = z->right = NULL;
}

void inorder(nodeptr root)
{
	if(root == NULL )
		return ;
	inorder(root->left);
	printf("%d ",root->key);
	inorder(root->right);
}

int main()
{
	nodeptr root = NULL;
	nodeptr n1 = createNode(5);
	nodeptr n2 = createNode(4);
	nodeptr n3 = createNode(6);
	nodeptr n4 = createNode(3);

	insert(&root, n1);

	inorder(root);
	printf("\n");
	
	insert(&root, n2);

	inorder(root);
	printf("\n");
	delete(&root,n1);

	inorder(root);
	printf("\n");

	insert(&root,n3);

	inorder(root);
	printf("\n");
	
insert(&root,n1);

printf("##%d\n",n2->key);
printf("##%d\n",n2->left);
printf("##%d\n",n2->right->key);
printf("##%d\n",n2->right->right);
printf("##%d\n",n2->right->left->key);
printf("##%d\n",n2->right->left->left);
printf("##%d\n",n2->right->left->right);
	inorder(root);
 printf("\n");
	insert(&root,n4);

	inorder(root);
printf("\n");
	delete(&root,n3);

	inorder(root);
	printf("\n");
	delete(&root,n1);

	inorder(root);
	printf("\n");
	delete(&root,n2);

	inorder(root);
	printf("\n");
	delete(&root,n4);


	inorder(root);
	printf("\n");

	return 0;
}
