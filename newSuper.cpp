/*
 *
 * @Author Mu He, 250995508
 *
 * CLRS 1.3 Merge(A,p,q,r), p15, for Divide-and-Conqur Algo.
 * CLRS 1.1 Insert(A,p,q)
 *
 * @2018-12-01, 6:30 A.M.
 * editted at 2019/2/4
 *
 */

//Merge(A,B,size of A, size of B): merge two sorted array

#include "newSuper.hpp"

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
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

/* l is for left index and r is right index of the
 sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
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

void MixedSort(int arr[], int l, int r, int k){
    if (l < r && r - l > k){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
    else if (l < r && r - l < k){
        InsertSort(arr,r);
    }
}

void k_draw(std::vector<double> result, double average, int step);

void super_K(int size){
    //count the average of Merge;
    if(size <= num[7] && size >= num[0]){
        double *a = (double*)malloc(sizeof(double)*6);
        for(int i = 0; i < 6; i++){
            *(a+i) = test("asn1_b",size);
        }
        average = (a[0]+a[1]+a[2]+a[3]+a[4]+a[5])/6;
        free(a);
    }
    //else if(size == num[8]) average = test("asn1_b",size);

    else {
        printf("\nSize too large!\n");
        exit(1);
    }

    int maxTime = 600000;//等待不超过600000ms, 十分钟
    int upper_bound = size/10;//不考虑采样的点的上限
    printf("最大采样限度: %d;\n平均单次采样时间: %f ms\n",upper_bound,average);

    int sample_amount = maxTime/average;
    if (sample_amount <= 0)sample_amount = 10000000000;

    printf("在时间允许内可以采样的最大规模:%d;\n受物理限制的采样率: %d\n",sample_amount,windowW);

    int sampleNumber = 1000;//采样点的数量。屏幕一般宽为1000. 多于此点无意义。

    sam_num = (sampleNumber>sample_amount ? sample_amount:sampleNumber);//如果数据很少，那么按数据采样；反之不能超过屏幕大小；
    printf("最终决定的实践的采样点数:%d;\n预计时间:%f ms, = %f mins\n",sam_num,sam_num*average,sam_num*average/1000/60);

    step = upper_bound/sam_num + 1; //采样点间的步长. +1 保证不会太小

    printf("在最大采样区间内采样的间隔: %d\n",step);


    for(int i = 1; i <= sam_num; i++){
        double answer = test(size,i);
        if(answer > largest)largest = answer;
        else if(answer < smallest)smallest = answer;
        result.push_back(answer);
        //printf("%d/%d\n",i,sam_num);
    }
}

void k_draw(std::vector<double> result, int sample_num){

    printf("归并平均: %f 混合最大: %f, 混合最小: %f\n",average,largest,smallest);
    double range = largest - smallest;

    //绘制基准线。注意其压缩算法。
    Bresenham(0,low+(average - smallest)/range*delta,windowW,low+(average - smallest)/range*delta,218,112,214);//base line: light puple;

    int i = 0;
    int jumpPeriod = windowW/sample_num; //这是绘图时候的步进点。比如踩点100个，屏幕宽1000，则按10为单位跳跃。
    printf("屏幕采样跳跃值: %d\n",jumpPeriod);
    for (std::vector<double>::iterator iter = result.begin(); iter != result.end(); iter++){
        Bresenham(i,low+(*iter - smallest)/range*delta,i+jumpPeriod,low+(*(std::next(iter, 1)) - smallest)/range*delta,0,0,0);
        i += jumpPeriod;
    }
}

//main
int main(int argc, char **argv){
    //seperate(argc,argv);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mu He");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    super_K(num[6]);

    glutDisplayFunc(OnDisplay);
    glutKeyboardFunc(OnKeyboard);

    //-- run the program
    glutMainLoop();
    return 0;
}

