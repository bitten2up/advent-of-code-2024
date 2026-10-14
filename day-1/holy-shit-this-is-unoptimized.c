#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
        }
       if (min != i) {
            int temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
    }
}
int main(int argc, char* argv[])
{
    FILE* input = fopen("test.txt", "r");

    fseek(input, 0L, SEEK_END);
    int inputsize = ftell(input);
    rewind(input);
    
    char* buffer = calloc(1, inputsize+1);

    if (buffer == NULL)
	{
		fclose(input);
		free(buffer);
		fputs("mem alloc failed\n", stderr);
		exit(1);
	}
    if (1 != fread(buffer,inputsize, 1, input))
	{
		fclose(input);
        free(buffer);
		fputs("read failed, or file is blank\n", stderr);
        exit(1);
	}
    fclose(input);
    int start, end, total;
    start = end = total = 0;

    uint32_t array[2][2000];
    int arrayEnd = -1;
    
    for (int i = 0; i <= inputsize; i+=12)
    {
        if (buffer[i] == 0)
            break;

        //printf("%i:%c\n", buffer[i]-'0', buffer[i+2]);
        arrayEnd++;
        array[0][arrayEnd] = array[1][arrayEnd] = 0;
        for (int x = 0; x < 5; x++)
        {
            array[0][arrayEnd] = array[0][arrayEnd] * 10 + buffer[i+x]-'0';
            array[1][arrayEnd] = array[1][arrayEnd] * 10 + buffer[i+6+x]-'0';
        }
        //printf("%i:%i\n",array[0][arrayEnd],array[1][arrayEnd]);
    }
    printf("\n\n");
    int n = arrayEnd+1;

    printf("sorry this is for part 2 :3\n");
    for (int i = 0; i <= arrayEnd; i++)
    {
        int counter = 0;
        for (int x = 0; x <= arrayEnd; x++)
            if (array[0][i] == array[1][x])
                counter++;
        //printf("%i\n",array[0][i] * counter);
        total += array[0][i] * counter;

    }

    printf("Similarity score: %i", total);
    printf("\n\n%i\n",n+1);
    selectionSort(array[0],n);
    selectionSort(array[1],n);

    for (int i = 0; i <= arrayEnd; i++)
    {
        //printf("%i:%i\n",array[0][i],array[1][i]);
        if (array[0][i] > array[1][i])      
        {
            //printf("%i-%i+", array[0][i], array[1][i]);
            total += array[0][i] - array[1][i];
        }
        else
        {
            //printf("%i-%i+", array[1][i], array[0][i]);
            total += array[1][i] - array[0][i];
        }
    }
    printf("\n");

    printf("Value is: %i\n", total);
    free(buffer);
    buffer = NULL;
    return 0;
}
