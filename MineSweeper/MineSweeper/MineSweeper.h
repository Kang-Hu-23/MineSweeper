#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include<locale.h>
#include<windows.h>

#define WALL L'■'

typedef struct 
{
    POINT position;  // 鼠标点击的坐标
    char buttonType; // 'L' 表示左键，'R' 表示右键
} MouseClickInfo;

void SetLoc();

void SetCmd();

void SetPos(short x, short y);

void Menu();

void SetGam(int* x,int* y,int* z);

int** InitInviMatrix(int x, int y);

void PutMine(int x ,int y ,int mine , int** arr_invisible);

void PutNum(int x, int y, int mine, int** arr_invisible);

void CreatMap(int x, int y);

MouseClickInfo getMouseClick();

void LeftJudge(int x, int y, int* z, int** arr_invisible, MouseClickInfo clickInfo);

void RightJudge(int x, int y, int** arr_invisible, MouseClickInfo clickInfo);

void Check(int x, int y, int*, int** arr_invisible);
