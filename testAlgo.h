//
//  testAlgo.h
//  cs3340_1
//
//  Created by Charles on 2019-02-06.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef testAlgo_h

#include <iostream>
#include <string>
#include "algos.h"
#define testAlgo_h
#endif /* testAlgo_h */

//test only for Mixed Sort
double test_mix(int size, int k, int printON){
    //std::cout<<"k: "<<k<<std::endl;
    if(printON != 1 && printON != 0){
        printf("printON: %d; Warning: test_mix: printON illegal\n",printON);
        exit(1);
    }
    //Make array C, reversely sorted integers
    int *C = array_generator(size,printON);//printON = 0 means don't print out

    //timer
    clock_t t1 = clock();
    MixedSort(C, 0, size, k);
    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    std::cout << "\nMixed Sort:"<< time <<"ms"<< std::endl;

    if(printON == 1)array_reporter(C,size,"asn1_c");
    free(C);
    return time;
}

//test for Merge_sort(A,p,r) and Insert_sort
double test(std::string choice, int size, int printON){
    if(printON != 1 && printON != 0){
        printf("printON: %d; Warning: test: printON illegal\n", printON);
        exit(1);
    }
    //Make array C, reversely sorted integers, choose print it or not
    int *A = array_generator(size,printON);//printON = 0 means don't print out

    //timer
    clock_t t1 = clock();

    if(choice == "asn1_b"){MergeSort(A, 0, size-1);}
    else if(choice == "asn1_a")InsertSort(A,0,size);
    else {
        printf("Warning: test: No case matched;\n");
        exit(1);

    }
    
    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    std::cout << "\nMerge Sort:"<< time <<"ms"<< std::endl;

    if(printON == 1)array_reporter(A,size,choice);

    free(A);
    return (double)time;
}


void test_A(int size, int printON){
    test("asn1_a",size,printON);
}

void test_B(int size, int printON){
    test("asn1_b",size,printON);
}
