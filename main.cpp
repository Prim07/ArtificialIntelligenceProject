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
#include <float.h>  //double max size


void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;

//Bent Cigar Functions from Basic Section
//pomocnicza funkcja, na której będziemy testować
double bent_cigar_basic(double*, const int);
double sum_of_diff_pow(double*, const int);


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

    srand(time(NULL));

    //1 - bent cigar
    //3 - zakharov
    //4 - rosenbrock
    //5 - rastrigin
    int func_nums[4] = { 1, 3, 4, 5 };

	for (i = 0; i < 4; i++)
	{
//        printf("function number %d\n", i+1);
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
		for (j = 0; j < n; j++)
        {
            x[n+j]=(rand()%10001)/100.0;
        }
        for (k = 0; k < 1; k++)
        {
            cec17_test_func(x, f, n,m,func_num);
            for (j = 0; j < 2; j++)
            {
                //printf(" f%d(x[%d]) = %f,",func_num,j+1,f[j]);
            }
            printf("\n");
        }
	}




    //=========================================================
    // Black Hole Algorithm
    //=========================================================
    double GLOBAL_BEST = 0.0;

    //Initialize a population
    for (int iter = 0; iter < 1; iter++) {
        int itMax = 0;
        int population = 20;
        Star **arrOfStars = new Star *[population];

        for (int i = 0; i < population; i++) {
            arrOfStars[i] = new Star(n);
        }

        Star *Black_Hole = NULL;
//        std::cout << "\n\n=============================================\n\n";

        for (int k = 0; k < itMax; k++) {

            double local_best = DBL_MAX;
            //obliczanie wartości funkcji
            for (int i = 0; i < population; i++) {
                double *pos = arrOfStars[i]->GetPosition();
//                double val = sum_of_diff_pow(pos, n);
                double val = bent_cigar_basic(pos, n);
                arrOfStars[i]->SetFunctionValue(val);
            }

            //szukanie najlepszej wartości
            for (int i = 0; i < population; i++) {
                if (arrOfStars[i]->GetFunctionValue() < local_best) {
                    local_best = arrOfStars[i]->GetFunctionValue();
                    Black_Hole = arrOfStars[i];
                }
            }

            //zmiana położenia gwiazd
            for (int i = 0; i < population; i++) {
                if (arrOfStars[i] != Black_Hole) {
                    double *old_pos = arrOfStars[i]->GetPosition();
                    double *new_pos = new double[n];
                    double *black_hole_pos = Black_Hole->GetPosition();
                    double _rand = rand() % 1001 / 1000.0;
                    for (int j = 0; j < n; j++) {
                        new_pos[j] = old_pos[j] + _rand * (black_hole_pos[j] - old_pos[j]);
                    }
                    arrOfStars[i]->SetPosition(new_pos);
                }
            }

            //szukanie nowej czarnej dziury
            for (int i = 0; i < population; i++) {
                //liczenie wartości
                if (arrOfStars[i] != Black_Hole) {
                    double *pos = arrOfStars[i]->GetPosition();
//                    double val = sum_of_diff_pow(pos, n);
                    double val = bent_cigar_basic(pos, n);
                    arrOfStars[i]->SetFunctionValue(val);

                    //sprawdzenie, czy lepsze od czarnej dziury
                    double current_val = arrOfStars[i]->GetFunctionValue();
                    double black_hole_val = Black_Hole->GetFunctionValue();
                    //podmiana na nową czarną dziurę
                    if (current_val < black_hole_val) {
//                    double* tmp_pos = arrOfStars[i]->GetPosition();
//                    arrOfStars[i]->SetPosition(Black_Hole->GetPosition());
//                    Black_Hole->SetPosition(tmp_pos);
                        Black_Hole = arrOfStars[i];
                    }
                }
            }

            //sprawdzenie, które gwiazdy przekroczyły horyzont zdarzeń
            //te zabijamy i kreujemy nowe w ich miejsce
            //  1. liczenie R
            double nom = Black_Hole->GetFunctionValue();
            double denom = 0.0;
            for (int i = 0; i < population; i++) {
                if (arrOfStars[i] != Black_Hole) {
                    denom += arrOfStars[i]->GetFunctionValue();
                }
            }
            double R = nom / denom;
            //  2. sprawdzenie
            for (int i = 0; i < population; i++) {
                double distance = 0.0;
                for (int j = 0; j < n; j++) {
                    distance += pow(arrOfStars[i]->GetPosition(j) - Black_Hole->GetPosition(j), 2);
                }
                distance = sqrt(distance);
                if (arrOfStars[i] != Black_Hole && distance < R) {
                    delete arrOfStars[i];
                    arrOfStars[i] = new Star(n);
                }
            }

//        std::cout << "=============================================\n\n";
        }

        double global_best = DBL_MAX;
        //szukanie ostatni raz najlepszej wartości
        //najpierw ponowne ustawienie
        for (int i = 0; i < population; i++) {
            double *curr_pos = arrOfStars[i]->GetPosition();
//            double curr_val = sum_of_diff_pow(curr_pos, n);
            double curr_val = bent_cigar_basic(curr_pos, n);
            arrOfStars[i]->SetFunctionValue(curr_val);
        }
        for (int i = 0; i < population; i++) {
//        std::cout << "in f: " << arrOfStars[i]->GetFunctionValue() << std::endl;
            //printf("Pos: %.6lf\n", arrOfStars[i]->GetFunctionValue());
            if (arrOfStars[i]->GetFunctionValue() < global_best) {
                global_best = arrOfStars[i]->GetFunctionValue();
            }
        }

//        std::cout << "Result of algorithm: " << global_best << std::endl;
//        GLOBAL_BEST = (global_best < GLOBAL_BEST) ? global_best : GLOBAL_BEST;
        GLOBAL_BEST += global_best;
        for(int i = 0; i < population; i++)
            delete arrOfStars[i];
        delete [] arrOfStars;
    }
    std::cout << "Average bests: " << GLOBAL_BEST / 30.0 << std::endl;
    // Free memory
	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);

	return 0;
}



//=========================================================

double bent_cigar_basic(double* x, const int D) {
    double sum = 0.0;
    for(int i = 2; i <= D; i++) {
        sum += pow(x[i - 1], 2);
    }
    sum *= 1000000;
    sum += pow(x[0], 2);

    return sum;
}

double sum_of_diff_pow(double* x, const int D) {
    double sum = 0.0;
    for(int i = 1; i <= D; i++) {
        sum += pow(fabs(x[i - 1]), i + 1);
    }
    return sum;
}
