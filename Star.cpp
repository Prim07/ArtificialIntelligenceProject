//
// Created by LENOVO on 2017-05-12.
//

#include "Star.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

Star::Star() {

    position= (double *) calloc(sizeof(double), 20);
    srand(time(NULL));
    for (int i = 0; i <10; i++) {
        position[10+i] = (rand()%10001)/100.0;
    }
}
