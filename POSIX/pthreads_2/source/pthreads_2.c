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

#define	MAXINTS		5 // maximum number of integers that user may enter

/*
 * global variables and constants
 */
int		num_ints=0;		// current number of integers entered by user
int		done=0;			// flag indicating completion of user data entry
float	average=0.0;	// global storage for average

/*
 * function to display the set of numbers periodically
 */
void	disp_sorted(int *data)
{
	if (num_ints != 0)
	{
		if ((num_ints % 1)==0) // display the set every 10 integers
		{
			printf("the current (sorted) integer set is: ");
			for (int i=0; i!=num_ints; ++i)
			{
				printf("%d ", data[i]);
			}
			printf("\n");
		}
	}
	return;              	// return the pointer to x
}

/*
 * thread function to display the average of the set of numbers periodically
 */
//void 	*disp_avg_thread()
//{
//	if ((num_ints % 4)==0) // display the average every 4 integers
//	{
//		printf("the current average is: %f \n", average);
//	}
//	usleep(3000);		// put thread to sleep in order to save CPU cycles
//	return NULL;
//}


/*
 * thread function computes average of current set
 */
//void	*avg_thread(void *arr)
//{
//	int 	*x = (int *) arr;	// cast the passed data to integer type
//	int		sum=0;
//	for (int i=0; i!=num_ints; ++i)
//	{
//		sum += x[i];
//	}
//	if (num_ints !=0)
//	{
//		average = (float) (sum/num_ints);
//	}
//	usleep(500); 	// put thread to sleep in order to save CPU cycles
//	return x;
//}

/*
 * thread function sorts data set in its current set
 */
void	*bubb_sort_thread(void *arr)
{
	int 	*x = (int *) arr;	// cast the passed data to integer type
	int 	swaps; 				// a flag indicating if a swap has occurred (if none occur, this set is sorted)
	int		temp;

	//while (num_ints != MAXINTS)
	while (done==0)
	{
		if (num_ints != 0)
		{
			swaps = 1;
			while (swaps==1)
			{
				swaps = 0; // if a swap occurs, this flag toggled
				for (int i=0; i!=(num_ints-1); ++i)
				{
					if (x[i] > x[i+1]) // elements must be in ascending order, if not ...
					{	// ... then swap!
						temp 	= x[i];
						x[i] 	= x[i+1];
						x[i+1] 	= temp;
						swaps  	= 1; // a swap has occurred
					}
				}
			}
		}
		//usleep(50);			// put thread to sleep in order to save CPU cycles
	}
	return x;
}

int main()
{
    pthread_t 	thread_calc_2;	// this is our handle to the pthread
    int 		set[MAXINTS]; 	//  storage for our numbers

    // initialize set to zero
    for (int i=0; i != MAXINTS; ++i)
    {
    	set[i]=0;
    }

    // create the threads, returns 0 on the successful creation of each thread
//    if(pthread_create(&thread_disp_1, NULL, &disp_nums_thread, set)!=0)
//    {
//    	printf("Failed to create the thread\n");
//    	return 1;
//    }

//    if(pthread_create(&thread_disp_2, NULL, &disp_avg_thread, NULL)!=0)
//    {
//    	printf("Failed to create the thread\n");
//    	return 1;
//    }
//    if(pthread_create(&thread_calc_1, NULL, &avg_thread, set)!=0)
//    {
//    	printf("Failed to create the thread\n");
//    	return 1;
//    }

    if(pthread_create(&thread_calc_2, NULL, &bubb_sort_thread, (void *)set)!=0)
    {
    	printf("Failed to create the thread\n");
    	return 1;
    }

    int 	user_int;
    printf("Please enter some positive integers... thanks\n");
    while (num_ints != MAXINTS)
    {
    	scanf("%d", &user_int);
    	set[num_ints]=user_int;
    	++num_ints;
    	usleep(2000); // encourage pthreads to run
    	disp_sorted(set);
    	printf("num_ints=%d\n",num_ints);
    }
    done=1; // user has finished entering data
//    pthread_cancel(thread_calc_1);
//    pthread_cancel(thread_calc_2);
//    pthread_cancel(thread_disp_1);
//    pthread_cancel(thread_disp_2);
    void *result;
    pthread_join(thread_calc_2, &result);
    disp_sorted((int *)result);
    return 0;
}




