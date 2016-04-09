#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

typedef struct node
{
	char *str;
	char *dup_str;
	int *idx;
	int num_idx;
}node;

typedef node* nodeptr;

node words[10000];
int num_words;
int isNumeric(const char *str) 
{
	while(*str != '\0')
	{
		if(*str < '0' || *str > '9')
			return 0;
		str++;
	}
	return 1;
}
int isword(const char *str)
{
	for(;*str ;str++) 
	{
		if(!isalpha(*str))
			return 0;
	}
	return 1;
}
void print_words()
{
	int j,i;
	for(i = 0; i < num_words; i++)
	{
		printf("%s ",words[i].str);
		for( j = 0; j < words[i].num_idx; j++)
		{
			if ( j == words[i].num_idx-1 )
				printf("%d ",words[i].idx[j]);
			else
				printf("%d, ",words[i].idx[j]);
		}
		printf("\n");
	}

}
void count_sort(int l)
{
	printf("\nFOR l = %d\n",l);
	node out_words[10000];
	int count[28];
	memset(count,0,sizeof(count));
	int i ,j, k;
	for( i = 0; i < 10000; i++)
	{
		out_words[i].str = malloc(100);
		out_words[i].dup_str = malloc(100);
		out_words[i].idx = malloc(50);
		out_words[i].num_idx = 0;
	}


	// count[0] = '0'
	// count[1] = 'a'
	for(i = 0; i < num_words; i++)
	{
		if( words[i].dup_str[l] == '0' )
		{
			count[0]++;  
		}
		else 
		{
			count[ words[i].dup_str[l] - 'a' + 1]++;  
		}
	}
	for( i = 0; i < 28; i++)
		printf("%d ",count[i]);
	puts("\n");
	for(i = 1; i < 28; i++)
		count[i] += count[i-1];
	for( i = 0; i < 28; i++)
		printf("%d ",count[i]);

	puts("\nceck");
	for(i = num_words-1; i >= 0; i--)
	{
		if( words[i].dup_str[l] == '0' )
		{
			out_words[ count[0] - 1] = words[i];
			count[0]--;
		}
		else 
		{
			out_words[ count[ words[i].dup_str[l] - 'a' + 1] - 1] = words[i];
			count[words[i].dup_str[l]-'a'+1]--;
		}
	}
	for( i = 0; i < num_words; i++)
		words[i] = out_words[i];
	print_words();
}


void update_dup_str(int mx_len)
{
	// make every string of same length. add '0' in suffixes
	// store in dup_str
	int i ,j;
	for(i = 0;i  < num_words; i++)
	{
		char str[100] ; strcpy(str,words[i].str);  
		int lenstr = strlen(str);
		int diff = mx_len - lenstr; // add diff '0'
		for(j = lenstr; j < mx_len; j++)
		{
			str[j] = '0';  
		}
		str[j] = '\0';
		strcpy(words[i].dup_str,str);
	}
}

void radix_sort()
{
	int i , l;
	int mx_len  = 0;
	for(i = 0; i < num_words;i++)
	{
		int temp_len = strlen(words[i].str);
		if(temp_len > mx_len )
			mx_len = temp_len;
	}
	update_dup_str(mx_len);
	puts("inside radix_sort");
	print_words();
	printf("%mx_len = %d\n",mx_len);

	for(l = mx_len-1; l >= 0; l--)
	{
		count_sort(l);
	}
}



int main()
{
	int i = 0 ,j = 0, k = 0 , l = 0;
	int curr_page_num = 0;
	char line[100];
	for( i = 0; i < 10000; i++)
	{
		words[i].str = malloc(100);
		words[i].dup_str = malloc(100);
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
		line[strlen(line)-1] = '\0';
		puts(line);
		printf("len  of line = %lu\n",strlen(line));
		i = 0;
		for(; i < strlen(line); )
		{
			printf("i* = %d\n",i);
			if(line[i] == ' ' )
			{
				i++;
				continue;
			}
			char temp_str[100];
			k = 0;
			while(line[i] != ' ')
			{
				if(line[i] == '\0') break;
				printf("line[%d] = %c\n",i,line[i]);
				temp_str[k++] = line[i];
				i++;
			}
			temp_str[k] = '\0';
			printf("i = %d\n",i);
			printf("temp_str = %s\n",temp_str);
			printf("len_temp_str = %lu\n",strlen(temp_str));
			// now compare this temp_str with all the existing strings in words[]
			int flag_str = 0;
			//	printf("num_words = %d\n",num_words);
			int la = 0;
			for(;temp_str[la];la++)temp_str[la] = tolower(temp_str[la]);  
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
				if( isNumeric( temp_str ) ) continue;
				if( !isword(temp_str)) continue;
				strcpy(words[num_words].str,temp_str);  // str updated
				words[num_words].idx[0] = curr_page_num;// index updated
				words[num_words].num_idx++;
				num_words++;
			}
		}
	}
	for(i = 0; i < num_words; i++)   strcpy(words[i].dup_str,words[i].str);
	puts("PRINTITITITITITITI\n\n\n");
	print_words();

	radix_sort();
	puts("\n\nFINAL ANS");
	print_words();

	/********* input is done *******/

	return 0;  
}
