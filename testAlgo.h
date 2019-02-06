//
//  testAlgo.h
//  cs3340_1
//
//  Created by Charles on 2019-02-06.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef testAlgo_h
#include <vector>
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
    //std::cout << "Mixed Sort: "<< time <<"ms    /"<<size<< std::endl;

    if(printON == 1)array_reporter(C,size,"asn1_c");
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
    clock_t t1, t2;
    t1 = t2 = clock();
    if(choice == "asn1_b"){MergeSort_1(A, 0, size);}
    else if(choice == "asn1_bb"){//多个b算法大比较；
        MergeSort_0(A, 0, size-1);

        t2 = clock();
        MergeSort_1(A, 0, size-1);

    }
    else if(choice == "asn1_a")InsertSort(A,size);
    else if(choice == "asn1_aa"){
        InsertSort(A,size);//多个a算法大比较；
        t2 = clock();
        InsertSort_inC(A, 0, size);
    }
    else {
        printf("Warning: test: No case matched;\n");
        exit(1);
    }
    
    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    double time2 = (clock() - t2) * 1.0 / CLOCKS_PER_SEC * 1000;

    if((t1 - t2) > 0.001 || (t2 - t1) > 0.001 )time = time - time2;

    std::string r;
    if(choice == "asn1_b")r = "Merge Sort: ";
    else if(choice == "asn1_a")r = "InsertSort: ";
    else if(choice == "asn1_bb")r = "MergeSort_1:";
    else if(choice == "asn1_aa")r = "Insert in C++: ";
    std::cout.flags(std::ios::fixed);
    std::cout << r << time <<"ms    /size:"<<size<< std::endl;

    if(r == "MergeSort_1:"){
        r = "MergeSort_2:";
        std::cout << r << time2 <<"ms    /size:"<<size<< std::endl;
    }
    if(r == "Insert in C++: "){
        r = "Insert in  C : ";
        std::cout << r << time2 <<"ms    /size:"<<size<< std::endl;
    }

    if(printON == 1)array_reporter(A,size,choice);

    return (double)time;
}


void test_A(int size, int printON){
    test("asn1_a",size,printON);
}

void test_B(int size, int printON){
    test("asn1_b",size,printON);
}

void test_BB(int size, int printON){
    test("asn1_bb",size,printON);
}

void test_AA(int size,int printON){
    test("asn1_aa",size,printON);
}
