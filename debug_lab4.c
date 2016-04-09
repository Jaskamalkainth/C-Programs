#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
 *
 * Huffman Problem
 *
 */


/*
 *  min_heapify()
 *  build_min_heap()
 *  heap_extract_min()
 *  heap_decrease_key()
 *  min_heap_insert()
 */

/*
 * Procedure:
 * 1.  Make the frequency table.
 * 2. initialize the min_priority_queue using the frequency table ( frequency as the key ).
 *     FIFO should be there.
 * 3. Create the Huffman tree using the Huffman Algo.
 * 4. count the number of nodes in the huffman tree (OUTPUT1)
 * 5. Post order traversal ( OUTPUT2)
 * 6.Print the encoded message (OUTPUT3)
 */


struct minheapNode
{
	char data;  
	int freq;
	int entry_time;
	struct minheapNode *left;
	struct minheapNode *right;
};
typedef struct minheapNode* minheapNodePTR;
struct minheap
{
	int size;
	int capacity;
	minheapNodePTR *array;
};
typedef struct minheap* minheapPTR;

int label = 0;
minheapNodePTR newNode(char data , int freq )
{
	minheapNodePTR nn = malloc(sizeof(struct minheapNode));
	nn->data = data;
	nn->freq = freq;
	nn->left = nn->right = NULL;
	label++;
	nn->entry_time = label;
	return nn;
}

minheapPTR createMinHeap ( int capacity )
{
	minheapPTR hh = malloc(sizeof(struct minheap));
	hh->size = 0;
	hh->capacity = capacity;
	hh->array = malloc(capacity*sizeof(minheapPTR));
	return hh;
}

void swapNode( minheapNodePTR *a , minheapNodePTR *b )
{
	minheapNodePTR temp = *a;
	*a = *b;
	*b = temp;
}
/***************** min_heapify() **************/
void min_heapify(minheapPTR hh , int i)
{
	int smallest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;
	if( left < hh->size && hh->array[left]->freq < hh->array[smallest]->freq )
		smallest = left;
	if( left < hh->size && ( hh->array[left]->freq == hh->array[smallest]->freq))
	{
		if( hh->array[left]->entry_time < hh->array[smallest]->entry_time)
			smallest = left;
	}

	if( right < hh->size && hh->array[right]->freq < hh->array[smallest]->freq )
		smallest = right;
	if( right < hh->size && ( hh->array[right]->freq == hh->array[smallest]->freq))
	{
		if( hh->array[right]->entry_time < hh->array[smallest]->entry_time)
			smallest = right;
	}
	if( left < hh->size && right < hh->size && smallest < hh->size)
	{
	printf("%c | %d\n",hh->array[left]->data,hh->array[left]->freq); 
	printf("%c | %d\n",hh->array[smallest]->data , hh->array[smallest]->freq); 
	printf("%c | %d\n",hh->array[right]->data , hh->array[right]->freq); 
	}

	printf("inside min_heapify %d %d\n\n",smallest,hh->array[smallest]->freq);
	if( smallest != i )
	{
		swapNode(&(hh->array[smallest]) , &(hh->array[i])); 
		min_heapify(hh , smallest);
	}
}

minheapNodePTR extractMin (minheapPTR hh )
{
	minheapNodePTR nn = hh->array[0];
	/************* here is the problem i guess *************/
	hh->array[0] = hh->array[hh->size - 1];
	hh->size -= 1;
	min_heapify(hh,0);
	return nn;
}

void insertminHeap(minheapPTR hh , minheapNodePTR nn )
{
	hh->size += 1;
	int i = hh->size - 1;
	while ( i & (nn->freq < hh->array[(i-1)/2]->freq ))
	{
		hh->array[i]  = hh->array[(i-1)/2];
		i = (i-1)/2;
	}
	hh->array[i] = nn;
}

void buildminHeap( minheapPTR hh )
{
	int n = hh->size - 1;
	int i;
	for(i = (n-1)/2; i >= 0 ; i--)
	{
		printf("BUILDING i  =  %d\n",i);
		min_heapify(hh,i);
	}
}

int leafnode ( minheapNodePTR nn )
{
	if ( nn->left == NULL && nn->right == NULL) 
		return 1;
	else
		return 0;
}
void print_min_heap(minheapPTR hh )
{
	int n = hh->size;
	int i ;
	printf("%s\n","PRINTIGN MIN HEAP");
	for(i = 0; i < n; i++)
	{
		printf("(%c , %d)\n",hh->array[i]->data , hh->array[i]->freq);  
	}
	printf("\n");
}

/********************* Huffman tree ALgo ***************/

int output1_num_of_nodes_in_tree = 0;
minheapNodePTR build_Huffman_tree( char data[] , int freq[] , int size)
{
	minheapNodePTR left ,right , top;
	minheapPTR hh = createMinHeap(size);
	/* building minheap */
	int i;
	for(i = 0; i < size; i++)
		hh->array[i] = newNode(data[i],freq[i]);
	hh->size = size;
	
	printf("minheap size = %d\n",hh->size);
	print_min_heap(hh);
	buildminHeap(hh);
	print_min_heap(hh);
		/* building minheap END */

	/* huffman ALgo */

	while ( hh->size != 1 )
	{
		left = extractMin(hh);
		right = extractMin(hh);
		printf("%s\n","DEBUGGING INSIDE BUILD build_Huffman_tree \n");
		printf("left data  :%c\n",left->data);
		printf("right data :%c\n",right->data);
		top = newNode('0' , left->freq + right->freq);
		output1_num_of_nodes_in_tree++;
		top->left = left;
		top->right = right;
		insertminHeap(hh , top);
		print_min_heap(hh);
	}
	return extractMin(hh);
	// returns the root node of the Huffman tree
	// with this we can do Postorder , Inorder traversal and also print the huffman codes
}

char map_char_to_code[30][100];

void print_Huffman_code( minheapNodePTR root , int arr[] , int top )
{
	if( root -> left )
	{
		arr[top] = 0;
		print_Huffman_code(root->left,arr,top+1);
	}
	if( root -> right )
	{
		arr[top] = 1;
		print_Huffman_code(root->right,arr,top+1);
	}
	if( leafnode(root) )
	{
		int i;
		for(i = 0; i < top; i++)
		{
			if( arr[i] == 0 )
				map_char_to_code[root->data - 'A'][i] = '0';
			if( arr[i] == 1 )
				map_char_to_code[root->data - 'A'][i] = '1';
		}
	}
}



void postorder( minheapNodePTR root)
{
	if ( root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%c",root->data);
}
void inorder( minheapNodePTR root)
{
	if ( root == NULL)
		return;
	inorder(root->left);
	printf("%c",root->data);
	inorder(root->right);
}

int main()
{

	char inp[1000];
	scanf("%s",inp);
	int len = strlen(inp);
	int i , j;
	int tempfreq[27] = {0};
	for(i = 0; i < len; i++)
		tempfreq[inp[i]-'A']++;
	int cnt = 0;
	for(i = 0; i < 27; i++)
		if(tempfreq[i] != 0)
			cnt++;

	int freq[cnt] ;
	for(i = 0; i < cnt; i++)
		freq[i] = 0;
	char arr[cnt];
	int k = 0;
	for(i = 0; i < len; i++)
	{
		char ch = inp[i];
		int flag = 0;
		for( j = 0; j < i; j++ )
		{
			if( inp[j] == ch )
				flag = 1;
		}
		if( flag == 1 )
			continue;
		else
		{
			if( i != 0)
				k++;
		}
		arr[k] = ch;
		printf("llalalal k = %d , %c %d \n",k ,arr[k],freq[k]);
		for(j = 0; j < len; j++)
		{
			if( inp[j] == ch )
			{
				freq[k]++;
			}
		}
	}
	// char arr[] 
	// int freq[] 

	printf("%s\n","char and freq array\n");
	for(i = 0; i < cnt ; i++)
		printf("%c %d \n",arr[i],freq[i]);


	minheapNodePTR root = build_Huffman_tree (arr , freq ,cnt );

/*
	printf("%s\n","DEBUGGING TREE BEGIN\n");
	printf("%c\n",root->data);
	printf("%c\n",root->left->data);
	printf("%c\n",root->right->data);
	printf("%c\n",root->right->left->data);
	printf("%c\n",root->right->right->data);
	printf("%c\n",root->right->right->left->data);
	printf("%c\n\n",root->right->right->right->data);
	printf("%s\n","DEBUGGING TREE END\n");
*/
	
	
	printf("%d\n",output1_num_of_nodes_in_tree+cnt);

	postorder(root);
	printf("\n");
	inorder(root);
	printf("\n");
	// huffman coding
	
	int farr[1000];
	int top = 0;
	for(i = 0; i < 30; i++)
	{
		memset(map_char_to_code[i],'#',100);  
	}
	print_Huffman_code(root,farr,top);
	printf("%%%% %c \n", map_char_to_code[0][0]);
	for(i = 0; i < len; i++)
	{
		char ch = inp[i];
		int k = 0;
		while(map_char_to_code[ch-'A'][k] != '#' )
		{
			printf("%c",map_char_to_code[ch-'A'][k++]);
		}
	}
	return 0;
}
