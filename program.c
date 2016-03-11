#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>

#define N 6 //sets number
#define R 10 //numer of elements in set
#define PROC 70 //all elements

struct sets{
	int array[R];
};

int * search(struct sets *tab, int *setX)
{
    int result[N];
    int i; //pass=0

    for(i=0; i<N; i++)
    {
        result[i]=0;
    }

    for(i=0; i<N; i++)
    {
        int j, k;
        int counter=0;

        for(j=0; j<R; j++)
        {
            for(k=0; k<R; k++)
            {
                if(tab[i].array[j] == setX[k])
                {
                    counter++;
                }
            }

	    //printf("Conuter: %d   - 	i: %d \n", counter,i);

            if(counter == R)
            {
                result[i]=5;
                //the same sets
            }
            else if(counter > 1 && counter < R)
            {
                result[i]=1;
                //
            }
            else if(counter == 0)
            {
                result[i]=2;
                //0
            }
        }
	printf("counter: %d\n", counter);
    }

    return result;
}



int main(int argc, char **argv)
{
	struct sets *tab;
	int *setX,rank=0,p=0,r=0,*obl,i,*d,q=0,*counter;
	int *pointer;

	setX = (int *)malloc(sizeof(int) *R);
	tab = (struct sets *)malloc(sizeof(struct sets)*N);

	MPI_Init(&argc, &argv);
	MPI_Status status;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	r = PROC % p;

	if(r == 0)
	{
		q = PROC/p;
	}
	else
	{
		q = (PROC + p - r) / p;
	}

	if(rank == 0)
	{

                setX[0] = 1;
                setX[1] = 2;
                setX[2] = 3;
                setX[3] = 4;
                setX[4] = 5;
                setX[5] = 6;
                setX[6] = 7;
                setX[7] = 8;
                setX[8] = 9;
                setX[9] = 10;


                tab[0].array[0] = 1;
                tab[0].array[1] = 2;
                tab[0].array[2] = 3;
                tab[0].array[3] = 4;
                tab[0].array[4] = 5;
                tab[0].array[5] = 6;
                tab[0].array[6] = 7;
                tab[0].array[7] = 8;
                tab[0].array[8] = 9;
                tab[0].array[9] = 10;


                tab[1].array[0] = 11;
                tab[1].array[1] = 2;
                tab[1].array[2] = 3;
                tab[1].array[3] = 4;
                tab[1].array[4] = 5;
                tab[1].array[5] = 6;
                tab[1].array[6] = 7;
                tab[1].array[7] = 8;
                tab[1].array[8] = 9;
                tab[1].array[9] = 10;


                tab[2].array[0] = 111;
                tab[2].array[1] = 222;
                tab[2].array[2] = 555;
                tab[2].array[3] = 32;
                tab[2].array[4] = 22;
                tab[2].array[5] = 111;
                tab[2].array[6] = 211;
                tab[2].array[7] = 511;
                tab[2].array[8] = 32;
                tab[2].array[9] = 22;


                tab[3].array[0] = 1;
                tab[3].array[1] = 1;
                tab[3].array[2] = 1;
                tab[3].array[3] = 1;
                tab[3].array[4] = 1;
                tab[3].array[5] = 1;
                tab[3].array[6] = 1;
                tab[3].array[7] = 1;
                tab[3].array[8] = 1;
                tab[3].array[9] = 1;


                tab[4].array[0] = 1;
                tab[4].array[1] = 2;
                tab[4].array[2] = 5;
                tab[4].array[3] = 32;
                tab[4].array[4] = 22;
                tab[4].array[5] = 1;
                tab[4].array[6] = 2;
                tab[4].array[7] = 5;
                tab[4].array[8] = 32;
                tab[4].array[9] = 22;


                tab[5].array[0] = 1;
                tab[5].array[1] = 2;
                tab[5].array[2] = 5;
                tab[5].array[3] = 32;
                tab[5].array[4] = 22;
                tab[5].array[5] = 1;
                tab[5].array[6] = 2;
                tab[5].array[7] = 5;
                tab[5].array[8] = 32;
                tab[5].array[9] = 22;
	}


	obl = calloc(q, sizeof(int));

	clock_t start, finish;
	double duration;
	start = clock();

	//counter = search(tab,setX);
	MPI_Scatter(tab, q, MPI_INT, obl, q, MPI_INT, 0, MPI_COMM_WORLD);
 	counter = search(tab, setX);
	int *dane;
	if(rank == 0)
	{
		printf("Wartosc p: %d\n",p);
		for(i=1; i < p; i++)
		{
			MPI_Recv(dane, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
			printf("Odbieram: %d\n", *(dane+i));
		}

		int k;

		for(k=0; k<N; k++)
		{
			printf("Zwracam counter %d\n", *(counter+k));

			if(*(counter+k) == 5)
			{
				printf("Set number %d is the same \n", k);
			}
			if(*(counter+k) == 1)
			{
				printf("Set number %d have at least one identical \n", k);
			}
			if(*(counter+k) == 2)
			{
				printf("No elements in set number %d \n", k);
			}
		}
	}
	else
	{
		MPI_Send(counter, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	
	
	free(tab);
	free(setX);

	MPI_Finalize();

	return 0;
}


