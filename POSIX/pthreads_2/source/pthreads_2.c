/*
 * pthreads_2.c
 *
 *  Created on: Sep. 16, 2019
 *      Author: takis
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define	MAXINTS		30 // maximum number of integers that user may enter

/*
 * global variables and constants
 */
int		num_ints=0;		// current number of integers entered by user

/*
 * thread function to display the set of numbers periodically
 */
void	*disp_nums_thread(void *data)
{
	int	*x = (int *)data;	//cast the data passed to an int (array)

	if ((num_ints % 10)==0) // display the set every 10 integers
	{
		printf("the current integer set is: ");
		for (int i=0; i!=num_ints; ++i)
		{
			printf("%d ", x[i]);
		}
		printf("\n");
	}
	usleep(1000);			// put thread to sleep in order to save CPU cycles
	return x;              	// return the pointer to x
}

/*
 * thread function to display the average of the set of numbers periodically
 */
void 	*disp_avg_thread(void *value)
{
	float	*avg = (float *)value;    //cast the data passed to an int

	if ((num_ints % 4)==0) // display the average every 4 integers
	{
		printf("the current average is: %f \n", *avg);
	}
	usleep(1000);			// put thread to sleep in order to save CPU cycles
	return avg;            	//return the pointer to x
}


/*
 * thread function computes average of current set
 */
void	*avg_thread(void *arr)
{
	int	sum=0;
	for (int i=0; i!=num_ints; ++i)
	{
		sum += arr
	}
}

/*
 * thread function sorts data set in its current set
 */
void	*bubb_sort_thread(void *arr)
{
	int 	*x = (int *) arr;	// cast the passed data to integer type
	bool 	swaps = 1; 			// best to assume swaps will be needed
	int		temp;

	while (swaps)
	{
		swaps = 0; // if a swap occurs, this is toggled
		for (int i=0; i!=(num_ints-1); ++i)
		{
			if (x[i+1] < x[i])
			{
				temp 	= x[i];
				x[i] 	= x[i+1];
				x[i+1] 	= temp;
				swaps  	= 1; // a swap has occurred
			}
		}
	}
	usleep(500);			// put thread to sleep in order to save CPU cycles
	return arr;
}

int main() {
    pthread_t thread_1, thread_2;         //this is our handle to the pthread
    int *set=malloc(MAXINTS*sizeof(int));

    // create the threads, returns 0 on the successful creation of each thread
    if(pthread_create(&thread_1, NULL, &threadFunction_1, &x_1)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }
    if(pthread_create(&thread_2, NULL, &threadFunction_2, &x_2)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }
    pthread_cancel(thread_1);
    pthread_cancel(thread_2);
    printf("Final: x_1=%d, x_2=%d, y=%d\n",x_1,x_2, y);
    return EXIT_SUCCESS;
}




