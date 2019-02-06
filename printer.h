//
//  printer.h
//  cs3340_1
//
//  Created by Charles on 2019-02-06.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef printer_h
#define printer_h

#include <stdlib.h>
#include <stdio.h>

#endif /* printer_h */

//Make array C, reversely sorted integers. print = 1: print the array
int* array_generator(int size, int printON){
    int *C = (int*)malloc(sizeof(int)*size);
    if(size < 20)C = (int*)malloc(sizeof(int)*20);
    //avoiding size < 20 and have run code.
    for(int j = 0; j < 20; j++)*(C+j) = 0;

    C[0] = size;

    for(int i = 1; i < size; i++){
        //*(C+i) = LOW + rand() % (UP - LOW);
        C[i] = C[i-1] - rand()%(3);
    }

    if(printON == 1){
        printf("Reverse Array generated - 20/Size %d\n",size);
        //Asked to print first 20 num
        for(int i = 0; i < 20; i++){
            printf("        %d\n",*(C+i));
        }
    }
    return C;
}

void array_reporter(int* D, int size, std::string choice){
    if(choice=="asn1_b")printf("\nMerge Sort Output - 20/Size:%d\n",size);
    else if(choice=="asn1_a") printf("Insert Sort Output - 20/Size:%d\n",size);
    else if(choice=="asn1_c") printf("Mixed Sort Output - 20/Size:%d\n",size);
    else printf("Error: array_reporter: wrong name;");

    //if size < 20, D may have unexpected entries. Avioid it.
    if(size < 20)
        for(int i = size; i < 20; i++)
            D[i] = 0;

    //Print first 20 answers
    for(int i = 0; i < 20; i++){
        printf("        %d\n",*(D+i));
    }
}
