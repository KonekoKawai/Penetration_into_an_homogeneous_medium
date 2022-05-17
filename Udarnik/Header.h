#pragma once

#include <iostream>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include <SDL.h> // ����������� � �������

#include "depth_calculation.h"
#include "Texture.h"
#include "motion_display.h"

const int SCREEN_WIDTH = 1100; // ������ ������
const int SCREEN_HEIGHT = 900; // ������ ������

const int SCREEN_WIDTH_MOTION = SCREEN_WIDTH/4*3; // ������ ������ ��� ����������� ��������
const int SCREEN_HEIGHT_MOTION = SCREEN_HEIGHT; // ������ ������ ��� ����������� ��������

const int SCREEN_WIDTH_INFO = SCREEN_WIDTH / 4; 
const int SCREEN_HEIGHT_INFO = SCREEN_HEIGHT;

const int HEIGHT_UDARNIK = SCREEN_HEIGHT_MOTION*2; // ������ ��������


const int THICKHNESS_PIKSEL = 6; // ������ ����� � ��������

//#define Test


#ifdef Test
const int ARRAY_SIZE = 5; // ���������� ��������� ��� ���������
#endif

using std::cout;
using std::cin;
using std::endl;

SDL_Window* gWindow = NULL; // ���������� ���� ��� �����
SDL_Surface* gScreenSurface = NULL; // ���������� ����������� ��� ����������� ���� 
SDL_Renderer* gRenderer = NULL; // ���������� ��������� ���������� �������� ��������� �������� �� �����

SDL_Rect rect_PDSK = { 0 , 0 , SCREEN_WIDTH / 4 * 3 , SCREEN_HEIGHT }; // ������� ��� ����������� ������� ���������
SDL_Rect rect_info_Num = { SCREEN_WIDTH / 4 * 3  ,  0  , SCREEN_WIDTH / 4 + 1 , SCREEN_HEIGHT/4 }; // ������� ��� ����������� ���������� � ��������� ��������
SDL_Rect rect_info_PDSK = { SCREEN_WIDTH / 4 * 3 , SCREEN_HEIGHT / 4 , SCREEN_WIDTH / 4 + 1 , SCREEN_HEIGHT/4*3 }; // ������� ��� ����������� ���������� � ����

// ��������� ������� 
void init();  // ������� ������������� ���� 
void close();  // ������������� ������ 
bool enter(depth_calculation* udar);