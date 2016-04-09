#include<stdio.h>
#include<stdlib.h>


/*
 * O(n^3)
 *
int C(int n , int r)
{
	int res = 1;
	if ( r > n-r )
	{
		r = n-r;  
	}

	int i;
	for(i = 0; i < r; i++)
	{
		res *= ( n-i );
		res /= ( i+1 );
	}
	return res;
}
int main()
{
	int n ; scanf("%d",&n);
	// C(line , i )
	int line , j;
	for(line = 0;line <= n; line++)
	{
		for(j = 0; j<=line;j++)
		{
			printf("%d ", C(line,j) );
		}

		printf("\n");
	}
}
*/


/*
 *
 *  O(n^2) with O(n^2) space complexity
int main()
{
	int n; scanf("%d",&n);

	int arr[n+1][n+1];
	int line , i ;
	for(line = 0; line <= n; line++)
	{
		for(i = 0; i<= line; i++)
		{
			if ( line == i || i == 0 )
				arr[line][i] = 1;
			else
			{
				arr[line][i] = arr[line-1][i-1] + arr[line-1][i];  
			}
			printf("%d " , arr[line][i]);
		}

		printf("\n");
	}
	return 0;
}


*/

/*
 *
 *
 *
 *  Using Dynamic memory allocation 
 *
 *  O(n^2)
 *
 * 
 */


int main()
{
	int n; scanf("%d",&n);
	
	int ** pt =   calloc((n+2),sizeof(int *));  
	int i , j;

	for(i = 0; i <= n; i++)
	{
		pt[i] = calloc(i+1,sizeof(int));  
	}

	/*
	 *
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			scanf("%d",&pt[i][j]);  
		}
	}
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%d ",pt[i][j]);  
		}
		printf("\n");
	}

	*/
	

	for(i = 0; i <= n; i++)
	{
		for(j = 0; j <= i; j++)
		{
			if( j == i || i == 0)
				pt[i][j] = 1;
			else
			{
				pt[i][j] = pt[i-1][j-1] + pt[i-1][j];
			}
		}
	}
	for(i = 0; i <= n; i++)
	{
		for(j = 0; j <= i; j++)
		{
			printf("%d ",pt[i][j]);  
		}
		printf("\n");
	}


	for(i = 0; i <= n; i++)
	{
		free(pt[i]);  
	}
	free(pt);
	
}
