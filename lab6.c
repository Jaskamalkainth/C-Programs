#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

typedef struct node
{
	char *str;
	int *idx;
	int num_idx;
}node;

typedef node* nodeptr;

node words[10000];
int num_words;

int main()
{
	int i = 0 ,j = 0, k = 0 , l = 0;
	int curr_page_num = 0;
	char line[100];
	for( i = 0; i < 10000; i++)
	{
		words[i].str = malloc(100);
		words[i].idx = malloc(50);
		words[i].num_idx = 0;
	}
	while(1)
	{
		if( fgets(line,100,stdin) == NULL ) 
			break;
		if( line[0] <= '9' && line[0] >= '0' && strlen(line) == 2) 
		{
			curr_page_num++;
			continue;
		}
		puts(line);
		printf("len  of line = %lu\n",strlen(line));
		i = 0;
		while(line[i] != '\0')
		{
			if(line[i] == ' ' )
			{
				i++;
				continue;
			}
			char temp_str[100];
			k = 0;
			while(line[i] != ' ')
			{
				temp_str[k++] = line[i];
				i++;
			}
			printf("i = %d\n",i);
			temp_str[k] = '\0';
			puts(temp_str);
			// now compare this temp_str with all the existing strings in words[]
			int flag_str = 0;
			printf("num_words = %d\n",num_words);
			for(j = 0;j < num_words; j++)
			{
				if( strcmp(words[j].str,temp_str) == 0 )
				{
					flag_str = 1;
					if( words[j].idx[words[j].num_idx-1] != curr_page_num )
					{
						words[j].idx[words[j].num_idx] = curr_page_num;// index updated
						words[j].num_idx++;
					}
					break;
				}
			}
			if(flag_str == 0 )
			{
				strcpy(words[num_words].str,temp_str);  // str updated
				words[num_words].idx[0] = curr_page_num;// index updated
				words[num_words].num_idx++;
				num_words++;
			}



		}



		printf("num_words = %d\n",num_words);
		printf("%s\n","PRINTING WORD ARRAY");
		for(i = 0; i < num_words; i++)
		{
			printf("[%s,(",words[i].str);
			for( j = 0; j < words[i].num_idx; j++)
				printf(" %d ",words[i].idx[j]);
			printf(") ] \n");
		}

	}
	for(i = 0; i < num_words; i++)
	{
		printf("[%s ,(",words[i].str);
		for( j = 0; j < words[i].num_idx; j++)
			printf(" %d ",words[i].idx[j]);
		printf(") ] \n");
	}
	return 0;  
}
