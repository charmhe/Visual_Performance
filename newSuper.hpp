//
//  newSuper.hpp
//  cs3340_1
//
//  Created by Charles on 2019-02-05.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef newSuper_hpp
#define newSuper_hpp

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

#endif /* newSuper_hpp */


const int windowW = 1000;
const int windowH = 1000;
const int up = 950;
const int low = 50;
const int delta = up - low;

std::vector<double> result;
double smallest = 1000000000;
double largest = -1;
double average = -1;
int step;
int sam_num;

void OnDisplay();
void OnKeyboard(unsigned char key, int x, int y);
void Draw();
void k_draw(std::vector<double> result, int sample_num);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void MixedSort(int arr[], int l, int r, int k);
void InsertSort(int arr[], int n);
int* array_generator(int size, int print);


unsigned char frame[windowW * windowH * 3];
void Bresenham( int x1,  int y1,  int x2,  int y2,unsigned char r, unsigned char g, unsigned char b);
void array_reporter(int* D, int size, std::string choice);

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


void OnDisplay() {
    memset(frame, 255, windowW * windowH * 3);
    k_draw(result, sam_num);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(windowW, windowH, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte*)frame);
    glutSwapBuffers();
    glFlush();
}

//test for Merge_sort(A,p,r) and Insert_sort
double test(std::string choice, int size){
    UP = MAX = size;
    //Make array C, reversely sorted integers, choose print it or not
    int *C = array_generator(size,0);//0 means don't print out

    //timer
    clock_t t1 = clock();

    if(choice == "asn1_b")mergeSort(C, 0, MAX-1);
    else if(choice == "asn1_a")InsertSort(C,MAX-1);
    else exit(1);

    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    //std::cout << "\nMerge Sort:"<< time <<"ms"<< std::endl;

    //array_reporter(C,size,choice);
    free(C);
    return time;
}

//test only for Mixed Sort
double test(int size, int k){
    UP = MAX = size;
    //Make array C, reversely sorted integers
    int *C = array_generator(size,0);//0 means don't print out

    //timer
    clock_t t1 = clock();
    MixedSort(C, 0, MAX-1, k);
    //timer
    double time = (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000;
    //std::cout << "\nMixed Sort:"<< time <<"ms"<< std::endl;

    //array_reporter(C,size,choice);
    free(C);
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

//Make array C, reversely sorted integers. print = 1: print the array
int* array_generator(int size, int print){
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
