/* 
 *
 * @Author Charles He
 * 
 * CLRS 1.3 Merge(A,p,q,r), p15, for Divide-and-Conqur Algo.
 * CLRS 1.1 Insert(A,p,q)
 * 
 * @2018-12-01, 6:30 A.M.
 * editted at 2019/2/4
 * 
 */
#include <vector>
#include <algorithm>
#include <iterator>
#include <time.h> //for time(NULL)
#include <unistd.h> //for getpid()
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <math.h>
#include <iostream>
#define LOW 0   //the random number's lower bound
#define num1 20000
#define num2 200000
#define num3 200000000

int MAX;
int numsize = 9;
int num[9] = {2,20,200,2000,num1,num2,2000000,20000000,num3};
int UP;//the random number's upper bound
 
/* 
 * The use of Random
 * #include <time.h> //for time(NULL)
 * #include <unistd.h> //for getpid()
 * srand(time(NULL)-getpid());
 * 
 * The algo of Making an random unsorted array:
 * A[i] = LOW + rand()%(UP - LOW);
 *
 * Making an random sorted array:
 * A[0] = int;
 * A[i] = A[i-1] + rand()%(UP - LOW);
 * 
 */

const int windowW = 1000;
const int windowH = 1000;
const int up = 950;
const int low = 50;
const int delta = up - low;

void OnDisplay();
void OnKeyboard(unsigned char key, int x, int y);
void Draw();

unsigned char frame[windowW * windowH * 3];
void Bresenham( int x1,  int y1,  int x2,  int y2,unsigned char r, unsigned char g, unsigned char b);

void OnKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
    }
}

void DrawPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= windowW || y >= windowH)
        return;

    unsigned int index = 3 * (y * windowW + x);
    frame[index] = r;
    frame[index + 1] = g;
    frame[index + 2] = b;
}

/*
 * Draw a line by Bresenham's algorithm.
 *
 * @author Mu He
 *
 */

void Bresenham( int x1,  int y1,  int x2,  int y2, unsigned char r, unsigned char g, unsigned char b) {

    // To remark end points as red.
    //    DrawPixel(x1,y1,255,0,0);
    //    DrawPixel(x1+1,y1,255,0,0);
    //    DrawPixel(x1,y1+1,255,0,0);
    //    DrawPixel(x1+1,y1+1,255,0,0);
    //
    //    DrawPixel(x2,y2,255,0,0);
    //    DrawPixel(x2+1,y2,255,0,0);
    //    DrawPixel(x2,y2+1,255,0,0);
    //    DrawPixel(x2+1,y2+1,255,0,0);

    int dx  = x2 - x1,
    dy  = y2 - y1,
    y   = y1,
    epsilon = 0; // epsilon as error.

    /*
     * As we know, a Bresenham's Algo must work together for 8 octants. Starts from 12 o' clock, I named the first
     * octants as #1, then #2; the 3'o clock's as #3, #4, lastly end with #8.
     *
     * Obviously, Case 2 and Case 1 is the basis of all cases. Case 2 could generate #3, #7, #6 and Case 1 do the rest.
     *
     * Case 2, I learn from class note, and I do the rest all by myself.
     */

    /* First four groups: based on Case 2 */

    if(0 <= dy && dy <= dx){ // 0 < m < 1, case 2
        //std::cout << "case 2" << std::endl;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  { //Some little optimization, avoiding division with left-shift.
                y++;  epsilon -= dx;
            }
        }
    }

    if(dy >=0 && dy <= -dx){ // 0 > m > -1, case 7

        // Case 7 is mirror of 2, around y-axis.  So change For Loop's order, and dx, dy into abs.

        //std::cout << "case 7" << std::endl;
        dx = -dx;
        for(int x = x1; x >= x2; x-=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y++;  epsilon -= dx;
            }
        }
    }

    else if(dy <= 0 && -dy <= dx){ // -1 < m < 0, case 3

        // 3 is mirror of 2, around x-axis. So y++ => y--, and dx, dy into abs.

        //std::cout << "case 3" << std::endl;
        dy = -dy;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y--;  epsilon -= dx;
            }
        }
    }

    //Another version of case 3 is regard it as case 7's reverse. So exchange the end points.
    //Bresenham(x2,y2, x1, y1);

    else if(dy <= 0 && dx <= dy){ // -1 < m < 0, case 6
        //case 6 is just a reverse of case 2. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }


    /* Another four groups: based on Case 1
     *
     * The design idea of Case 1 is, it's a mirror around line y = x.
     *
     * So simply exchange x,y, and all is done.
     * However, just call Bre(y1,x1,y2,x2) won't work for it.
     */

    else if(0 <= dx && dx <= dy){ // m > 1, case 1

        //Case 1 is case 2's sibling: Change every x and y, but don't change Draw(x,y).

        //std::cout << "case 1" << std::endl;

        int x = x1;
        for(int y = y1; y <= y2; y+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dx;
            if ( (epsilon << 1) >= dy )  {
                x++;  epsilon -= dy;
            }
        }
    }

    else if(dx <= 0 && -dx <= dy){ // m < -1, case 8

        //Case 8 is case 1's mirror around y-axis. Simply change the order of for loop; Abs dx, dy; and x = x1 => x = x2;

        //std::cout << "case 8" << std::endl;

        dx = -dx;
        int x = x2;
        for(int y = y2; y >= y1; y-=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dx;
            if ( (epsilon << 1) >= dy )  {
                x++;  epsilon -= dy;
            }
        }
    }

    else if(dx <= 0 && dy <= dx){ // m < -1, case 5
        //case 5 is just a reverse of case 1. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }

    else if(0 <= dx && dy <= -dx){ // m < -1, case 4
        //case 4 is just a reverse of case 8. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }
}


void Draw() {
    float dt = 2.0*M_PI/200.0 ;
    for (float t = 0.0 ; t < 2.0*M_PI;) {
        float x1 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
        float y1 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
        t += dt ;
        float x2 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t)) ;
        float y2 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t)) ;
        Bresenham(x1,y1,x2,y2,0,0,0) ;
    }
}

 

//Merge(A,B,size of A, size of B): merge two sorted array
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

//Merge sort algorithm ;), array A, start position p and end position
int* Merge_sort(int* A, int p, int r){
    if(p<r){
        int q = (p+r)/2;
        int*B = Merge_sort(A, p, q);
        int*C = Merge_sort(A, q+1, r);
        return Merge(B,C,q-p+1,r-q);
    }else return A+p;
}

//InsertSort Algorithm, array A, start position p and end position
int* InsertSort(int *A, int p, int r){
    for (int i = p+1; i < r+1; i++) {
        for (int j = i; j > 0 && A[j - 1] > A[j]; j--) {
            int tmp = A[j];
            A[j] = A[j - 1];
            A[j - 1] = tmp;
        }
    }
    return A;
}


//MixedSort Algorithm, array A, start position p and end position
//...and k as sub-string's size.
int* MixedSort(int* A, int p, int r, int k){
    if(r-p < k)return InsertSort(A,p,r);
    if(p<r){
        int q = (p+r)/2;
        int*B = Merge_sort(A, p, q);
        int*C = Merge_sort(A, q+1, r);
        return Merge(B,C,q-p+1,r-q);
    }else return A+p;
}

//Make array C, reversely sorted integers. print = 1: print the array
int* rarray_generator(int size, int print){
    int *C = (int*)malloc(sizeof(int)*size);
    if(size<20)C = (int*)malloc(sizeof(int)*100);
    //avoiding size < 20
    for(int j = 0; j < 20; j++)*(C+j) = 0;

    C[0] = size;
    
    for(int i = 1; i < MAX; i++){
        //*(C+i) = LOW + rand() % (UP - LOW);
        C[i] = C[i-1] - rand()%(3);
    }
    
    if(print == 1){
        printf("Reverse Array generated - 20/Size %d\n",size);
        //Asked to print first 20 num
        for(int i = 0; i < 20; i++){
            printf("        %d\n",*(C+i));
        }
    }

    return C;
}

void array_reporter(int* D, int size, std::string choice){
    if(choice=="asn1_b")printf("\nMerge Sort Output - 20/Size:%d\n",MAX);
    else if(choice=="asn1_a") printf("Insert Sort Output - 20/Size:%d\n",MAX);
    else if(choice=="asn1_c") printf("Mixed Sort Output - 20/Size:%d\n",MAX);

    //if size < 20, D may have unexpected entries. Avioid it.
    if(size < 20)
        for(int i = size; i < 20; i++)
            D[i] = 0;

    //Print first 20 answers
    for(int i = 0; i < 20; i++){
        printf("        %d\n",*(D+i));
    }
}

//test for Merge_sort(A,p,r) and Insert_sort
double test(std::string choice, int size){
    UP = MAX = size;
    //Make array C, reversely sorted integers, choose print it or not
    int *C = rarray_generator(size,0);//0 means don't print out

    int*D;

    //timer
    clock_t t1 = clock();

    if(choice == "asn1_b")D = Merge_sort(C, 0, MAX-1);
    else if(choice == "asn1_a")D = InsertSort(C,0,MAX-1);
    else exit(1);
    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    //std::cout << "\nMerge Sort:"<< time <<"ms"<< std::endl;

    //array_reporter(D,size,choice);
    
    return time;
}

//test only for Mixed Sort
double test(int size, int k){
    UP = MAX = size;
    //Make array C, reversely sorted integers 
    int *C = rarray_generator(size,0);//0 means don't print out

    //timer
    clock_t t1 = clock();
    int*D = MixedSort(C, 0, MAX-1, k);

    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    //std::cout << "\nMixed Sort:"<< time <<"ms"<< std::endl;

    //array_reporter(D,size,choice);
    
    return time;
}

void seperate(int argc, char **argv){
    //To generate a random number;
    srand(time(NULL)-getpid());
    //To convert input arguments
    int size = std::stoi(argv[1]); std::string choice(argv[0]);
    
    if(argc == 2 && choice.substr(2) != "asn1_c")test(choice.substr(2), size);
    else if(argc == 3 && choice.substr(2) == "asn1_c"){
        int k = std::stoi(argv[2]);
        if (k > 0 && k <= size)test(size, k);
        else exit(1);
    }
    else exit(1);
}

void k_draw(std::vector<double> result, double average, int step);

std::vector<double> result;
double smallest = 1000000000;
double largest = -1;
double average = -1;
int step;
int sam_num;

void super_K(int size){
    //count the average of Merge;
    if(size <= num[7] && size >= num[0]){
        double *a = (double*)malloc(sizeof(double)*6);
        for(int i = 0; i < 6; i++){
            *(a+i) = test("asn1_b",size);
        }
        average = (a[0]+a[1]+a[2]+a[3]+a[4]+a[5])/6;
    }
    else if(size == num[8]) average = test("asn1_b",size);

    else {
        printf("\nSize too large!\n");
        exit(1);
    }

    int maxTime = 600000;//等待不超过600000ms, 十分钟
    int upper_bound = size/10;//不考虑采样的点的上限
    printf("最大采样限度: %d;\n平均单次采样时间: %f ms\n",upper_bound,average);

    int sample_amount = maxTime/average;
    if (sample_amount <= 0)sample_amount = 10000000000;

    printf("在时间允许内可以采样的最大规模:%d;\n受物理限制的采样率: %d",sample_amount,windowW);

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

void OnDisplay() {
    memset(frame, 255, windowW * windowH * 3);
    k_draw(result, sam_num);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(windowW, windowH, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte*)frame);
    glutSwapBuffers();
    glFlush();
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

