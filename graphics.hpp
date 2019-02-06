//
//  newSuper.hpp
//  cs3340_1
//
//  Created by Charles on 2019-02-05.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef newSuper_hpp
#define newSuper_hpp


#include <iterator>
#include "graphicLibrary.h"
#include "testAlgo.h"


#define LOW 0   //the random number's lower bound
#define num1 20000
#define num2 200000
#define num3 200000000

int numsize = 9;
int num[9] = {2,20,200,2000,num1,num2,2000000,20000000,num3};
int UP;//the random number's upper bound

#endif /* newSuper_hpp */

double smallest = 1000000000;
double largest = -1;
double average = -1;
int step;
int sam_num;

void k_draw(std::vector<double> result, int sample_num){

    printf("归并平均: %f 混合最大: %f, 混合最小: %f\n",average,largest,smallest);
    double range = largest - smallest;

    //绘制基准线。注意其压缩算法。
    Bresenham(0,low+(average - smallest)/range*delta,drawWidth,low+(average - smallest)/range*delta,218,112,214);//base line: light puple;

    int i = 0;
    int jumpPeriod = drawWidth/sample_num; //这是绘图时候的步进点。比如踩点100个，屏幕宽1000，则按10为单位跳跃。
    printf("屏幕采样跳跃值: %d\n",jumpPeriod);
    for (std::vector<double>::iterator iter = result.begin(); iter != result.end(); iter++){
        Bresenham(i,low+(*iter - smallest)/range*delta,i+jumpPeriod,low+(*(std::next(iter, 1)) - smallest)/range*delta,0,0,0);
        i += jumpPeriod;
    }
}

void super_K(int size,int upper){

    //count the average of Merge;
    if(size <= num[7] && size >= num[0]){
        double *a = (double*)malloc(sizeof(double)*6);
        for(int i = 0; i < 6; i++){
            *(a+i) = test("asn1_b",size,0);
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
    int upper_bound = upper;
    if(upper == 1)upper_bound = size/10;//如果upperbound == 1,  则为size/10的长度
    else if(upper < 1){printf("Warning: SuperK: illegal upperbound\n");exit(1);}
    printf("最大采样限度_upper_bound: %d;\n平均单次采样时间_average: %f ms\n",upper_bound,average);

    int sample_amount = maxTime/average;
    if (sample_amount <= 0)sample_amount = 10000000000;

    printf("在时间允许内可以采样的最大次数_sample_amount:%d;\n受物理限制的采样率_drawWidth: %d\n",sample_amount,drawWidth);

    int sampleNumber = 1000;//采样点的数量。屏幕一般宽为1000. 多于此点无意义。

    sam_num = (sampleNumber>sample_amount ? sample_amount:sampleNumber);//如果数据很少，那么按数据采样；反之不能超过屏幕大小；
    sam_num = (sam_num>upper_bound ? upper_bound:sam_num);//这里要注意，sam_num要比较2次。为什么呢？屏幕大小，时间允许内最大采样率，和尺寸。如果尺寸就1或者2，那搞大了也没意义。

    printf("最终决定的实践的采样点数_sam_num:%d;\n预计时间:%f ms, = %f mins\n",sam_num,sam_num*average,sam_num*average/1000/60);

    step = upper_bound/sam_num; //采样点间的步长. +1 保证不会太小
    if(step == 0)step+=1;

    printf("在最大采样区间内采样的间隔: %d\n",step);


    for(int i = 1; i <= sam_num; i++){
        printf("k: %d\n",i);
        double answer = test_mix(size,i,0);
        if(answer > largest){largest = answer; printf("最大k: %d\n",i);}
        else if(answer < smallest){smallest = answer; printf("最小k: %d\n",i);}

        result.push_back(answer);

        //printf("%d/%d\n",i,sam_num);
    }
}

void super_k(int argc, char **argv, int size,int upperbound){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowW, windowH);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mu He");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    super_K(size,upperbound);

    glutDisplayFunc(OnDisplay);
    glutKeyboardFunc(OnKeyboard);

    //-- run the program
    glutMainLoop();
}

void OnDisplay() {
    memset(frame, 255, windowW * windowH * 3);
    k_draw(result, sam_num);

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(windowW, windowH, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte*)frame);
    glutSwapBuffers();
    glFlush();
}

