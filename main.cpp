//
//  main.cpp
//  cs3340_1
//
//  Created by Charles on 2019-02-04.
//  Copyright © 2019 Mu He. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

#define LOW 0   //the random number's lower bound
#define num1 20000
#define num2 200000
#define num3 200000000

int MAX;
int num[9] = {2,20,200,2000,num1,num2,2000000,200000000,num3};
int UP;//the random number's upper bound

using namespace std;

void PrintArray(int *array, int n) {
    for (int i = 0; i < n; ++i)
        std::cout << array[i] << " " << std::flush;
    std::cout << std::endl;
}

void InsertionSort(int arr[], int arr_size){
    if(arr_size > 1){
        int size = arr_size;
        for(int i = 1; i < size; ++i){
            int j = i - 1;
            int key = arr[i];
            while(j >= 0 && arr[j] > key){
                arr[j+1] = arr[j];
                --j;
            }
            arr[j+1] = key;
        }
    }
}

void insertion_sort(std::vector<int>& array) {
    for (auto it = array.begin(), end = array.end(); it != end; ++it) {
        std::rotate(std::upper_bound(array.begin(), it, *it), it, it + 1);
    }
}

int main(int argc, const char * argv[]) {
    for(int i = 0;i < 9;i++){
        cout<< i <<"\t";
        vector <int> a;
        for(int j = num[i]; j > 0;j--){
            a.push_back(j);
        }

        clock_t t1 = clock();
        insertion_sort(a);
        cout << "时长：" << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 <<"毫秒"<< endl;

//        vector<int>::iterator iter = a.begin();
//        cout<< i <<"\t";
//        while (iter != a.end())
//        {
//            cout << *iter << "\t";
//            iter++;
//        }
    }
    return 0;
}

