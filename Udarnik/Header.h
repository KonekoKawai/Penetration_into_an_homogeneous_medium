#pragma once

#include <iostream>
#include <cmath>
#include <conio.h>
#include <Windows.h>
#include <SDL.h> // Отображение и графика
#include <SDL_ttf.h> // Шритфы

#include "depth_calculation.h"
#include "Texture.h"
#include "motion_display.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
// ПО УМОЛЧАНИЮ Но меняется далее Или нет?
SDL_DisplayMode info_Display_Options;

const int SCREEN_WIDTH = 1200; // Ширина экрана
const int SCREEN_HEIGHT = 700; // Высота экрана

const int SCREEN_WIDTH_MOTION = SCREEN_WIDTH/4*3; // Ширина экрана для отображения ударника
const int SCREEN_HEIGHT_MOTION = SCREEN_HEIGHT; // Высота экрана для отображения ударника

const int SCREEN_WIDTH_INFO = SCREEN_WIDTH / 4;
const int SCREEN_HEIGHT_INFO = SCREEN_HEIGHT;
//////////////////////////////////////////////////////////////////////////////////////////////////////

const int THICKHNESS_PIKSEL = 3; // Ширина точки в пикселях

const int NUMB_TEXT_INFO = 11; // Количество окон с текстом в окне с информацией
const int NUMB_TEXT = 4;
const int FONT_SIZE = 14;// Размер шрифта

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
bool enter(depth_calculation* udar); // Функция ввода параметров

#define Test

#ifdef Test
const int ARRAY_SIZE = 5; // Количество ударников для просмотра
#endif