//
//  algos.h
//  cs3340_1
//
//  Created by Charles on 2019-02-06.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef algos_h
#define algos_h

#include <time.h> //for time(NULL)
#include <unistd.h> //for getpid()
#include <math.h>
#include <string.h>
#include <iostream>
#include "printer.h"

#endif /* algos_h */

//Merge(A,B,size of A, size of B): merge two sorted array
//分离型Merge算法。
int* Merge(int* A, int*B, int a, int b){
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
    return C;
}

//merge is for mergeSort
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
     are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
     are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//我的算法，他人merge
////Merge sort algorithm ;), array A, start position p and end position
void MergeSort_0(int*A, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort_0(A,p, q);
        MergeSort_0(A,q+1, r);
        merge(A,p,q,r);
    }
}

//他人算法，他人merge
void MergeSort_1(int arr[], int l, int r){
    if (l < r ){
        int m = l+(r-l)/2;
        MergeSort_1(arr, l, m);
        MergeSort_1(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/*
 MixedSort Algorithm, array A, start position p and end position
 ...and k as sub-string's size.
 */
void InsertSort(int*arr, int l);
void MixedSort(int arr[], int l, int r, int k)
{
    if (l < r && r - l > k ){
        int m = l+(r-l)/2;
        MixedSort(arr, l, m, k);
        MixedSort(arr, m+1, r, k);
        merge(arr, l, m+1, r);
    }else if(l < r && r - l < k)InsertSort(arr,r-l);
}

//InsertSort Algorithm, array A, start position p and end position
void InsertSort_inC(int A[], int p, int r){
    for (int i = p+1; i < r; i++) {
        for (int j = i; j > 0 && A[j - 1] > A[j]; j--) {
            int tmp = A[j];
            A[j] = A[j - 1];
            A[j - 1] = tmp;
        }
    }
}

void InsertSort(int*arr, int l) {

    std::vector<int> array(arr,arr+l);
//    std::cout<<"头 "<<array[0]  <<std::endl;
//    std::cout<<"size: "<<array.size()  <<std::endl;
    for (auto it = array.begin(), end = array.end(); it != end; ++it) {
        std::rotate(std::upper_bound(array.begin(), it, *it), it, it + 1);
    }
    memcpy(arr,array.data(),l-1);
    //for(int i = 0; i<q-p; i++)std::cout<<"头"<<i<<array[p+i]  <<std::endl;
}
