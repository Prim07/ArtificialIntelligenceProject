/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Dec. 12th 2013
*/

#include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "Star.h"


void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int main()
{
	int i,j,k,n,m,func_num;
	double *f,*x;
	FILE *fpt;
	char FileName[255];
	m=2;
	n=10;
	x= (double *) calloc(sizeof(double), m * n);
	f=(double *)malloc(sizeof(double)  *  m);


    //================= populacji
    int itMax = 1;
    int population = 50;

    //1 - bent cigar
    //3 - zakharov
    //4 - rosenbrock
    //5 - rastrigin
    int func_nums[4] = { 1, 3, 4, 5 };

	for (i = 0; i < 4; i++)
	{
        printf("function number %d\n", i+1);
		func_num=func_nums[i];
		sprintf(FileName, "C:/temp/input_data/shift_data_%d.txt", func_num);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
			printf("\n Error: Cannot open input file for reading \n");
		}
		
		if (x==NULL)
			printf("\nError: there is insufficient memory available!\n");
		for(k=0;k<n;k++)
		{
				fscanf(fpt,"%lf",&x[k]);
//				printf("%d: %lf\n",k,x[k]);
		}

		fclose(fpt);

        //====================Losowe zamiast zera
        srand(time(NULL));
		for (j = 0; j < n; j++)
        {
            x[n+j]=(rand()%10001)/100.0;
        }




        for (k = 0; k < 1; k++)
        {
            cec17_test_func(x, f, n,m,func_num);
            for (j = 0; j < 2; j++)
            {
                printf(" f%d(x[%d]) = %f,",func_num,j+1,f[j]);
            }
            printf("\n");
        }

	}
	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);

	return 0;
}


