//
//  main.cpp
//  QueenSearch
//
//  Created by ljp on 17/5/27.
//  Copyright © 2017年 LiuJiapeng. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define N 10000000
using namespace std;

int queen[N], randCol[N], mainDiag[N * 2] = {0}, backDiag[N * 2] = {0};
int diagConflict = 0;

void qs_init(int);
void qs_search(int);

int main(int argc, const char * argv[]) {
    int c = 100;
    double start, finish;
    srand(time(0));
    start = clock();
    qs_init(c);
    qs_search(c);
    finish = clock();
    cout << "Time used = " << (finish - start) / CLOCKS_PER_SEC << endl;
    return 0;
}

void qs_init(int c) {
    int r;
    for (int i = 0; i < N; i++)
        randCol[i] = i;
    for (int i = 0; i < N; i++) {   // 获得随机的列排列
        r = rand() % N;
        swap(randCol[i], randCol[r]);
    }
    
    /* 前N-c行的皇后无对角线冲突 */
    int q = 0, rc = 0, dir = 1;
    while (q < N - c) {
        if (randCol[rc] == -1) {
            if (rc + dir >= N || rc + dir < 0)  // 到两端则转向
                dir *= -1;
            rc += dir;
            continue;               // 该列已有皇后则跳过
        }
        if (mainDiag[randCol[rc] - q + N - 1] == 1 || backDiag[randCol[rc] + q] == 1) {
            if (rc + dir >= N || rc + dir < 0)  // 到两端则转向
                dir *= -1;
            rc += dir;
            continue;               // 对角线上有皇后则跳过
        }
        queen[q] = randCol[rc];
        mainDiag[randCol[rc] - q + N - 1] = 1;
        backDiag[randCol[rc] + q] = 1;
        randCol[rc] = -1;
        if (rc + dir >= N || rc + dir < 0)      // 到两端则转向
            dir *= -1;
        rc += dir;
        q++;
    }
    
    /* 后c行的皇后随机摆放 */
    rc = 0;
    while (q < N) {
        if (randCol[rc] == -1) {
            rc++;
            continue;               // 该列已有皇后则跳过
        }
        queen[q] = randCol[rc];
        diagConflict += mainDiag[randCol[rc] - q + N - 1]++;
        diagConflict += backDiag[randCol[rc] + q]++;
        randCol[rc] = -1;
        rc++;
        q++;
    }
}
/*
void qs_search(int c) {
    int q1, q2, newConflict;
    while (diagConflict > 0) {
        q1 = N - c + rand() % c;
        q2 = rand() % N;
        newConflict = diagConflict - mainDiag[queen[q1] - q1 + N - 1] - backDiag[queen[q1] + q1] - mainDiag[queen[q2] - q2 + N - 1] - backDiag[queen[q2] + q2] + 4 + mainDiag[queen[q2] - q1 + N - 1] + backDiag[queen[q2] + q1] + mainDiag[queen[q1] - q2 + N - 1] + backDiag[queen[q1] + q2];
        if (newConflict <= diagConflict) {
            mainDiag[queen[q1] - q1 + N - 1]--;
            backDiag[queen[q1] + q1]--;
            mainDiag[queen[q2] - q2 + N - 1]--;
            backDiag[queen[q2] + q2]--;
            swap(queen[q1], queen[q2]);
            mainDiag[queen[q1] - q1 + N - 1]++;
            backDiag[queen[q1] + q1]++;
            mainDiag[queen[q2] - q2 + N - 1]++;
            backDiag[queen[q2] + q2]++;
            diagConflict = newConflict;
        }
    }
    cout << "A solution has been found." << endl;
}*/

void qs_search(int c) {
    int q1, q2, newConflict;
    while (diagConflict > 0) {
        for (q1 = 0; q1 < N; q1++) {
            if (mainDiag[queen[q1] - q1 + N - 1] == 1 && backDiag[queen[q1] + q1] == 1)
                continue;   // 无对角线冲突则跳过
            for (q2 = 0; q2 < N; q2++) {
                newConflict = diagConflict - mainDiag[queen[q1] - q1 + N - 1] - backDiag[queen[q1] + q1] - mainDiag[queen[q2] - q2 + N - 1] - backDiag[queen[q2] + q2] + 4 + mainDiag[queen[q2] - q1 + N - 1] + backDiag[queen[q2] + q1] + mainDiag[queen[q1] - q2 + N - 1] + backDiag[queen[q1] + q2];
                if (newConflict < diagConflict) {  // 若新冲突数不大于旧冲突数
                    mainDiag[queen[q1] - q1 + N - 1]--;
                    backDiag[queen[q1] + q1]--;
                    mainDiag[queen[q2] - q2 + N - 1]--;
                    backDiag[queen[q2] + q2]--;
                    swap(queen[q1], queen[q2]);     // 交换两个皇后所在的列
                    mainDiag[queen[q1] - q1 + N - 1]++;
                    backDiag[queen[q1] + q1]++;
                    mainDiag[queen[q2] - q2 + N - 1]++;
                    backDiag[queen[q2] + q2]++;
                    diagConflict = newConflict;
                    break;
                }
            }
        }
    }
    cout << "A solution has been found." << endl;
}

