#pragma once

#include <iostream>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include <SDL.h> // Отображение и графика

#include "depth_calculation.h"
#include "Texture.h"
#include "motion_display.h"

const int SCREEN_WIDTH = 1100; // Ширина экрана
const int SCREEN_HEIGHT = 900; // Высота экрана

const int SCREEN_WIDTH_MOTION = SCREEN_WIDTH/4*3; // Ширина экрана для отображения ударника
const int SCREEN_HEIGHT_MOTION = SCREEN_HEIGHT; // Высота экрана для отображения ударника

const int SCREEN_WIDTH_INFO = SCREEN_WIDTH / 4; 
const int SCREEN_HEIGHT_INFO = SCREEN_HEIGHT;

const int HEIGHT_UDARNIK = SCREEN_HEIGHT_MOTION*2; // Высота ударника


const int THICKHNESS_PIKSEL = 6; // Ширина точки в пикселях

//#define Test


#ifdef Test
const int ARRAY_SIZE = 5; // Количество ударников для просмотра
#endif

using std::cout;
using std::cin;
using std::endl;

SDL_Window* gWindow = NULL; // Глобальное окно для всего
SDL_Surface* gScreenSurface = NULL; // Глобальная поверхность для глобального окна 
SDL_Renderer* gRenderer = NULL; // Отображает состояние рендеринга Помогает рендерить текстуры на экран

SDL_Rect rect_PDSK = { 0 , 0 , SCREEN_WIDTH / 4 * 3 , SCREEN_HEIGHT }; // Квадрат для отображения системы координат
SDL_Rect rect_info_Num = { SCREEN_WIDTH / 4 * 3  ,  0  , SCREEN_WIDTH / 4 + 1 , SCREEN_HEIGHT/4 }; // Квадрат для отображения информации о состоянии движения
SDL_Rect rect_info_PDSK = { SCREEN_WIDTH / 4 * 3 , SCREEN_HEIGHT / 4 , SCREEN_WIDTH / 4 + 1 , SCREEN_HEIGHT/4*3 }; // Квадрат для отображения информации с ПДСК

// Прототипы функций 
void init();  // Функция инициализация окна 
void close();  // Инициализация выхода 
bool enter(depth_calculation* udar);