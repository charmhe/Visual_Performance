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

#include "graphics.hpp"

//used to compare merge's performance
void compare2merge(int size, int printON){
    test_BB(size, printON);
}

void compare2insert(int size, int printON){
    test_AA(size, printON);
}

void insert(int size, int printON){
    test("asn1_a", size, printON);
}

void mergS(int size, int printON){
    test("asn1_b", size, printON);
}

void
mixed(int size, int printON, int k){
    test_mix(size, k, printON);
}


int main(int argc, char **argv){
    int k = 2;
    int size = 2000000;
    int printON = 0;

//    insert(size,printON);
//    mergS(size,printON);
//    mixed(size, printON, k);


//    super_k(argc, argv, num[6],50);

    compare2merge(size, printON);
    return 0;
}

