//
//  algorithm.h
//  cs3340_1
//
//  Created by Charles on 2019-02-06.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef algorithm_h
#define algorithm_h
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <time.h> //for time(NULL)
#include <unistd.h> //for getpid()
#include <math.h>


#endif /* algorithm_h */

//Merge(A,B,size of A, size of B): merge two sorted array
void Merge(int* A, int*B, int a, int b){
    int i = 0, j = 0; //cursor for sub array A[0,a) and B[0.b)
    int k = 0;//cursor for C[0,a+b];
    int* C = (int*)malloc(sizeof(int)*(a+b));
    while(i!=a && j!=b){
        if(*(A+i) > *(B+j))
            *(C+k++) = *(B+j++);
        else
            *(C+k++) = *(A+i++);
    }
    while(j!=b)*(C+k++)=*(B+j++);
    while(i!=a)*(C+k++)=*(A+i++);
}

//Merge sort algorithm ;), array A, start position p and end position
void MergeSort(int* A, int p, int r){
    if(p<r){
        int q = (p+r)/2;
        MergeSort(A, p, q);
        MergeSort(A, q+1, r);
        Merge(A+p,A+q+1,q-p+1,r-q);
    }else ;
}

void InsertSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i-1;
        /* Move elements of arr[0..i-1], that are
         greater than key, to one position ahead
         of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

//MixedSort Algorithm, array A, start position p and end position
//...and k as sub-string's size.
void MixedSort(int* A, int p, int r, int k){
    if(p < r && r - p > k ){
        int q = (p+r)/2;
        MergeSort(A, p, q);
        MergeSort(A, q+1, r);
        Merge(A+p,A+q+1,q-p+1,r-q);
    }else if(p < r && r - p < k)InsertSort(A,r);
}
