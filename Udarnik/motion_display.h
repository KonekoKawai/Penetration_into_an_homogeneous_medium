#pragma once

#include <iostream>
#include <SDL.h>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>

#include "depth_calculation.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern const int SCREEN_WIDTH_MOTION; // Ширина экрана для отображения ударника
extern const int SCREEN_HEIGHT_MOTION; // Высота экрана для отображения ударника

extern const int SCREEN_WIDTH_INFO;
extern const int SCREEN_HEIGHT_INFO;

// Отступы для экрана с информацией и графика с ней 
const int WIDTH_INDENT = SCREEN_WIDTH / 50;
const int HEIGHT_INDENT = SCREEN_HEIGHT / 30;

extern const int PIKSEL_IN_ON_M_MOTION;


extern const int THICKHNESS_PIKSEL; // Толщина точек и прочего на экране
extern const int HEIGHT_UDARNIK; 

extern SDL_Renderer* gRenderer; // Отображает состояние рендеринга Помогает рендерить текстуры на экран

extern SDL_Rect rect_PDSK; // Квадрат для отображения системы координат
extern SDL_Rect rect_info_PDSK; // Квадрат для отображения информации
extern SDL_Rect rect_info_Num; // Квадрат для отображения информации


class motion_display
{
public:
	motion_display();
	~motion_display();

	void display_PDSK(); // Отображает систему координат на 3/4 экрана слева
	
	int get_current_y();
	void display_motion_point(depth_calculation* udar); // Отобразить движение точки
	void display_motion_klin(depth_calculation* udar); // Отобразить движение клина
	void display_info_PDSK(); // Отобразить в окне информации PDSK 
	void display_info_PSDK_V_and_L(depth_calculation* udar); // Отобразить в окне информации Изменение 

	void scaling_PDSK(depth_calculation *udar); // Изменяет масштаб PDSK 
private:
	int current_x;
	int current_y;
	int start_x;
	int start_y;
	SDL_Rect current_point;
	SDL_Rect end_point;

	int PIKSEL_IN_ON_M_INFO_L; // Пикселей в одном метре  ДЛЯ экрана с информации о движении ударника
	int PIKSEL_IN_ON_M_INFO_V; // Пикселей в одном метре  ДЛЯ экрана с информации о движении ударника

};


