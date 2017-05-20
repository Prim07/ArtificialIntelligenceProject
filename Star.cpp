//
// Created by LENOVO on 2017-05-12.
//

#include "Star.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

Star::Star(const int D) {
//    std::cout << "Creating new star: \n";
    position = (double *) calloc(sizeof(double), /*20*/ D);
    for (int i = 0; i < D; i++) {
        position[/*D +*/ i] = (rand() % 10001) / 50.0 - 100.0;
//        std::cout << i << ": " << position[i] << std::endl;
    }
//    std::cout << std::endl;
}
