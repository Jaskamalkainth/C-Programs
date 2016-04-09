#include <stdio.h>
#include <string.h>
#define RANGE 255
 
// The main function that sort the given string str in alphabatical order
void countSort(char *str)
{
    // The output character array that will have sorted str
    char output[strlen(str)];
 
    // Create a count array to store count of inidividul characters and
    // initialize count array as 0
    int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));
 
    // Store count of each character
    for(i = 0; str[i]; ++i)
        ++count[str[i]];
 
    for (i = 1; i <= RANGE; ++i)
		printf("%d ",count[i]);
    // Change count[i] so that count[i] now contains actual position of
    // this character in output array
	printf("\n\n\n");
    for (i = 1; i <= RANGE; ++i)
        count[i] += count[i-1];


    for (i = 1; i <= RANGE; ++i)
		printf("%d ",count[i]);
	printf("\n\n\n");
 
    // Build the output character array
    for (i = 0; str[i]; ++i)
    {
		printf("**%d\n",count[str[i]]);
        output[count[str[i]]-1] = str[i];
        --count[str[i]];
    }
 
    // Copy the output array to str, so that str now
    // contains sorted characters
    for (i = 0; str[i]; ++i)
        str[i] = output[i];
}
 
// Driver program to test above function
int main()
{
    char str[] = "geeksforgeeks";//"applepp";
 
    countSort(str);
 
    printf("Sorted string is %s\n", str);
    return 0;
}
